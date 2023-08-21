// Copyright (c) 2023 xist.gg

#include "XcgsPlayerPawn.h"

#include "UI/XcgsHUDLayout.h"
#include "CommonUIExtensions.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "XcgsGameplayTags.h"
#include "XcgsInputConfig.h"
#include "XcgsLog.h"
#include "Core/XcgsGameState.h"
#include "Core/XcgsHelpers.h"


// Sets default values
AXcgsPlayerPawn::AXcgsPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Xcgs is an RTS style input by default, so player pawn should never affect navigation
	bCanAffectNavigationGeneration = false;

	CameraOffset = FVector::ZeroVector;
	ZoomVelocity = 10.f;
}


void AXcgsPlayerPawn::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	// DO NOT CALL SUPER -- this is a complete override
	//-Super::CalcCamera(DeltaTime, OutResult);

	GetActorEyesViewPoint(OutResult.Location, OutResult.Rotation);

	OutResult.Location += CameraOffset;
}


void AXcgsPlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// We expect that this *player* pawn will be possessed by players, but who knows...
	const APlayerController* PC = Cast<APlayerController>(NewController);
	if (ensure(PC))
	{
		// Add HUD Layout widget to the player's Game UI Layer
		XCGS_LOG(TEXT("Pushing Game HUD [%s] to UI"), *GetNameSafe(HUDLayoutClass));
		HUDLayoutWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(PC->GetLocalPlayer(), XcgsTag::UI_Layer_Game, HUDLayoutClass);

		// Add EnhancedInput IMCs
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = UXcgsHelpers::GetEnhancedInputLocalPlayerSubsystem(PC))
		{
			XCGS_LOG(TEXT("Clearing all input mappings"));
			Subsystem->ClearAllMappings();

			// Apply the array of IMCs in descending priority
			int32 Priority = InputMappingContexts.Num();
			for (const TObjectPtr<const UInputMappingContext>& Imc : InputMappingContexts)
			{
				// Don't store empty IMCs in Data Assets!
				if (ensure(Imc != nullptr))
				{
					XCGS_LOG(TEXT("Adding IMC [%s] with priority %i"), *GetNameSafe(Imc), Priority);

					FModifyContextOptions Options = {};
					Options.bIgnoreAllPressedKeysUntilRelease = false;

					Subsystem->AddMappingContext(Imc, Priority, Options);
					Priority--;
				}
			}
		}
	}
}


void AXcgsPlayerPawn::UnPossessed()
{
	// Remove any HUD we added to the player's UI
	if (HUDLayoutWidget.IsValid())
	{
		XCGS_LOG(TEXT("Cleaning up HUD Layout Widget"));
		UCommonUIExtensions::PopContentFromLayer(HUDLayoutWidget.Get());
		HUDLayoutWidget.Reset();
	}

	// Remove any EnhancedInput IMCs
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = UXcgsHelpers::GetEnhancedInputLocalPlayerSubsystem(GetController<APlayerController>()))
	{
		XCGS_LOG(TEXT("Clearing input mappings"));
		Subsystem->ClearAllMappings();
	}

	// Unbind from EnhancedInput
	UnbindInputValueActions();

	Super::UnPossessed();
}


void AXcgsPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// You **MUST** set InputActionMap or your pawn won't have any inputs!
	if (!ensure(IsValid(InputActionMap)))
	{
		XCGS_ERROR_LOG(TEXT("InputActionMap is not configured for player pawn; player pawn will have no inputs"));
		return;
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (ensure(EnhancedInput))
	{
		constexpr bool bLogNotFound = true;

		// Look and Zoom should update every tick while Triggered
		BindInputValueAction(EnhancedInput, XcgsTag::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look, bLogNotFound);
		BindInputValueAction(EnhancedInput, XcgsTag::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, bLogNotFound);
		BindInputValueAction(EnhancedInput, XcgsTag::InputTag_Zoom, ETriggerEvent::Triggered, this, &ThisClass::Input_Zoom, bLogNotFound);

		// Start/Stop Time only on completed input actions, not on pending actions
		BindInputValueAction(EnhancedInput, XcgsTag::InputTag_Time_Start, ETriggerEvent::Completed, this, &ThisClass::Input_Time_Start, bLogNotFound);
		BindInputValueAction(EnhancedInput, XcgsTag::InputTag_Time_Stop, ETriggerEvent::Completed, this, &ThisClass::Input_Time_Stop, bLogNotFound);
	}
}


