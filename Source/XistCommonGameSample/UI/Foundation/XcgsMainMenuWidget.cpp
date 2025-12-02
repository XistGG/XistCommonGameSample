// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsMainMenuWidget.h"

#include "CommonUIExtensions.h"
#include "XcgsGameplayTags.h"
#include "XcgsLog.h"
#include "Input/CommonUIInputTypes.h"


UXcgsMainMenuWidget::UXcgsMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UXcgsMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// This registers a "UI Action Binding" with CommonUI, such that when the UI_Action_MainMenu UI Action occurs,
	// the delegate is called which forwards the event to our own HandleMainMenuAction
	constexpr bool bShouldDisplayInActionBar = false;
	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(XcgsTag::UI_Action_MainMenu), bShouldDisplayInActionBar, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleMainMenuAction)));
}


void UXcgsMainMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	XCGS_LOG(TEXT("Pushing Empty widgets to lower layers to effectively disable their UI"));

	BlankGameWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), XcgsTag::UI_Layer_Game, BlankWidgetClass);
	BlankGameMenuWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetOwningLocalPlayer(), XcgsTag::UI_Layer_GameMenu, BlankWidgetClass);
}


void UXcgsMainMenuWidget::NativeOnDeactivated()
{
	XCGS_LOG(TEXT("Popping Empty widgets to lower layers to effectively re-enable their UI"));

	if (BlankGameWidget.IsValid())
	{
		UCommonUIExtensions::PopContentFromLayer(BlankGameWidget.Get());
		BlankGameWidget.Reset();
	}

	if (BlankGameMenuWidget.IsValid())
	{
		UCommonUIExtensions::PopContentFromLayer(BlankGameMenuWidget.Get());
		BlankGameMenuWidget.Reset();
	}

	Super::NativeOnDeactivated();
}


void UXcgsMainMenuWidget::HandleMainMenuAction()
{
	// When the player gives a "main menu" action while the main menu is open,
	// it means we need to close the main menu and return to game.
	DeactivateWidget();
}
