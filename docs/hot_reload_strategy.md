# Hot-reload strategy (MVP)

## 1) ABI boundary: C-compatible API

The runtime boundary for hot-swappable modules is fixed to a C ABI:
- exported symbol: `Goliaf_GetModuleApi`
- lifecycle callbacks: `Init`, `Tick`, `Shutdown`
- opaque handles only (`GoliafKernelContext`, `GoliafModuleState`)

This keeps binary coupling low and avoids C++ ABI instability.

## 2) Ownership constraints across the boundary

Ownership of resources is never shared across kernel/module boundary:
- module-owned: memory/state allocated in module `Init` and released in module `Shutdown`
- kernel-owned: engine services/resources exposed through `GoliafKernelContext`

Both sides may *reference* foreign resources, but must not deallocate them.

## 3) Interface versioning and compatibility checks

Every module publishes `GoliafModuleVersion { magic, major, minor }`.
Loader checks:
- `magic` must match `GOLIAF_MODULE_ABI_MAGIC`
- `major` must match the loader major ABI
- callback pointers must be non-null

Minor version differences are accepted for backward-compatible changes.

## 4) MVP scope for hot-reload

Hot-reload rollout order:
1. shaders
2. scripts
3. asset data

C++ code hot-reload is explicitly deferred to a post-MVP milestone.

## 5) Fail-safe and rollback scenarios

Safe reload pipeline:
1. keep active module running
2. load candidate module in isolation
3. validate ABI + callbacks
4. run candidate `Init`
5. switch active pointer only if all checks succeed

On any failure, candidate is discarded and previous module continues running
without service interruption.
