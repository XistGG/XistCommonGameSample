// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "XcgsHelpers.generated.h"


class UEnhancedInputLocalPlayerSubsystem;


UCLASS()
class XISTCOMMONGAMESAMPLE_API UXcgsHelpers : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UXcgsHelpers() {}

    /**
     * Get the EnhancedInput LocalPlayer Subsystem for the player represented by PlayerController
     * @param PlayerController
     * @return nullptr, or if available, the EnhancedInput LocalPlayer Subsystem for the player
     */
    UFUNCTION(BlueprintCallable)
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(const APlayerController* PlayerController);

	/** Used by BP (LogObject) to log the message LogMessage to the Error log */
	UFUNCTION(BlueprintCallable)
	static void XcgsErrorLog(UObject* LogObject, FString LogMessage);

	/** Used by BP (LogObject) to log the message LogMessage to the Warning log */
	UFUNCTION(BlueprintCallable)
	static void XcgsWarningLog(UObject* LogObject, FString LogMessage);

	/** Used by BP (LogObject) to log the message LogMessage to the Log */
	UFUNCTION(BlueprintCallable)
	static void XcgsLog(UObject* LogObject, FString LogMessage);

	/** Used by BP (LogObject) to log the message LogMessage to the Display log */
	UFUNCTION(BlueprintCallable)
	static void XcgsDisplayLog(UObject* LogObject, FString LogMessage);

};
