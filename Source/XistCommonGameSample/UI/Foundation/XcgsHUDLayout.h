// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "UI/XcgsActivatableWidget.h"
#include "XcgsHUDLayout.generated.h"


/**
 * HUD Layout
 */
UCLASS(Abstract, BlueprintType, Blueprintable, meta=(DisplayName="Xcgs HUD Layout", Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsHUDLayout : public UXcgsActivatableWidget
{
	GENERATED_BODY()

public:
	UXcgsHUDLayout(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UUserWidget interface
	virtual void NativeOnInitialized() override;
	//~End of UUserWidget interface

protected:
	/** Callback called whenever the player gives the "Show Main Menu" input */
	void HandleMainMenuAction();

	/** Class to use as the Main Menu for this HUD Layout */
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UXcgsActivatableWidget> MainMenuClass;

};
