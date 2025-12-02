// Copyright (c) 2023 xist.gg

#pragma once

#include "CommonActivatableWidget.h"
#include "XcgsActivatableWidget.generated.h"


/**
 * Input Modes that XcgsActivatableWidgets can activate
 */
UENUM(BlueprintType)
enum class EXcgsWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};


/**
 * Activatable Widget
 *
 * An activatable widget that optionally overrides the input mode when activated
 */
UCLASS(Abstract, Blueprintable, meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UXcgsActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End of UCommonActivatableWidget interface

protected:
	/** The desired input mode to use while this UI is activated, for example do you want key presses to still reach the game/player controller? */
	UPROPERTY(EditDefaultsOnly, Category=Input)
	EXcgsWidgetInputMode InputMode = EXcgsWidgetInputMode::Default;

};
