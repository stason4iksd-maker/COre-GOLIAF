#include "dev/editor/Editor.h"

#include "core/Logger.h"

namespace core_goliaf::dev {

void Editor::initialize() const {
    core::Logger::info("Dev", "Editor shell initialized (Dear ImGui integration point)");
    core::Logger::info("Dev", "Scene hierarchy panel ready (stub)");
    core::Logger::info("Dev", "Inspector panel ready (stub)");
    core::Logger::info("Dev", "Asset browser ready (stub)");
}

} // namespace core_goliaf::dev
