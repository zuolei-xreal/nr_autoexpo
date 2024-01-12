#pragma once

//
// native plugin API
//
#include <stdint.h>
#if defined(__CYGWIN32__) || defined(_WIN32)
#define NR_INTERFACE_API __cdecl
#define NR_INTERFACE_EXPORT __declspec(dllexport)
#if defined(NR_INTERFACE_DEPRECATION_SUPPRESS)
#define NR_INTERFACE_DEPRECATED(__msg__)
#else
#define NR_INTERFACE_DEPRECATED(__msg__) __declspec(deprecated(__msg__))
#endif
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
#define NR_INTERFACE_API
#define NR_INTERFACE_EXPORT __attribute__((visibility("default")))
#if defined(NR_INTERFACE_DEPRECATION_SUPPRESS)
#define NR_INTERFACE_DEPRECATED(__msg__)
#else
#define NR_INTERFACE_DEPRECATED(__msg__) __attribute__((deprecated(__msg__)))
#endif
#else
#define NR_INTERFACE_API
#define NR_INTERFACE_EXPORT
#define NR_INTERFACE_DEPRECATED(__msg__)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void NR_INTERFACE_EXPORT NR_INTERFACE_API NRExposurePredict(unsigned char *InputData0, uint16_t *i_time, uint16_t *i_gain, uint16_t i_width,
                                                                uint16_t i_height, uint16_t i_step);

#ifdef __cplusplus
}
#endif
