// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsGameViewportClient.h"

#include "CommonUISettings.h"
#include "ICommonUIModule.h"


namespace GameViewportTags
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Platform_Trait_Input_HardwareCursor, "Platform.Trait.Input.HardwareCursor");
}


UXcgsGameViewportClient::UXcgsGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UXcgsGameViewportClient::Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	// We have software cursors set up in our project settings for console/mobile use, but on desktop
	// native hardware cursors are preferred.
	const bool bUseHardwareCursor = ICommonUIModule::GetSettings().GetPlatformTraits().HasTag(GameViewportTags::TAG_Platform_Trait_Input_HardwareCursor);
	SetUseSoftwareCursorWidgets(!bUseHardwareCursor);
}
