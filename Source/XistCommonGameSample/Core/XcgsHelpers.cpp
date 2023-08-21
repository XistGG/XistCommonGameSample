// Copyright (c) 2023 xist.gg

#include "XcgsHelpers.h"

#include "EnhancedInputSubsystems.h"
#include "XcgsLog.h"


UEnhancedInputLocalPlayerSubsystem* UXcgsHelpers::GetEnhancedInputLocalPlayerSubsystem(const APlayerController* PlayerController)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem {nullptr};

	if (IsValid(PlayerController))
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		}
	}

	return Subsystem;
}


// This allows Blueprints to send messages to the usual error log stream
void UXcgsHelpers::XcgsErrorLog(UObject* LogObject, FString LogMessage)
{
	XCGS_ERROR_LOG(TEXT("Error: [%s]: %s"), *GetNameSafe(LogObject), *LogMessage);
}


// This allows Blueprints to send messages to the usual warning log stream
void UXcgsHelpers::XcgsWarningLog(UObject* LogObject, FString LogMessage)
{
	XCGS_WARNING_LOG(TEXT("Warning: [%s]: %s"), *GetNameSafe(LogObject), *LogMessage);
}


// This allows Blueprints to send messages to the usual log stream
void UXcgsHelpers::XcgsLog(UObject* LogObject, FString LogMessage)
{
	XCGS_LOG(TEXT("[%s]: %s"), *GetNameSafe(LogObject), *LogMessage);
}


// This allows Blueprints to send messages to the usual display log stream
void UXcgsHelpers::XcgsDisplayLog(UObject* LogObject, FString LogMessage)
{
	XCGS_DISPLAY_LOG(TEXT("[%s]: %s"), *GetNameSafe(LogObject), *LogMessage);
}
