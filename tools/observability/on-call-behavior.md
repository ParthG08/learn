# On-Call Behaviour — What to Do and What Not to Do

On-call is a rotation where you are the primary responder for production incidents during a defined window (day/night, week, etc.). The goal is **not** to fix everything yourself — it's to **restore service safely and quickly**, escalate when needed, and communicate clearly. How you behave matters as much as how you debug.

---

## The On-Call Mindset

| Principle | Meaning |
|---|---|
| **Availability > heroics** | The business metric is time-to-restore service, not "who fixed it alone". |
| **Mitigate first, investigate second** | Restore users first (rollback, failover, kill switch). Debug root cause after things are calm. |
| **You are the communicator, not just the debugger** | Half of the job is keeping stakeholders informed. Silence is the worst failure mode. |
| **SLOs, not perfection** | Aim to keep within your error budget. Not every alert needs a page. |
| **Blameless** | On-call humans are expected to make mistakes. Postmortems fix systems, not people. |

---

## Before You Go On-Call (Preparation)

- [ ] **Know your rotation window** — exact start/end times, timezone, and who to hand over to.
- [ ] **Read the runbooks** for the services you cover, *before* anything breaks.
- [ ] **Know the escalation chain** — who to call when you can't fix it, at every severity.
- [ ] **Check dashboards & alerts** — understand which alerts are currently firing, and what "healthy" looks like.
- [ ] **Test your access** — can you actually log in, reach the prod environment, get on-call tooling (PagerDuty/Opsgenie), and view logs/metrics/traces?
- [ ] **Know the SLOs** — which services are protected by error budgets, and what the alert thresholds mean.
- [ ] **Learn the "recent incidents"** — check recent postmortems; you'll likely inherit the same root causes.
- [ ] **Prepare your environment** — laptop charged, reliable internet, phone reachable, notifications loud.
- [ ] **Confirm overlap/handover** — talk to the outgoing person about anything half-finished.

---

## During On-Call — What to DO

### 1. Respond Fast and Acknowledge

- **Acknowledge alerts immediately** — even if just to say "looking at it". The timer and your teammates are waiting on you.
- Set a personal SLO for acknowledgement (e.g. under 5 minutes for P1, under 15 for P2).
- If you can't engage, acknowledge anyway and say when you'll start.

### 2. Communicate Continuously (the golden rule)

- Post updates to the incident channel **as you go**: what you see, what you're trying, what you need.
- Follow the format: **What is happening → What we're doing → What we need**.
- Update the incident status (Investigating / Identified / Monitoring / Resolved) as it changes.
- Involve a **dedicated communicator / incident commander** on large incidents so you can stay heads-down debugging.
- Over-communicate frequency for severe incidents (every 10–15 min), even if there's no news — "still investigating" is valid.

### 3. Mitigate / Stabilize First

1. **Stop the bleeding** — rollback the deploy, fail over to the secondary, toggle the feature flag, scale out, shed load.
2. Only then **investigate the root cause**.
3. Prefer **reversible** actions. Never do something permanent while uncertain.
4. Use the tools you prepared for: runbooks, kill switches, canary rollbacks, database failovers.

### 4. Follow the Incident Lifecycle

| Stage | Actions |
|---|---|
| **Detect** | Alert fires (or user report). Confirm it's real, not a flapping/false alert. |
| **Triage / Acknowledge** | Confirm severity, page the right people, open the incident channel/ticket. |
| **Mitigate** | Apply the fastest safe fix to restore service (usually rollback/failover). |
| **Diagnose** | After service is stable, find the root cause from logs/traces/metrics. |
| **Resolve & Monitor** | Declare resolved, keep monitoring for a defined window (e.g. 30–60 min) before closing. |
| **Postmortem** | Write a blameless postmortem: timeline, root cause, impact, action items, follow-ups. |

### 5. Use Your Escalation Chain

- Escalate **early**, not after burning hours solo. Escalating is a strength, not a failure.
- Know what "escalation" triggers for you: second on-call, team lead, engineering manager, on-duty SRE.
- Escalate when: you're stuck > ~30–60 min, the incident is growing in scope, or it crosses a severity boundary.
- When you hand off a live incident, give the full context: timeline, what was tried, current state, what's next.

