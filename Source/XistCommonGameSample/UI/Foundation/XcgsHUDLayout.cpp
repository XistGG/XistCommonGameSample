// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsHUDLayout.h"

#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"
#include "XcgsGameplayTags.h"


UXcgsHUDLayout::UXcgsHUDLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UXcgsHUDLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
	// the delegate is called which forwards the event to our own HandleMainMenuAction
	constexpr bool bShouldDisplayInActionBar = false;
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(XcgsTag::UI_Action_MainMenu), bShouldDisplayInActionBar, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleMainMenuAction)));
}


void UXcgsHUDLayout::HandleMainMenuAction()
{
	if (ensure(!MainMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), XcgsTag::UI_Layer_Menu, MainMenuClass);
	}
}
