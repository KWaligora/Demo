// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/Input/DemInputComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/DemCharacter.h"
#include "Character/Inventory/DemInventoryComponent.h"
#include "Character/Movement/DemCharacterMovementComponent.h"
#include "Logs/DemLogDefinitions.h"

UDemInputComponent::UDemInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDemInputComponent::SetupInput(UEnhancedInputComponent* InEnhanceInputComponent, const ULocalPlayer* InLocalPlayer)
{
	if (InEnhanceInputComponent == nullptr || InLocalPlayer == nullptr)
	{
		UE_LOG(LogDemController, Error, TEXT("[%hs] InEnhanceInputComponent or InLocalPlayer is nullptr"), __FUNCTION__);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InLocalPlayer);
	check(EnhancedSubsystem);
	
	EnhancedSubsystem->AddMappingContext(MainMappingContext, 0);
	
	InEnhanceInputComponent->BindAction(SwitchWeaponInput, ETriggerEvent::Started, this, &ThisClass::SwitchWeapon);
	
	InEnhanceInputComponent->BindAction(AimInput, ETriggerEvent::Started, this, &ThisClass::StartAiming);
	InEnhanceInputComponent->BindAction(AimInput, ETriggerEvent::Completed, this, &ThisClass::StopAiming);
	
	InEnhanceInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &ThisClass::Look);
	InEnhanceInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void UDemInputComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CacheInventoryComponent();
}

void UDemInputComponent::CacheInventoryComponent()
{
	const APlayerController* PC = GetOwner<APlayerController>();
	const ADemCharacter* DemCharacter = IsValid(PC) ? PC->GetPawn<ADemCharacter>() : nullptr;
	
	if (!IsValid(DemCharacter))
	{
		UE_LOG(LogDemController, Error, TEXT("[%hs] Can't get PlayerPawn"), __FUNCTION__);
		return;
	}
	
	InventoryComponentWeak = DemCharacter->GetInventoryComponent();
	DemCharacterMovementComponentWeak = Cast<UDemCharacterMovementComponent>(DemCharacter->GetCharacterMovement());
}

void UDemInputComponent::SwitchWeapon(const FInputActionValue& InInputActionValue)
{
	UDemInventoryComponent* InventoryComponent = InventoryComponentWeak.Get();
	if (InventoryComponent == nullptr)
	{
		UE_LOG(LogDemController, Error, TEXT("[%hs] InventoryComponent is invalid"), __FUNCTION__);	
		return;
	}
	
	// subtracting 1 because the enum starts with 0
	const int32 WeaponIndex = FMath::TruncToInt(InInputActionValue.GetMagnitude()) - 1;
	InventoryComponent->SetCurrentWeaponSlot(static_cast<EDemItemType>(WeaponIndex));
}

void UDemInputComponent::StartAiming()
{
	UDemCharacterMovementComponent* MovementComponent = DemCharacterMovementComponentWeak.Get();
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogDemController, Error, TEXT("[%hs] MovementComponent is invalid"), __FUNCTION__);	
		return;
	}
	
	MovementComponent->SetGait(EDemGait::Walking);
}

void UDemInputComponent::StopAiming()
{
	UDemCharacterMovementComponent* MovementComponent = DemCharacterMovementComponentWeak.Get();
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogDemController, Error, TEXT("[%hs] MovementComponent is invalid"), __FUNCTION__);	
		return;
	}
	
	MovementComponent->SetGait(EDemGait::Jogging);
}

void UDemInputComponent::Look(const FInputActionValue& InputActionValue)
{
	const APlayerController* PC = GetOwner<APlayerController>();
	APawn* Pawn = IsValid(PC) ? PC->GetPawn() : nullptr;
	
	if (!IsValid(Pawn))
	{
		return;
	}
	
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	
	Pawn->AddControllerYawInput(LookVector.X);
	Pawn->AddControllerPitchInput(LookVector.Y);
}

void UDemInputComponent::Move(const FInputActionValue& InputActionValue)
{
	const APlayerController* PC = GetOwner<APlayerController>();
	APawn* Pawn = IsValid(PC) ? PC->GetPawn() : nullptr;
	
	if (!IsValid(Pawn))
	{
		return;
	}
	
	const FVector2D MoveVector2D = InputActionValue.Get<FVector2D>();
	
	Pawn->AddMovementInput(Pawn->GetActorForwardVector(), MoveVector2D.X);
	Pawn->AddMovementInput(Pawn->GetActorRightVector(), MoveVector2D.Y);
}
