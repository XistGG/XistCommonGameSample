// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "ModularPawn.h"
#include "XcgsPawn.generated.h"


/**
 * Modular Pawn
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsPawn : public AModularPawn
{
	GENERATED_BODY()

public:
	AXcgsPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
