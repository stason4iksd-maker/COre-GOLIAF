# Architecture Rules

- **Layering**: `app -> core -> subsystems(render/editor/ecs/network/assets/scripting)` without reverse dependencies.
- **Data ownership**: ECS owns runtime game state; renderer and networking consume immutable snapshots.
- **Module boundaries**: each subsystem has `include/<module>` public API and `src/<module>` implementation.
- **Determinism**: simulation and replication paths must be seed-driven and replayable.
- **Build targets**:
  - `Dev.exe`: editor-only tooling + viewport + gizmos.
  - `Player.exe`: runtime ECS + Lua hot reload + scene/component loading.
  - `LanServer.exe`: headless networking + replication.
- **Scalability**: every new feature enters via a subsystem interface and adds tests at module boundary.
- **No stubs in production path**: placeholder modules like `RendererStub`, `PhysicsStub`, `AudioStub` are forbidden.
