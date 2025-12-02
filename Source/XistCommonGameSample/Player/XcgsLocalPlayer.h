// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

#include "CommonLocalPlayer.h"
#include "XcgsLocalPlayer.generated.h"


/**
 * CommonGame LocalPlayer
 *
 * Must be configured in DefaultEngine.ini:
 * 
 * [/Script/Engine.Engine]
 * LocalPlayerClassName=/Script/XistCommonGameSample.XcgsLocalPlayer
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsLocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:
	UXcgsLocalPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
