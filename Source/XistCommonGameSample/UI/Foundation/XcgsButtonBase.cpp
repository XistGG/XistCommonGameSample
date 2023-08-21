// Copyright (c) 2023 xist.gg

#include "XcgsButtonBase.h"

#include "CommonActionWidget.h"


void UXcgsButtonBase::SetButtonText(const FText& InText)
{
	bOverride_ButtonText = InText.IsEmpty();
	ButtonText = InText;
	RefreshButtonText();
}


void UXcgsButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateButtonStyle();
	RefreshButtonText();
}


void UXcgsButtonBase::UpdateInputActionWidget()
{
	Super::UpdateInputActionWidget();

	UpdateButtonStyle();
	RefreshButtonText();
}


void UXcgsButtonBase::RefreshButtonText()
{
	if (bOverride_ButtonText || ButtonText.IsEmpty())
	{
		if (InputActionWidget)
		{
			const FText ActionDisplayText = InputActionWidget->GetDisplayText();	
			if (!ActionDisplayText.IsEmpty())
			{
				UpdateButtonText(ActionDisplayText);
				return;
			}
		}
	}

	UpdateButtonText(ButtonText);
}


void UXcgsButtonBase::OnInputMethodChanged(ECommonInputType CurrentInputType)
{
	Super::OnInputMethodChanged(CurrentInputType);

	UpdateButtonStyle();
}
