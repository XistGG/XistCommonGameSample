// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "GameplayTagContainer.h"
#include "XcgsTimeMessage.generated.h"


/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct XISTCOMMONGAMESAMPLE_API FXcgsTimeMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag Verb;

	UPROPERTY(BlueprintReadWrite)
	float TimeSinceChanged {-1.f};

};
