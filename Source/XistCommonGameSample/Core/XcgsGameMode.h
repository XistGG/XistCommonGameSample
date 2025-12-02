// Copyright (c) 2023 xist.gg

#pragma once

#include "ModularGameMode.h"
#include "XcgsGameMode.generated.h"


/**
 * Modular Game Mode
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsGameMode : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	AXcgsGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	//~End of AGameModeBase interface

};
