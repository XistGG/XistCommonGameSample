// Copyright (c) 2023 xist.gg

#include "XcgsGameState.h"

#include "XcgsGameplayTags.h"
#include "Engine/World.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Messages/XcgsTimeMessage.h"


AXcgsGameState::AXcgsGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


bool AXcgsGameState::PauseGameTime()
{
	bool bError {false};
	if (!GetWorld()->IsPaused())
	{
		bError = ! GetWorld()->GetFirstPlayerController()->SetPause(true);
		if (!bError)
		{
			// Broadcast a Gameplay Message, game is now paused

			FXcgsTimeMessage Message;
			Message.Verb = XcgsTag::Event_Time_Message_Paused;
			Message.TimeSinceChanged = -1.f;  // TODO if you care about this info...

			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
			MessageSubsystem.BroadcastMessage(XcgsTag::Event_Time_Message, Message);
		}
	}
	return !bError;
}


bool AXcgsGameState::UnpauseGameTime()
{
	bool bError {false};
	if (GetWorld()->IsPaused())
	{
		bError = ! GetWorld()->GetFirstPlayerController()->SetPause(false);
		if (!bError)
		{
			// Broadcast a Gameplay Message, game is now Unpaused

			FXcgsTimeMessage Message;
			Message.Verb = XcgsTag::Event_Time_Message_Unpaused;
			Message.TimeSinceChanged = -1.f;  // TODO if you care about this info...

			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
			MessageSubsystem.BroadcastMessage(XcgsTag::Event_Time_Message, Message);
		}
	}
	return !bError;
}
