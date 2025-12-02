// Copyright (c) 2023 xist.gg

#include "XcgsInputDebugWidget.h"
#include "Engine/GameViewportClient.h"
#include "Input/CommonUIActionRouterBase.h"


UXcgsInputDebugWidget::UXcgsInputDebugWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoActivate = true;
}


void UXcgsInputDebugWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	// Register for OnActiveInputModeChanged events
	if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
	{
		if (UCommonUIActionRouterBase* ActionRouter = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
		{
			ActionRouter->OnActiveInputModeChanged().AddUObject(this, &ThisClass::NativeOnActiveInputModeChanged);
		}
	}

	// Simulate that input mode has changed when this widget is activated
	K2_OnActiveInputModeChanged();
}


void UXcgsInputDebugWidget::NativeOnDeactivated()
{
	// Unregister for OnActiveInputModeChanged events
	if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
	{
		if (UCommonUIActionRouterBase* ActionRouter = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
		{
			ActionRouter->OnActiveInputModeChanged().RemoveAll(this);
		}
	}

	Super::NativeOnDeactivated();
}


void UXcgsInputDebugWidget::GetUIInputConfigData(FText& MouseCaptureModeText, FText& MouseLockModeText, bool& bIsCursorVisible, bool& bIsLookInputIgnored, bool& bIsMoveInputIgnored)
{
	// Initialize outputs as empty

	MouseCaptureModeText = FText::FromString(TEXT("n/a"));
	MouseLockModeText = FText::FromString(TEXT("n/a"));

	bIsCursorVisible = bIsLookInputIgnored = bIsMoveInputIgnored = false;

	// Populate outputs if possible

	if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
	{
		APlayerController* PC = LocalPlayer->GetPlayerController(GetWorld());
		UGameViewportClient* GameViewportClient = LocalPlayer->ViewportClient;

		if (PC)
		{
			bIsCursorVisible = PC->ShouldShowMouseCursor();
			bIsLookInputIgnored = PC->IsLookInputIgnored();
			bIsMoveInputIgnored = PC->IsMoveInputIgnored();
		}

		if (GameViewportClient)
		{
			switch (const EMouseCaptureMode MouseCaptureMode = GameViewportClient->GetMouseCaptureMode())
			{
			case EMouseCaptureMode::CapturePermanently:
				MouseCaptureModeText = FText::FromString(TEXT("CapPerm"));
				break;
			case EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown:
				MouseCaptureModeText = FText::FromString(TEXT("CapPermInit"));
				break;
			case EMouseCaptureMode::CaptureDuringMouseDown:
				MouseCaptureModeText = FText::FromString(TEXT("CapDuringMD"));
				break;
			case EMouseCaptureMode::CaptureDuringRightMouseDown:
				MouseCaptureModeText = FText::FromString(TEXT("CapDurRMDOnly"));
				break;
			case EMouseCaptureMode::NoCapture:
				MouseCaptureModeText = FText::FromString(TEXT("NoCap"));
				break;
			default:
				MouseCaptureModeText = FText::FromString(TEXT("UNKNOWN"));
				break;
			}

			if (GameViewportClient->ShouldAlwaysLockMouse())
			{
				MouseLockModeText = FText::FromString(TEXT("Always"));
			}
			else if (GameViewportClient->LockDuringCapture())
			{
				MouseLockModeText = FText::FromString(TEXT("DurCap"));
			}
			else
			{
				MouseLockModeText = FText::FromString(TEXT("NoLock"));
			}
		}
	}
}