### 6. Document As You Go

- Copy/paste the timeline into the incident channel as you work (what time, what changed, what you saw).
- Capture error messages, log lines, and commands you ran — future-you and postmortems depend on this.
- If you fix something, note whether it's a permanent fix or a band-aid that needs follow-up.

### 7. Protect the Error Budget

- Understand whether the current issue is within budget (acceptable risk) or burning it fast.
- Don't take reckless mitigations for alerts that don't matter; don't ignore ones that do.
- Tune or silence genuinely noisy alerts *after* the incident, with a ticket — never during the firefight.

### 8. Hand Over Properly

- Give the next person a written handover: open issues, ongoing incidents, noisy alerts, things mid-flight.
- On multi-day rotations, do a daily handover even if nothing happened.
- Leave the environment in the state you found it (dashboards, incidents closed, alerts clean).

### 9. After On-Call Ends

- Attend/write the postmortem — blameless, action-oriented.
- Log "annoyances" to fix: flapping alerts, missing runbooks, tooling gaps.
- Rest. Sleep debt from a rough rotation is real; recovering is part of doing it well next time.

---

## What NOT to Do

| ❌ Don't | Why / Instead |
|---|---|
| **Don't stay silent** | Silence looks like nothing is happening or that you don't care. Post at least a "still investigating". |
| **Don't fix by guesswork / shotgun changes** | You'll make it worse. Make one change, verify, move on. |
| **Don't make permanent/irreversible changes mid-incident** | Prefer rollback over "fixing forward" unless a runbook explicitly says so. |
| **Don't restart/kill things without checking side effects** | A DB restart or pod kill can cascade. Understand what you're touching. |
| **Don't go rogue / lone-wolf it** | On a big incident, work *with* the channel. Say what you're doing so others don't duplicate or conflict. |
| **Don't ignore severity** | Don't treat a P1 like a P2, or burn the error budget on a noisy P3. |
| **Don't hide or downplay problems** | No "everything is fine" when it isn't. No hero-fixes that paper over the real issue. |
| **Don't blame people** | Blame the process/system in the postmortem, never the human who was awake at 3am. |
| **Don't claim resolved too early** | Confirm the fix holds and keep monitoring before closing the incident. |
| **Don't skip the handover** | Leaving without a handover strands the next person and creates silent risk. |
| **Don't take it personally** | You will miss things, cause incidents, and be woken up. That is normal, expected, and covered by being blameless. |
| **Don't neglect yourself** | If you're sleep-deprived, ask for help / escalate. Tired on-call engineers cause more incidents. |

---

## Communication Cheat-Sheet

**Good update:** "P1 — checkout API is timing out (5xx 40%). We've rolled back the last deploy, error rate dropping. Investigating the bad commit. ETA 20 min."

**Bad update:** (silence for 45 minutes)

**Good escalation:** "I've been investigating for 30 min, no root cause yet. Escalating to [name] for the queue-backpressure angle."

---

## Key Terms

| Term | Meaning |
|---|---|
| **On-call rotation** | Scheduled schedule of who's the primary (and secondary) responder. |
| **Page / Alert** | Notification that requires a human response. |
| **Severity (SEV1/SEV2/…)** | Incident priority based on user impact and SLO burn. |
| **Error budget** | Amount of downtime the service is allowed within an SLO window. |
| **MTTA** | Mean Time To Acknowledge — how fast alerts get a human response. |
| **MTTR** | Mean Time To Resolve — time from alert to service restored. |
| **Runbook** | Documented procedure for handling a known failure mode. |
| **Incident Commander** | Person coordinating communication/escalation during large incidents. |
| **Blameless postmortem** | Root-cause review that treats failures as systemic, not personal. |

---

## Summary — Do / Don't at a Glance

- **Do:** acknowledge fast · communicate continuously · mitigate before investigating · escalate early · document as you go · hand over well · write the postmortem · rest.
- **Don't:** go silent · make irreversible changes · lone-wolf · ignore severity · hide problems · blame people · close incidents too early · skip handover.
