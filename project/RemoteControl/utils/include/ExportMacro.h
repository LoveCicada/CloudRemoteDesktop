#pragma once

#if WIN32
#if defined(RTC_SHARED_LIBRARY)
#define RTC_EXPORT __declspec(dllexport)
#else
#define RTC_EXPORT __declspec(dllimport)
#endif
#else
#if __has_attribute(visibility) && defined(RTC_SHARED_LIBRARY)
#define RTC_EXPORT __attribute__((visibility("default")))
#endif
#endif

#ifndef RTC_EXPORT
#define RTC_EXPORT
#endif