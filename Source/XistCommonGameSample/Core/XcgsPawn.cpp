// Copyright (c) 2023 xist.gg

#include "XcgsPawn.h"


// Sets default values
AXcgsPawn::AXcgsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}
