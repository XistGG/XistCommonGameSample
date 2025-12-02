// Copyright (c) 2023 xist.gg

#pragma once

#include "ModularGameState.h"
#include "XcgsGameState.generated.h"


/**
 * Modular Game State
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsGameState : public AModularGameStateBase
{
	GENERATED_BODY()

public:
	AXcgsGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * Call this method to Pause the Game Time
	 * @return True if game is now paused, False if error Pausing
	 */
	UFUNCTION(BlueprintCallable)
	bool PauseGameTime();

	/**
	 * Call this method to Unpause the Game Time
	 * @return True if game is now unpaused, False if error Unpausing
	 */
	UFUNCTION(BlueprintCallable)
	bool UnpauseGameTime();

};
