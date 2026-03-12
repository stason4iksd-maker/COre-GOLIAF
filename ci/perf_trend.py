#!/usr/bin/env python3
import argparse
import json
from datetime import datetime, timezone
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--perf-input", required=True)
    parser.add_argument("--output", required=True)
    args = parser.parse_args()

    perf = json.loads(Path(args.perf_input).read_text(encoding="utf-8"))
    trend = {
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "current": perf["measurements"],
        "status": perf["status"],
        "trend_note": "Persist artifact history in CI storage to compute long-term trend.",
    }

    Path(args.output).write_text(json.dumps(trend, indent=2), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
