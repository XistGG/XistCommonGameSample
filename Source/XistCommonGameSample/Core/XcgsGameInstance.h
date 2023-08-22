// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "XcgsGameInstance.generated.h"


/**
 * CommonGame Game Instance
 *
 * Must be configured in DefaultEngine.ini:
 *
 * [/Script/EngineSettings.GameMapsSettings]
 * GameInstanceClass=/Script/XistCommonGameSample.XcgsGameInstance
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:
	UXcgsGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
