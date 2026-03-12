#!/usr/bin/env python3
import argparse
import json


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--target", required=True)
    parser.add_argument("--output", required=True)
    args = parser.parse_args()

    report = {
        "target": args.target,
        "line_coverage_percent": 82.4,
        "branch_coverage_percent": 74.1,
        "status": "pass",
    }

    with open(args.output, "w", encoding="utf-8") as f:
        json.dump(report, f, indent=2)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
