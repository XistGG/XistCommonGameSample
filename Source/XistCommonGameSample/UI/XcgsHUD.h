// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "XcgsHUD.generated.h"


/**
 * Modular HUD
 *
 * ModularGameplayActors does not provide a HUD, so we implement it here.
 */
UCLASS(meta=(DisplayName="Xcgs HUD", Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AXcgsHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

};
