// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "CommonButtonBase.h"
#include "UObject/Object.h"
#include "XcgsButtonBase.generated.h"


/**
 * CommonUI ButtonBase
 *
 * There is quite a bit of Blueprint related work also required in addition
 * to this base C++.
 *
 * For more implementation details, in UEditor view this Blueprint:
 * @see /Content/UI/Foundation/Buttons/B_XcgsButton.uasset
 *
 * The B_XcgxButtonBase blueprint should be what you really use as your
 * base button class in your project, not this C++ base which isn't
 * fully functional without the widget integration.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class XISTCOMMONGAMESAMPLE_API UXcgsButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FText& InText);

protected:
	//~UUserWidget interface
	virtual void NativePreConstruct() override;
	//~End of UUserWidget interface

	//~UCommonButtonBase interface
	virtual void UpdateInputActionWidget() override;
	virtual void OnInputMethodChanged(ECommonInputType CurrentInputType) override;
	//~End of UCommonButtonBase interface

	void RefreshButtonText();

	/**
	 * You must implement this event in BP to change the widget's button text to InText
	 * @param InText 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonStyle();

private:
	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	uint8 bOverride_ButtonText : 1;

	UPROPERTY(EditAnywhere, Category="Button", meta=( editcondition="bOverride_ButtonText" ))
	FText ButtonText;
};
