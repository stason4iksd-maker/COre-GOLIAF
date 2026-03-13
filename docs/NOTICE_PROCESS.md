# NOTICE update process

1. Update `third_party/dependencies.yml` when dependency set changes.
2. Update `third_party/licenses_registry.yml` with license/linking/notice metadata.
3. Run locally:
   - `python3 scripts/validate_licenses.py`
   - `python3 scripts/update_notice.py`
4. Commit updated `NOTICE` alongside metadata changes.
5. Release pipeline re-runs both scripts and fails if `NOTICE` is outdated.

This guarantees NOTICE consistency and license-policy enforcement in every release.
