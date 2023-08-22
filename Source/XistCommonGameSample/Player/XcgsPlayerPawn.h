// Copyright (c) 2023 xist.gg

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTags.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "Core/XcgsPawn.h"
#include "XcgsPlayerPawn.generated.h"


struct FEnhancedInputActionEventBinding;
class UXcgsInputActionMap;
class UInputMappingContext;
class UCommonActivatableWidget;
class UXcgsHUDLayout;


/**
 * Player Pawn
 */
UCLASS(meta=(Category=Xcgs))
class XISTCOMMONGAMESAMPLE_API AXcgsPlayerPawn : public AXcgsPawn
{
	GENERATED_BODY()

public:
	AXcgsPlayerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AActor interface
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	//~End of AActor interface

protected:
	//~APawn interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~End of APawn interface

protected:
	/** The HUD Layout widget to use (must be derived from Xcgs HUD Layout) */
	UPROPERTY(EditDefaultsOnly, DisplayName="HUD Layout Class")
	TSubclassOf<UXcgsHUDLayout> HUDLayoutClass;

	/** Used to keep track of the widget that was created to be our HUD */
	UPROPERTY(Transient, VisibleInstanceOnly)
	TWeakObjectPtr<UCommonActivatableWidget> HUDLayoutWidget;

	/** Array of IMC to use while this Pawn is possessed */
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<const UInputMappingContext>> InputMappingContexts;

	/** Map of InputActions to C++ GameplayTags */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UXcgsInputActionMap> InputActionMap;

	/** Speed at which Zoom changes */
	UPROPERTY(EditDefaultsOnly)
	float ZoomVelocity;

protected:
	template<class UserClass, typename... VarTypes>
	void BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, typename FEnhancedInputActionHandlerValueSignature::template TMethodPtr< UserClass, VarTypes... > Func, bool bLogIfNotFound, VarTypes... Vars);

	void UnbindInputValueActions();

	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Time_Start(const FInputActionValue& InputActionValue);
	void Input_Time_Stop(const FInputActionValue& InputActionValue);

	void Input_Zoom(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(Transient, VisibleInstanceOnly)
	TSet<int32> InputEventBindingHandles;

	UPROPERTY(Transient, VisibleInstanceOnly)
	FVector CameraOffset;

};
