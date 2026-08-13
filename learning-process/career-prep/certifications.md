# Certifications for a Forward Deployed Engineer (FDE)

> **TL;DR:** There is no required or official certification for an FDE. Employers hire FDEs for solving customer problems and shipping projects — certs are *supporting evidence*, not the main attraction. Pick 2–3 high-ROI certs that match your target stack, and spend the rest of your time building. (Researched 2026; see [agilefever.com](https://agilefever.com/forward-deployed-engineers-best-certifications-fde/) and [examos.io](https://examos.io/blog/how-to-become-forward-deployed-engineer-certifications).)

---

## 1. Core Principle

- **No FDE certification is required.** "FDE certifications" sold by content farms (GSDC, ADaSci CFDE, Udemy "FDE Mastery", etc.) are **low-credibility — skip them.** They signal nothing to real hiring managers.
- **What certs actually do:** build verifiable technical depth and get you through resume screens when switching careers or starting out.
- **What employers actually want (ranked):** ① real projects ② customer/problem-solving skills ③ technical depth ④ certifications.
- **The failure modes certs solve:** being too shallow to earn trust from senior engineers at the client site.
- **The failure mode certs don't solve:** soft skills — stakeholder handling, simplification, translating complexity, calming chaos, influencing without authority. Those are built through deliberate practice, not exams.

---

## 2. Tier 1 — Worth Doing (Highest ROI)

| Certification | Why | Cost/Time | When |
|---|---|---|---|
| **AWS Solutions Architect – Associate (SAA-C03)** | Consensus #1. Builds the trade-off reasoning FDE work runs on. AWS is the default primary cloud for most FDE employers. | ~$150, 3–6 weeks of focused study | During Phase 3.3 (Cloud Fundamentals) |
| **基本情報技術者 (Fundamental IT Engineer, FE)** | Japan's national baseline IT qualification. Resume differentiator for Japanese companies + PR points (see §5). | ~¥7,500, self-study | Early — baseline credibility in Japan |
| **応用情報技術者 (Applied IT Engineer, AP)** | Japan mid-level; covers system strategy + project management — directly FDE-relevant. Second exam → max 10 PR points. | ~¥7,500, self-study | 6–12 months after FE |

## 3. Tier 2 — Strong, Situational

| Certification | When it makes sense |
|---|---|
| **Azure AZ-104 / AZ-305** | Microsoft dominates Japanese enterprise. Pick AZ-104 (ops) or AZ-305 (architecture) if targeting Azure-based employers. |
| **GCP Professional Cloud Architect** | Target companies heavy on GCP or data/analytics/ML workloads. |
| **CKA (Certified Kubernetes Administrator)** | Hands-on exam, real operational depth. Only if K8s appears in target roles (Phase 3.4). |
| **HashiCorp Terraform Associate** | Cheap, fast, validates IaC (Phase 3.5). |
| **CompTIA Security+** | Pragmatic entry to enterprise security if you have no security background (Phase 6E). |
| **AWS Security Specialty (SCS-C02)** / **Microsoft SC-100** | Cloud-specific security depth (IAM, compliance frameworks). After Security+, not entry-level. |

## 4. Tier 3 — Only If Targeting Data/AI-Heavy FDE

| Certification | Notes |
|---|---|
| **AWS Data Engineer Associate (DEA-C01)** | Redshift, Glue, Lake Formation, Kinesis. Phase 6A is often the *majority* of FDE work — arguably under-tiered. |
| **Databricks Certified Data Engineer Associate** | Databricks dominates enterprise data environments. |
| **Microsoft Azure AI Engineer (AI-103)** | Signals AI deployment cred for enterprise AI products (Phase 6D). |

## 5. Japan-Specific Certifications (国家資格 — IPA ITEE)

> Administered by IPA (情報処理推進機構). Full details in `personal-growth/japan/japan-national-qualification.md`. These are national qualifications — highly recognizable to Japanese hiring managers and grant points toward the Highly Skilled Professional (HSP) visa / fast-tracked PR.

**Hierarchy:**
| Level | Exam | Notes |
|---|---|---|
| L1 | IT Passport (ITパスポート) | Entry IT literacy — usually skippable for engineers |
| L2 | **Fundamental IT (基本情報技術者)** | Junior baseline — worth taking |
| L3 | **Applied IT (応用情報技術者)** | Mid-level; system strategy + project management — most FDE-relevant |
| L4 | Advanced / Specialist (高度試験) | Choose by specialization below |

**L4 specialist exams relevant to FDE:**
- **プロジェクトマネージャ (PM)** — delivery, stakeholder, scope management at client sites
- **ネットワークスペシャリスト (NW)** — system integration, API management, webhooks, connectivity
- **データベーススペシャリスト (DB)** — data transformation, customer insights
- **情報処理安全確保支援士 (RISS / Security Specialist)** — security + compliance; a registered national qualification, valuable for regulated clients (gov/finance/healthcare)
- システムアーキテクト (SA), ITサービスマネージャ (ITSM), ITストラテジスト — situational

**PR/visa angle:**
- Each ITEE exam cleared = 5 HSP points; 2+ exams = 10 points (the cap).
- 70 points → PR after 3 years; 80 points → PR after 1 year.
- L3/L4 don't grant more points than L2, but they unlock the 10-point cap via a second exam.

**Practical notes:**
- No age/nationality/education restrictions. Can be taken while enrolled in a Master's.
- L1 & L2 are CBT; L3/L4 are paper-based (April/October) and primarily in Japanese.
- Outside Japan, ITPEC exams can be taken in English in select countries (Vietnam, Thailand, etc.) and are legally recognized in Japan.

## 6. Other Japan-Market Considerations

- **Oracle certifications** — Oracle is deeply embedded in Japanese enterprise (finance/gov). Oracle Certified Professional (OCP) or Oracle Master is common on Japanese resumes, but **only if** targeting Oracle-heavy shops.
- **AWS/Cloud certs in Japan** — AWS is the dominant public cloud in Japan; SAA-C03 reads well on Japanese resumes. Azure follows for enterprise.
- **JLPT (N2)** — not a technical cert, but the *real* career moat for a Japan FDE. N2 is the functional floor for a Japanese workplace. Treat it as more valuable than any technical cert on this list.
- **統計検定 / データサイエンティスト検定** — optional signal if targeting data-heavy roles.

## 7. Recommended Sequencing (for a Japan FDE target)

1. **AWS SAA-C03** — during Phase 3.3.
2. **基本情報技術者 (FE)** — early, cheap Japan baseline.
3. **One Tier-2** (CKA or Azure/GCP) — only after knowing the target employer's stack.
4. **応用情報技術者 (AP)** — 6–12 months later; gives 10-point PR cap.
5. **Tier-3 data/AI cert** — only if data/AI-heavy FDE roles are the target.
6. **JLPT N2** — daily, ongoing, the biggest moat.

## 8. Mostly Skip

- PMP, Scrum Master, ITIL, generic AI-awareness certs, coding certificates, any "FDE certification" from non-vendor bootcamps.

---

## Sources
- https://agilefever.com/forward-deployed-engineers-best-certifications-fde/
- https://examos.io/blog/how-to-become-forward-deployed-engineer-certifications
- https://www.gsdcouncil.org/certified-forward-deployed-engineer (not recommended, listed for awareness)
- IPA official site: https://www.ipa.go.jp/shiken/index.html
- Repo note: `personal-growth/japan/japan-national-qualification.md`
