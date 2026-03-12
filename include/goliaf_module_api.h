#ifndef GOLIAF_MODULE_API_H
#define GOLIAF_MODULE_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * C ABI version for binary compatibility checks.
 */
#define GOLIAF_MODULE_ABI_MAGIC 0x474F4C49u /* "GOLI" */
#define GOLIAF_MODULE_ABI_MAJOR 1u
#define GOLIAF_MODULE_ABI_MINOR 0u

/** Opaque handles crossing the ABI boundary. */
typedef struct GoliafKernelContext GoliafKernelContext;
typedef struct GoliafModuleState GoliafModuleState;

/**
 * Interface version provided by a module.
 */
typedef struct GoliafModuleVersion {
  uint32_t magic;
  uint16_t major;
  uint16_t minor;
} GoliafModuleVersion;

/**
 * Module lifecycle callbacks.
 * Ownership rule: modules must not free kernel-owned resources,
 * and kernels must not free module-owned resources.
 */
typedef struct GoliafModuleApi {
  GoliafModuleVersion version;

  /**
   * Initializes module state. The returned state is owned by the module.
   */
  int (*Init)(GoliafKernelContext *kernel, GoliafModuleState **out_state);

  /**
   * Performs one update tick.
   */
  int (*Tick)(GoliafKernelContext *kernel, GoliafModuleState *state, double dt_seconds);

  /**
   * Releases module-owned state created by Init.
   */
  void (*Shutdown)(GoliafKernelContext *kernel, GoliafModuleState *state);
} GoliafModuleApi;

/**
 * Symbol exported by a dynamic module.
 */
#if defined(_WIN32)
#define GOLIAF_EXPORT __declspec(dllexport)
#else
#define GOLIAF_EXPORT __attribute__((visibility("default")))
#endif

GOLIAF_EXPORT const GoliafModuleApi *Goliaf_GetModuleApi(void);

#ifdef __cplusplus
}
#endif

#endif /* GOLIAF_MODULE_API_H */
