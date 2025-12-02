// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "CommonActivatableWidget.h"
#include "XcgsActivatableWidget.generated.h"

/**
 * EXcgsWidgetInputMode
 * 
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
 * UXcgsActivatableWidget
 *
 * An activatable widget that optionally overrides the input mode when activated
 */
UCLASS(Abstract, Blueprintable, meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	// Set Class Defaults
	UXcgsActivatableWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~Begin UUserWidget interface
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//~End UUserWidget interface

	//~Begin UCommonActivatableWidget interface
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~End UCommonActivatableWidget interface

	/** @return the ViewportClient of this widget's owning player */
	UGameViewportClient* GetViewportClient() const;

protected:
	/**
	 * The desired input mode to use while this UI is activated
	 *
	 * When EXcgsWidgetInputMode::Default, NO CHANGES are made to input settings upon Activation of this widget.
	 */
	UPROPERTY(EditDefaultsOnly, Category=Input)
	EXcgsWidgetInputMode InputMode = EXcgsWidgetInputMode::Default;
};
