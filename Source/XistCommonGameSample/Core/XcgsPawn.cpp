// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsPawn.h"


// Sets default values
AXcgsPawn::AXcgsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}