template <class UserClass, typename ... VarTypes>
void AXcgsPlayerPawn::BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FEnhancedInputActionHandlerValueSignature::TMethodPtr<UserClass, VarTypes...> Func, bool bLogIfNotFound, VarTypes... Vars)
{
	// The pawn **MUST** have an InputActionMap configured so we can map input actions to gameplay tags
	if (ensure(InputActionMap))
	{
		if (const UInputAction* Action = InputActionMap->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
		{
			const FEnhancedInputActionEventBinding& Binding = EnhancedInputComponent->BindAction(Action, TriggerEvent, Object, Func, Vars...);
			InputEventBindingHandles.Add(Binding.GetHandle());

			XCGS_VERBOSE_LOG(TEXT("Bound InputAction [%s] to [%s] handle=%i"), *GetNameSafe(Action), *InputTag.ToString(), Binding.GetHandle());
		}
	}
}


void AXcgsPlayerPawn::UnbindInputValueActions()
{
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!ensure(EnhancedInput))
	{
		XCGS_LOG(TEXT("Cannot unbind inputs without an EnhancedInputComponent"));
		return;
	}

	for (const int32& Handle : InputEventBindingHandles)
	{
		const bool bRemoved = EnhancedInput->RemoveActionEventBinding(Handle);
		if (!bRemoved)
		{
			XCGS_VERBOSE_LOG(TEXT("Failed to remove action event binding %i"), Handle);
		}
	}

	InputEventBindingHandles.Reset();
}


void AXcgsPlayerPawn::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	// this log is *extremely* verbose!
	//XCGS_VERBOSE_LOG(TEXT("Look X=%0.2f, Y=%0.2f"), Value.X, Value.Y);

	if (Value.X != 0.0f)
	{
		AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		AddControllerPitchInput(Value.Y);
	}
}


void AXcgsPlayerPawn::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		// Quaternion AxisY is the "right" vector
		FVector RightVector = GetControlRotation().Quaternion().GetAxisY();
		RightVector.Z = 0.f;  // constrain Z
		AddMovementInput(RightVector, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		// Quaternion AxisX is the "forward" vector
		FVector ForwardVector = GetControlRotation().Quaternion().GetAxisX();
		ForwardVector.Z = 0.f;  // constrain Z
		AddMovementInput(ForwardVector, Value.Y);
	}
}


void AXcgsPlayerPawn::Input_Time_Start(const FInputActionValue& InputActionValue)
{
	AXcgsGameState* GameState = Cast<AXcgsGameState>(GetWorld()->GetGameState());
	if (ensure(GameState))
	{
		XCGS_DISPLAY_LOG(TEXT("Start Time!"));
		GameState->UnpauseGameTime();
	}
}


void AXcgsPlayerPawn::Input_Time_Stop(const FInputActionValue& InputActionValue)
{
	AXcgsGameState* GameState = Cast<AXcgsGameState>(GetWorld()->GetGameState());
	if (ensure(GameState))
	{
		XCGS_DISPLAY_LOG(TEXT("Stop Time!"));
		GameState->PauseGameTime();
	}
}


void AXcgsPlayerPawn::Input_Zoom(const FInputActionValue& InputActionValue)
{
	// Get the non-normalized value
	// (usually this is 1.0 or -1.0 but it can/does sometimes go to 2, 3, ...)
	const float Value = InputActionValue.Get<float>();

	XCGS_VERBOSE_LOG(TEXT("Zoom %0.2f"), Value);

	CameraOffset.Z = FMath::Clamp(CameraOffset.Z + (Value * ZoomVelocity), 0.f, 500.f);
}
