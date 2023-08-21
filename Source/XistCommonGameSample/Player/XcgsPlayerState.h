// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "XcgsPlayerState.generated.h"


/**
 * Modular PlayerState
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsPlayerState : public AModularPlayerState
{
	GENERATED_BODY()

public:
	AXcgsPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
