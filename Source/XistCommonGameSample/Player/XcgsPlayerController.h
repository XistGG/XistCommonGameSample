// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "XcgsPlayerController.generated.h"


/**
 * CommonGame PlayerController
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsPlayerController : public ACommonPlayerController /** CommonGame base */
{
	GENERATED_BODY()

public:
	AXcgsPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

};
