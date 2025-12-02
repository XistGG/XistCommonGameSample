// Copyright (c) 2023 xist.gg

#pragma once

#include "GameUIManagerSubsystem.h"
#include "Containers/Ticker.h"
#include "XcgsUIManagerSubsystem.generated.h"


/**
 * Game UI Manager Subsystem
 */
UCLASS(meta=(DisplayName="Xcgs UI Manager Subsystem", Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API UXcgsUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:
	UXcgsUIManagerSubsystem();

	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End of USubsystem interface

private:
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	FTSTicker::FDelegateHandle TickHandle;
};
