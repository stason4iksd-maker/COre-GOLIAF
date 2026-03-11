# Third-Party Licenses and Linking Policy

## Dependency register

| dependency | license | static/dynamic link policy | notice requirements |
|---|---|---|---|
| SDL2 | Zlib | Dynamic preferred; static allowed | Include SDL copyright/license text in game docs or installer materials. |
| OpenAL Soft | LGPL-2.1-or-later | **Dynamic required** to avoid copyleft spillover into engine binaries. | Provide LGPL text, OpenAL Soft copyright notice, and user ability to relink/replace shared library. |
| stb | MIT | Static allowed | Preserve MIT notice in source and/or shipped legal notices. |
| libogg | BSD-3-Clause | Static or dynamic | Keep BSD-3-Clause copyright/conditions/disclaimer in distribution. |

## Audio middleware decision

**Selected option:** OpenAL Soft (LGPL-2.1-or-later) for runtime audio output.

### Legal implications
- OpenAL Soft is accepted only under **dynamic-linking** policy.
- Release artifacts must keep OpenAL Soft as a replaceable shared library (`.dll`/`.so`/`.dylib`).
- Product distribution must include:
  - LGPL v2.1+ license text,
  - OpenAL Soft attribution,
  - end-user instructions (or practical ability) to replace the library binary.
- Any direct modifications to OpenAL Soft itself must be published under LGPL terms.

## Engine-license compatibility check (MIT/BSD)

The engine may be distributed under MIT or BSD-family licenses. Compatibility review:

| component | component license | MIT engine | BSD engine | rationale |
|---|---|---|---|---|
| SDL2 | Zlib | Compatible | Compatible | Permissive; requires retention of notice only. |
| OpenAL Soft | LGPL-2.1-or-later | Compatible with dynamic linking policy | Compatible with dynamic linking policy | Copyleft obligations stay at library boundary when dynamically linked and replaceable. |
| stb | MIT | Compatible | Compatible | Same or similarly permissive requirements. |
| libogg | BSD-3-Clause | Compatible | Compatible | BSD terms are compatible with MIT/BSD engine distribution. |

## Governance

- Canonical machine-readable registry: `third_party/licenses_registry.yml`.
- Dependency list under audit: `third_party/dependencies.yml`.
- CI validation script: `scripts/validate_licenses.py`.
- NOTICE generation script: `scripts/update_notice.py`.
