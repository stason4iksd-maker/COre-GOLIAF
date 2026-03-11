#include "goliaf_module_api.h"

#include <stddef.h>

typedef struct LoadedModule {
  const GoliafModuleApi *api;
  GoliafModuleState *state;
} LoadedModule;

static int Goliaf_IsCompatible(const GoliafModuleApi *api) {
  if (api == NULL) {
    return 0;
  }
  if (api->version.magic != GOLIAF_MODULE_ABI_MAGIC) {
    return 0;
  }
  if (api->version.major != GOLIAF_MODULE_ABI_MAJOR) {
    return 0;
  }
  return 1;
}

/**
 * Fail-safe reload pattern:
 * 1) keep current module active,
 * 2) load and validate candidate,
 * 3) init candidate state,
 * 4) switch pointer only on success,
 * 5) otherwise keep old module untouched.
 */
int Goliaf_ReloadModuleSafely(GoliafKernelContext *kernel,
                              LoadedModule *active,
                              const GoliafModuleApi *candidate_api) {
  GoliafModuleState *candidate_state = NULL;

  if (!Goliaf_IsCompatible(candidate_api)) {
    return -1;
  }

  if (candidate_api->Init == NULL || candidate_api->Tick == NULL ||
      candidate_api->Shutdown == NULL) {
    return -2;
  }

  if (candidate_api->Init(kernel, &candidate_state) != 0) {
    return -3;
  }

  if (active != NULL && active->api != NULL && active->api->Shutdown != NULL &&
      active->state != NULL) {
    active->api->Shutdown(kernel, active->state);
  }

  if (active != NULL) {
    active->api = candidate_api;
    active->state = candidate_state;
  }

  return 0;
}
