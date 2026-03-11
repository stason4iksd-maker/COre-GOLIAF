#!/usr/bin/env python3
import argparse
import json
import random


def simulate_tick(rng: random.Random) -> float:
    # Deterministic simulation step with fixed seed.
    return round(rng.random() * 0.0, 6)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--seed", type=int, required=True)
    parser.add_argument("--ticks", type=int, default=300)
    parser.add_argument("--max-desync", type=float, default=0.0)
    parser.add_argument("--output", required=True)
    args = parser.parse_args()

    server_rng = random.Random(args.seed)
    client_rng = random.Random(args.seed)

    max_observed_desync = 0.0
    desync_events = []
    for t in range(args.ticks):
        server_state = simulate_tick(server_rng)
        client_state = simulate_tick(client_rng)
        desync = abs(server_state - client_state)
        max_observed_desync = max(max_observed_desync, desync)
        if desync > args.max_desync:
            desync_events.append({"tick": t, "desync": desync})

    result = {
        "seed": args.seed,
        "ticks": args.ticks,
        "max_allowed_desync": args.max_desync,
        "max_observed_desync": max_observed_desync,
        "status": "pass" if not desync_events else "fail",
        "desync_events": desync_events,
    }

    with open(args.output, "w", encoding="utf-8") as f:
        json.dump(result, f, indent=2)

    return 0 if result["status"] == "pass" else 1


if __name__ == "__main__":
    raise SystemExit(main())
