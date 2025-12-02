// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsPlayerController.h"

#include "PrimaryGameLayout.h"
#include "XcgsLocalPlayer.h"
#include "XcgsLog.h"


// Sets default values
AXcgsPlayerController::AXcgsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;  // PlayerController MUST tick for EnhancedInput to work
}


// Called when the game starts or when spawned
void AXcgsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	XCGS_LOG(TEXT("Player Controller starting up [%s]"), *GetName());

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	/*
	 * The code inside this debug block isn't really required for this to work.
	 * However, it can be easy to miss these setup steps, so here are some
	 * extra checks to ensure the INI is correctly configured.
	 */

	// CommonGame requires that the LocalPlayer is a UCommonLocalPlayer
	const UCommonLocalPlayer* LocalPlayer = Cast<UCommonLocalPlayer>(GetLocalPlayer());
	ensureAlwaysMsgf(IsValid(LocalPlayer), TEXT("LocalPlayer must be derived from UCommonLocalPlayer; fix INI and restart"));

	// Make sure we're configured with a valid RootUILayout
	const UPrimaryGameLayout* RootUILayout = LocalPlayer->GetRootUILayout();
	ensureAlwaysMsgf(IsValid(RootUILayout), TEXT("RootUILayout must be configured in project settings"));
#endif
}


void AXcgsPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
