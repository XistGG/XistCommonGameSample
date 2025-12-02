// Copyright (c) 2023-2025 Xist.GG LLC

#pragma once

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
