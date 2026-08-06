#!/usr/bin/env python3
"""SRS engine for the FDE learning repo.

SM-2 spaced repetition over per-file cards (.md notes).

Ratings:
  again  -> q=0 (forgot, card resets)
  hard   -> q=3 (correct, struggled)
  good   -> q=4 (correct)
  easy   -> q=5 (correct, trivial)

CLI:
  python scripts/srs.py today                 List due cards (grouped by topic)
  python scripts/srs.py today --topic PATH    Due cards under PATH only
  python scripts/srs.py update PATH RATING    Record a rating for a card
  python scripts/srs.py schedule              Upcoming reviews per topic
  python scripts/srs.py stats                 Summary of the whole deck
"""

import argparse
import json
import sys
from datetime import date, timedelta
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
STATE_FILE = REPO_ROOT / ".srs" / "state.json"
DEFAULT_EASE = 2.5
MIN_EASE = 1.3

RATINGS = {"again": 0, "hard": 3, "good": 4, "easy": 5}


def load_state():
    if not STATE_FILE.exists():
        return {"version": 1, "files": {}}
    with STATE_FILE.open() as fh:
        return json.load(fh)


def save_state(state):
    STATE_FILE.parent.mkdir(parents=True, exist_ok=True)
    with STATE_FILE.open("w") as fh:
        json.dump(state, fh, indent=2, sort_keys=True)
        fh.write("\n")


def today_str():
    return date.today().isoformat()


def sm2(q, reps, interval, ease):
    """Return (reps, interval_days, ease) after a review rated q."""
    if q == 0:
        reps = 0
        interval = 0
    else:
        reps += 1
        if reps == 1:
            interval = 1
        elif reps == 2:
            interval = 6
        else:
            interval = max(1, round(interval * ease))

    ease = ease + (0.1 - (5 - q) * (0.08 + (5 - q) * 0.02))
    ease = max(MIN_EASE, ease)
    return reps, interval, ease


def is_due(card, today):
    if card["reps"] == 0 and card.get("due") is None:
        return True
    return card["due"] <= today


def path_key(p):
    return str(Path(p).resolve().relative_to(REPO_ROOT))


def cmd_today(args):
    state = load_state()
    today = args.date or today_str()
    topic = path_key(args.topic) if args.topic else None

    due = []
    for key, card in state["files"].items():
        if topic is not None and not key.startswith(topic):
            continue
        if is_due(card, today):
            due.append((key, card))

    if not due:
        print("No cards due. Review something else or take a break.")
        return 0

    due.sort(key=lambda kv: kv[1]["due"])
    current_topic = None
    for key, card in due:
        topic = str(Path(key).parent)
        if topic != current_topic:
            print(f"\n## {topic}")
            current_topic = topic
        overdue = ""
        if card["due"] < today:
            overdue = f"  (overdue { (date.fromisoformat(today) - date.fromisoformat(card['due'])).days }d)"
        print(f"  {Path(key).name}  [int {card['interval']}d | ease {card['ease']:.2f} | reps {card['reps']}]{overdue}")
    print(f"\n{len(due)} card(s) due.")
    return 0


def cmd_update(args):
    state = load_state()
    key = path_key(args.path)
    files = state["files"]

    q = RATINGS[args.rating]
    card = files.get(key)
    if card is None:
        card = {"reps": 0, "interval": 0, "ease": DEFAULT_EASE, "due": None,
                "last_reviewed": None, "history": []}
        files[key] = card

    today = args.date or today_str()
    reps, interval, ease = sm2(q, card["reps"], card["interval"], card["ease"])
    due = today if reps == 0 else (date.fromisoformat(today) + timedelta(days=interval)).isoformat()

    card["reps"] = reps
    card["interval"] = interval
    card["ease"] = round(ease, 3)
    card["due"] = due
    card["last_reviewed"] = today
    card["history"].append({"date": today, "rating": args.rating})

    save_state(state)

    next_label = "again today" if reps == 0 else f"{interval}d"
    print(f"{key}")
    print(f"  rated {args.rating} -> next review in {next_label} (due {due}) | ease {card['ease']}")
    return 0


def cmd_schedule(args):
    state = load_state()
    today = date.fromisoformat(args.date or today_str())

    per_topic = {}
    for key, card in state["files"].items():
        topic = str(Path(key).parent)
        per_topic.setdefault(topic, []).append((key, card))

    if not per_topic:
        print("Deck is empty. Use 'update' on your first note to seed it.")
        return 0

    rows = []
    for topic, cards in per_topic.items():
        min_due = min(c["due"] for _, c in cards if c["due"])
        days = (date.fromisoformat(min_due) - today).days
        rows.append((topic, min_due, days, len(cards)))

    rows.sort(key=lambda r: r[1])
    print("Topic                                  next due        in    cards")
    for topic, due, days, n in rows:
        print(f"{topic:<38} {due:<14} {days:>4}d  {n}")
    return 0


def cmd_stats(args):
    state = load_state()
    files = state["files"]
    if not files:
        print("Deck is empty.")
        return 0

    today = date.fromisoformat(args.date or today_str())
    due = sum(1 for c in files.values() if is_due(c, today.isoformat()))
    again = sum(1 for c in files.values() if c["reps"] == 0)
    young = sum(1 for c in files.values() if c["reps"] == 1)
    mature = sum(1 for c in files.values() if c["reps"] >= 2)
    avg_ease = sum(c["ease"] for c in files.values()) / len(files)
    total_reviews = sum(len(c["history"]) for c in files.values())

    print(f"cards:   {len(files)}")
    print(f"due:     {due}")
    print(f"learning (reps=0):  {again}")
    print(f"learning (reps=1):  {young}")
    print(f"mature (reps>=2):   {mature}")
    print(f"avg ease: {avg_ease:.3f}")
    print(f"total reviews: {total_reviews}")
    return 0


def main():
    parser = argparse.ArgumentParser(description="SM-2 spaced repetition engine")
    sub = parser.add_subparsers(dest="cmd", required=True)

    p_today = sub.add_parser("today", help="list cards due for review")
    p_today.add_argument("--topic", default=None, help="only cards under this dir")
    p_today.add_argument("--date", default=None, help="YYYY-MM-DD (default today)")

    p_update = sub.add_parser("update", help="record a rating for a card")
    p_update.add_argument("path", help="path to the .md note")
    p_update.add_argument("rating", choices=sorted(RATINGS))
    p_update.add_argument("--date", default=None, help="YYYY-MM-DD (default today)")

    p_sched = sub.add_parser("schedule", help="upcoming reviews per topic")
    p_sched.add_argument("--date", default=None)

    p_stats = sub.add_parser("stats", help="deck summary")
    p_stats.add_argument("--date", default=None)

    args = parser.parse_args()
    if args.cmd == "today":
        return cmd_today(args)
    if args.cmd == "update":
        return cmd_update(args)
    if args.cmd == "schedule":
        return cmd_schedule(args)
    if args.cmd == "stats":
        return cmd_stats(args)
    return 1


if __name__ == "__main__":
    sys.exit(main())
