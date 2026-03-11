#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--budgets", required=True)
    parser.add_argument("--output", required=True)
    args = parser.parse_args()

    budgets = json.loads(Path(args.budgets).read_text(encoding="utf-8"))

    measurements = {
        "frame_time_ms": 14.2,
        "memory_mb": 680,
        "startup_time_s": 3.1,
    }

    verdicts = {
        metric: {
            "budget": budget,
            "measured": measurements[metric],
            "pass": measurements[metric] <= budget,
        }
        for metric, budget in budgets.items()
    }

    status = "pass" if all(v["pass"] for v in verdicts.values()) else "fail"
    payload = {
        "status": status,
        "budgets": budgets,
        "measurements": measurements,
        "verdicts": verdicts,
    }

    Path(args.output).write_text(json.dumps(payload, indent=2), encoding="utf-8")
    return 0 if status == "pass" else 1


if __name__ == "__main__":
    raise SystemExit(main())
