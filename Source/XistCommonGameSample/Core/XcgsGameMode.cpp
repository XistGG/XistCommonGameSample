// Copyright (c) 2023 xist.gg

#include "XcgsGameMode.h"

#include "XcgsGameState.h"
#include "Player/XcgsPlayerController.h"
#include "Player/XcgsPlayerPawn.h"
#include "UI/XcgsHUD.h"


AXcgsGameMode::AXcgsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AXcgsGameState::StaticClass();
	PlayerControllerClass = AXcgsPlayerController::StaticClass();
	DefaultPawnClass = AXcgsPlayerPawn::StaticClass();
	HUDClass = AXcgsHUD::StaticClass();
}


void AXcgsGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}


void AXcgsGameMode::InitGameState()
{
	Super::InitGameState();
}
