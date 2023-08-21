// Copyright (c) 2023 xist.gg

#include "XcgsActivatableWidget.h"


UXcgsActivatableWidget::UXcgsActivatableWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
	default:
		// By default, no input change is desired, return an empty config
		return TOptional<FUIInputConfig>();
	}

	return ConfigOverride;
}
