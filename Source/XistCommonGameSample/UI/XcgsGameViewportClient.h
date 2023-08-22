// Copyright (c) 2023 xist.gg

#pragma once


#include "CoreMinimal.h"
#include "CommonGameViewportClient.h"
#include "XcgsGameViewportClient.generated.h"


/**
 * CommonGame Game Viewport Client
 *
 * Must be configured in DefaultEngine.ini:
 * 
 * [/Script/Engine.Engine]
 * GameViewportClientClassName=/Script/XistCommonGameSample.XcgsGameViewportClient
 */
UCLASS()
class UXcgsGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()

public:
	UXcgsGameViewportClient(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
