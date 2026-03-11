#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

import yaml


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    registry_path = root / "third_party" / "licenses_registry.yml"
    template_path = root / "legal" / "NOTICE.template"
    notice_path = root / "NOTICE"

    registry = yaml.safe_load(registry_path.read_text(encoding="utf-8"))
    template = template_path.read_text(encoding="utf-8")

    rows: list[str] = []
    for component in registry["components"]:
        rows.append(f"\n- {component['dependency']} ({component['license']})")
        rows.append(f"  Notice: {component['notices']}")

    output = template.replace("{{COMPONENT_LIST}}", "\n".join(rows).lstrip("\n"))
    notice_path.write_text(output + "\n", encoding="utf-8")
    print(f"Updated {notice_path.relative_to(root)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
