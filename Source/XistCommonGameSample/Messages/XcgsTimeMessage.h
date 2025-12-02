// Copyright (c) 2023 xist.gg

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
