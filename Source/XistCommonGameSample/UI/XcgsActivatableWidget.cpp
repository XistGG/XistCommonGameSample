// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsActivatableWidget.h"

#include "XcgsLog.h"

// Set Class Defaults
UXcgsActivatableWidget::UXcgsActivatableWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoActivate = true;

	bSetVisibilityOnActivated = true;
	bSetVisibilityOnDeactivated = true;
	ActivatedVisibility = ESlateVisibility::SelfHitTestInvisible;
	DeactivatedVisibility = ESlateVisibility::Collapsed;

	bSupportsActivationFocus = false;  // By default, DO NOT change input settings on each activation/deactivation
}

TOptional<FUIInputConfig> UXcgsActivatableWidget::GetDesiredInputConfig() const
{
	FUIInputConfig ConfigOverride;

	switch (InputMode)
	{
	case EXcgsWidgetInputMode::Game:
		ConfigOverride = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
		break;
	case EXcgsWidgetInputMode::GameAndMenu:
		ConfigOverride = FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringMouseDown);
		break;
	case EXcgsWidgetInputMode::Menu:
		ConfigOverride = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		break;
	case EXcgsWidgetInputMode::Default:
		// By default, no input change is desired, return an empty config
		return TOptional<FUIInputConfig>();
	default:
		checkf(false, TEXT("Unexpected InputMode value"));
	}

	return ConfigOverride;
}

void UXcgsActivatableWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (not IsDesignTime())
	{
		// If activatable widgets are supposed to be a specific visibility when not active, set that Visibility now
		if (not bAutoActivate
			&& not IsActivated()
			&& GetVisibility() != DeactivatedVisibility)
		{
			SetVisibility(DeactivatedVisibility);
		}
	}
}

void UXcgsActivatableWidget::NativeConstruct()
{
#if WITH_XCGS_DEBUG
	UE_LOG(LogXcgsUI, Verbose, TEXT("%hs: %s: Widget constructing (DesignTime?=%hi)"), __FUNCTION__, *GetClass()->GetName(), IsDesignTime());
#endif

	Super::NativeConstruct();
}

void UXcgsActivatableWidget::NativeDestruct()
{
#if WITH_XCGS_DEBUG
	UE_LOG(LogXcgsUI, Verbose, TEXT("%hs: %s: Widget destructing (DesignTime?=%hi)"), __FUNCTION__, *GetClass()->GetName(), IsDesignTime());
#endif

	Super::NativeDestruct();
}

void UXcgsActivatableWidget::NativeOnActivated()
{
#if WITH_XCGS_DEBUG
	UE_LOG(LogXcgsUI, Verbose, TEXT("%hs: %s: Widget Activating"), __FUNCTION__, *GetClass()->GetName());
#endif

	Super::NativeOnActivated();
}

void UXcgsActivatableWidget::NativeOnDeactivated()
{
#if WITH_XCGS_DEBUG
	UE_LOG(LogXcgsUI, Verbose, TEXT("%hs: %s: Widget Deactivating"), __FUNCTION__, *GetClass()->GetName());
#endif

	Super::NativeOnDeactivated();
}

UGameViewportClient* UXcgsActivatableWidget::GetViewportClient() const
{
	UGameViewportClient* ViewportClient{ nullptr };
	if (const APlayerController* PC = GetOwningPlayer<APlayerController>())
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			ViewportClient = LocalPlayer->ViewportClient;
		}
	}
	return ViewportClient;
}
