# Job Search — ATS-First Discovery Pipeline (Setup Plan)

> **Status: LIVE (2026-08-17).** The tool is built and running in the separate
> private repo [`ParthG08/job-alerts`](https://github.com/ParthG08/job-alerts),
> driven by a GitHub Actions cron (every 4h, runs on GitHub's servers, laptop
> can be off). Alerts go to Telegram bot `@parth_job_alert_bot`. This doc is
> the design + decisions record; `companies.json` here is the **source of
> truth** for the target list (mirrored to the tool repo's
> `config/companies.json`).

## 1. Overview

Goal: catch job postings on company ATS boards **before** they reach
LinkedIn/Indeed/aggregators (which sync hours-to-days late), so applications
land among the first reviewed.

- **Discovery is automated; applying stays human-in-the-loop.** Full
  auto-apply is deliberately rejected (form diversity, bot detection, low
  conversion quality).
- Free tier only — zero paid infra. No Firecrawl paid plan.

## 2. Platform Landscape (ranked for India)

| Rank | Platform | India profile | Public free JSON API? | Discovery mechanism |
|---|---|---|---|---|
| 1 | **Workday** | Highest volume (MNCs, GCCs, IT services, BFSI) | Semi-public (undocumented) | `POST https://<tenant>.wdX.myworkdayjobs.com/wday/cxs/<tenant>/<site>/jobs` body `{"appliedFacets":{},"limit":20,"offset":0,"searchText":""}` → JSON, no auth |
| 2 | **Greenhouse** | Very high (startups, unicorns, product firms) | Yes | `GET https://boards-api.greenhouse.io/v1/boards/{company}/jobs` |
| 3 | **SAP SuccessFactors** | High (EU/global enterprise, telecom, pharma) | No | Skipped — enterprise auth only |
| 4 | **Oracle Taleo / Cloud HCM** | High (legacy enterprise, finance) | No | Skipped — no public boards, DOM scraping only |
| 5 | **Ashby** | Fast growing (modern AI/SaaS/VC tech) | Yes | `GET https://api.ashbyhq.com/posting-api/job-board/{company}` |
| 6 | **Lever** | Moderate–high (mid/large product tech) | Yes | `GET https://api.lever.co/v0/postings/{company}?mode=json` |
| 7 | **iCIMS / SmartRecruiters** | Moderate (US MNCs, mid IT) | Partial | SmartRecruiters has a public posting API; iCIMS needs auth/partner creds |

- **Firecrawl** is used only as a fallback for custom/heavily dynamic career
  pages (beyond the ~5 free-tier limit for this setup). Standard ATS JSON
  endpoints are free and faster — prefer them first.
- Firecrawl free tier = 1,000 credits/month. With 25 companies and most on
  free ATS APIs, only a handful of custom pages route through Firecrawl.

## 3. Architecture (Hybrid Poll → Filter → Alert)

```
[Target list: companies.json]
        │
        ▼
[Pollers]  ── cron / GitHub Actions / worker, every 2–6 hrs
  ├── Greenhouse  → REST
  ├── Lever       → REST
  ├── Ashby       → REST
  ├── Workday     → POST /wday/cxs
  └── Firecrawl   → only custom career sites (Amazon, Microsoft, BrowserStack)
        │
        ▼
[Normalize]  → common Job {company, title, location, url, id, posted, desc}
        │
        ▼
[Filter & Score]  → keyword match vs profile (stack/seniority/geo); optional LLM
        │
        ▼
[Dedupe]  → seen-ids state file (only NEW postings alert)
        │
        ▼
[Alert]  → Telegram / Slack (company, role, apply link, match summary)
        │
        ▼
[You]  → review + submit in ~10s (optionally with Simplify-style assisted fill)
```

Decisions locked in from research:
- **Scope:** 4–5 platforms, 20–40 companies → keeps rate limits, alert noise,
  and maintenance trivial; enables referral + targeted outreach per role.
- **Poll cadence:** 2–4×/day (25 companies → ~50–100 requests/day, safely
  under any free limit).
- **Discovery trap:** ATS scrapers need an explicit URL/slug list; they do not
  discover new companies. Keep the target list curated.

## 4. Efficacy (from research)

| Stage | Efficacy | Note |
|---|---|---|
| Early discovery speed | ~90% | Internal listings caught hours ahead of LinkedIn |
| Clean parsing | ~85% | Markdown/JSON from React/SPA portals |
| Broad company coverage | ~60% | Limited to curated URL list |
| **Overall search impact** | **~75%** | First-applicant advantage; conversion still depends on resume fit |

## 5. Cost Decision

- **Firecrawl: free tier only** (1,000 credits/mo). ~15 custom pages × 2×/day
  fits well within it. Do not buy the paid plan.
- Standard ATS APIs (Greenhouse/Lever/Ashby) are free and need no scraper.
- Workday undocumented JSON endpoint is free; no Firecrawl credits needed.

## 6. Target Companies (25) — see `companies.json`

> **Platforms verified against live ATS APIs on 2026-08-17.** Several of the
> original assignments were wrong — corrected in `tools/job-search/companies.json`
> and mirrored to the tool repo's `config/companies.json`:

| Company | Actual platform | Notes |
|---|---|---|
| Postman, InMobi, PhonePe, HighRadius, Razorpay | **Greenhouse** | Razorpay slug is `razorpaysoftwareprivatelimited` |
| Zeta | **Lever** | was wrongly listed as Greenhouse |
| Signoz | **Ashby** | |
| Freshworks, ServiceNow, Swiggy, Whatfix | **SmartRecruiters** | ServiceNow/Swiggy/Whatfix were wrongly listed as Workday/Greenhouse |
| Salesforce, Sprinklr, BrowserStack | **Workday** | hosts are `wd12`/`wd1`/`wd3` — cannot be guessed; BrowserStack was wrongly listed as custom |
| Darwinbox, Cisco, Hasura, Juspay, Icertis, Chargebee, CleverTap, MoEngage, Zepto | **custom** | Darwinbox→BambooHR, Cisco→Phenom, Hasura→gem.com; many need Firecrawl or per-site parsing |
| Amazon, Microsoft | **custom** | careers sites don't expose a public JSON API |

## 7. Decided / Done — recorded for future reference

- [x] **Runner** — GitHub Actions cron (`poll.yml`), schedule `0 */4 * * *`.
- [x] **Alert channel** — Telegram (`@parth_job_alert_bot`); bot token +
      chat id set as repo secrets `TELEGRAM_BOT_TOKEN` / `TELEGRAM_CHAT_ID`
      on `ParthG08/job-alerts`. Slack webhook supported but not configured.
- [x] **State file** — `.state/seen.json`, persisted between runs via
      `actions/cache` in the workflow.
- [x] **Filtering** — keyword word-boundary scoring against `profile` +
      company overrides; optional LLM layer (`LLM_API_KEY`) disabled for now.
- [x] **Profile defaults** — backend-engineer skills/locations in
      `companies.json`; tune to reduce false positives (see next section).
- [x] **Firecrawl** — not configured; custom sites use plain HTTP fallback
      (best-effort). Add `FIRECRAWL_API_KEY` later for those.

**Still open (future):**

- [ ] **Company list finalization** — keep/drop/adjust the 25, esp. the
      `custom` entries (Darwinbox, Cisco, Hasura, Juspay, Icertis, Chargebee,
      CleverTap, MoEngage, Zepto, Amazon, Microsoft).
- [ ] **Icertis** — career site 301-redirects (broken); needs a real board URL
      or removal. **Darwinbox** — times out on plain HTTP.
- [ ] **LLM filter** — enable if alert noise becomes a problem.

## 8. Live State & Known Issues

**Implemented** (built in the separate private repo
[`ParthG08/job-alerts`](https://github.com/ParthG08/job-alerts)):

- Pollers: Greenhouse, Lever, Ashby, SmartRecruiters, Workday (paginated,
  limit caps at 20/page), custom/Firecrawl fallback.
- Filter (keyword word-boundary scoring + optional LLM), dedupe state,
  Telegram/Slack alerts, GitHub Actions cron every 4h.
- Verified live: ~780 jobs scanned per run across the API platforms; only
  Icertis and Darwinbox fail (see above).

**Known constraints worth remembering:**

1. Workday `wdN` host segment and site name **cannot be guessed** — must be
   read from the careers URL (devtools `cxs` filter) per company.
2. Workday `limit` silently caps at 20 — poller pages with `offset`.
3. SmartRecruiters API returns `200` + `totalFound: 0` for unknown companies
   (looks like a hit but isn't).
4. Custom career sites need Firecrawl (or per-site parsing) for quality
   results; plain HTTP gives noisy links.
5. Cron keeps running with the laptop off — it's GitHub-hosted.

**Sync rule:** edit `tools/job-search/companies.json` here first, then copy to
`job-alerts/config/companies.json` and push both repos.
