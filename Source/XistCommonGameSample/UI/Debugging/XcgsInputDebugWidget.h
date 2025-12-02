// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "UI/XcgsActivatableWidget.h"
#include "XcgsInputDebugWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FXcgsOnActiveInputModeChanged);


/**
 * Input Debugging Widget
 *
 * The purpose of this widget is simply to help you understand exactly what input
 * settings are in effect at the current time.
 */
UCLASS()
class XISTCOMMONGAMESAMPLE_API UXcgsInputDebugWidget : public UXcgsActivatableWidget
{
	GENERATED_BODY()

public:
	UXcgsInputDebugWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~UCommonActivatableWidget interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	//~End of UCommonActivatableWidget interface

	/**
	 * The actual values for mouse capture state and mouse lock state are NOT available to BP,
	 * and rather than hack the Engine and Lyra to make them available, I'm just exposing
	 * text descriptions of their values here.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Get UI Input Config Data")
	void GetUIInputConfigData(FText& MouseCaptureModeText, FText& MouseLockModeText, bool& bIsCursorVisible, bool& bIsLookInputIgnored, bool& bIsMoveInputIgnored);

	/** Implement this in your Widget BP and update your widget values every time this event fires */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="On Active Input Mode Changed")
	void K2_OnActiveInputModeChanged();

	/** Called by the CommonUIActionRouterBase subsystem only when this widget is active */
	UFUNCTION()
	void NativeOnActiveInputModeChanged(ECommonInputMode NewInputMode) { K2_OnActiveInputModeChanged(); }

};
