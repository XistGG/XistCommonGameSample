// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

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
	// Set Class Defaults
	UXcgsHUDLayout(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//~End UUserWidget interface

protected:
	/** Callback called whenever the player gives the "Show Main Menu" input */
	void HandleMainMenuAction();

	/** Class to use as the Main Menu for this HUD Layout */
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UXcgsActivatableWidget> MainMenuClass;

private:
	FUIActionBindingHandle MenuActionHandle;
};
