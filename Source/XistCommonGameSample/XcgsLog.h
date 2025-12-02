// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "Logging/LogMacros.h"


class UObject;


DECLARE_LOG_CATEGORY_EXTERN(LogXcgs, Log, All);


FString XcgsGetClientServerContextString(UObject* ContextObject = nullptr);


#define BOOL2TEXT(b)  (b) ? *TrueString : *FalseString

EXTERN_C const FString FalseString;
EXTERN_C const FString TrueString;


/**
 * Write a log of the specified level to the LogXcgs log
 * @param Level UE_LOG Level
 * @param fmt FString::Printf format string
 */
#define XCGS_LEVEL_LOG(Level, fmt, ...) \
        UE_LOG(LogXcgs, Level, TEXT("%s"), \
            *FString::Printf(TEXT("%05llu %s:%i %s"), \
            GFrameCounter, *FString(__FUNCTION__), __LINE__, \
            *FString::Printf(fmt, ##__VA_ARGS__)))


#define XCGS_LOG(fmt, ...)             XCGS_LEVEL_LOG(Log, fmt, ##__VA_ARGS__)
#define XCGS_DISPLAY_LOG(fmt, ...)     XCGS_LEVEL_LOG(Display, fmt, ##__VA_ARGS__)
#define XCGS_ERROR_LOG(fmt, ...)       XCGS_LEVEL_LOG(Error, fmt, ##__VA_ARGS__)
#define XCGS_WARNING_LOG(fmt, ...)     XCGS_LEVEL_LOG(Warning, fmt, ##__VA_ARGS__)
#define XCGS_VERBOSE_LOG(fmt, ...)     XCGS_LEVEL_LOG(Verbose, fmt, ##__VA_ARGS__)


#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
#define XCGS_DEBUG_LOG(fmt, ...)       XCGS_LEVEL_LOG(VeryVerbose, fmt, ##__VA_ARGS__)
#else
#define XCGS_DEBUG_LOG(fmt, ...)       {}
#endif
