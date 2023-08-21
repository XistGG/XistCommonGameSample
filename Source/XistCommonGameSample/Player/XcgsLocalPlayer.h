// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "XcgsLocalPlayer.generated.h"


/**
 * CommonGame LocalPlayer
 *
 * @see DefaultEngine.ini where this class is configured to be used as the ULocalPlayer in [/Script/Engine.Engine] LocalPlayerClassName=/Script/XistCommonGameSample.XcgsLocalPlayer
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsLocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:
	UXcgsLocalPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
