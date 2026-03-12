#!/usr/bin/env python3
from __future__ import annotations

import sys
from pathlib import Path

import yaml


def load_yaml(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as fh:
        return yaml.safe_load(fh)


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    registry = load_yaml(root / "third_party" / "licenses_registry.yml")
    deps_file = load_yaml(root / "third_party" / "dependencies.yml")

    engine_license = deps_file["engine"]["selected_license"]
    accepted_engine_licenses = set(registry["engine_license_policy"]["accepted_engine_licenses"])
    if engine_license not in accepted_engine_licenses:
        print(f"ERROR: unsupported engine license '{engine_license}'.")
        return 1

    component_map = {c["dependency"]: c for c in registry["components"]}
    allow_list = set(registry["engine_license_policy"]["compatibility_rules"][engine_license]["allow"])

    errors: list[str] = []
    for dep in deps_file["dependencies"]:
        name = dep["name"]
        if name not in component_map:
            errors.append(f"Dependency '{name}' is not present in licenses_registry.yml")
            continue

        component_license = component_map[name]["license"]
        if component_license not in allow_list:
            errors.append(
                f"Dependency '{name}' uses '{component_license}', not allowed for engine license '{engine_license}'"
            )

    if errors:
        for err in errors:
            print(f"ERROR: {err}")
        return 1

    print("License validation passed.")
    print(f"Engine license: {engine_license}")
    for dep in deps_file["dependencies"]:
        comp = component_map[dep["name"]]
        print(f"- {dep['name']}: {comp['license']} ({comp['linking']})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
