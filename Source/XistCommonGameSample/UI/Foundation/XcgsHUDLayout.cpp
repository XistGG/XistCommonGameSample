// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsHUDLayout.h"

#include "CommonUIExtensions.h"
#include "Input/CommonUIInputTypes.h"
#include "XcgsGameplayTags.h"

// Set Class Defaults
UXcgsHUDLayout::UXcgsHUDLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoActivate = true;

	// Change to GameAndMenu input mode when this widget is activated
	bSupportsActivationFocus = true;
	InputMode = EXcgsWidgetInputMode::GameAndMenu;
}

void UXcgsHUDLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (not IsDesignTime())
	{
		// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
		// the delegate is called which forwards the event to our own HandleMainMenuAction
		const auto ActionTag = FUIActionTag::ConvertChecked(XcgsTag::UI_Action_MainMenu);
		const auto Delegate = FSimpleDelegate::CreateUObject(this, &ThisClass::HandleMainMenuAction);
		constexpr bool bShouldDisplayInActionBar = false;
		MenuActionHandle = RegisterUIActionBinding(FBindUIActionArgs(ActionTag, bShouldDisplayInActionBar, Delegate));
	}
}

void UXcgsHUDLayout::NativeDestruct()
{
	if (MenuActionHandle.IsValid())
	{
		MenuActionHandle.Unregister();
	}

	Super::NativeDestruct();
}

void UXcgsHUDLayout::HandleMainMenuAction()
{
	if (ensureMsgf(not MainMenuClass.IsNull(),
		TEXT("%hs: You must configure MainMenuClass"), __FUNCTION__))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), XcgsTag::UI_Layer_Menu, MainMenuClass);
	}
}
