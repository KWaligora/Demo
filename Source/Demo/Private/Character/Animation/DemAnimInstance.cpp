// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/DemAnimInstance.h"

#include "Character/DemCharacter.h"
#include "Character/Inventory/DemInventoryComponent.h"
#include "Character/Movement/DemCharacterMovementComponent.h"
#include "Logs/DemLogDefinitions.h"

void UDemAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	const ADemCharacter* Character = Cast<ADemCharacter>(TryGetPawnOwner());
	if (Character == nullptr)
	{
		UE_LOG(LogDemAnimation, Error, TEXT("[%hs] Character is not DemCharacter"), __FUNCTION__)
		return;
	}
	
	CharacterMovementComponent = Cast<UDemCharacterMovementComponent>(Character->GetCharacterMovement());
	check(CharacterMovementComponent);
	
	CharacterMovementComponent->OnGaitChanged.AddDynamic(this, &ThisClass::OnGaitChanged);
	
	UDemInventoryComponent* InventoryComponent = Character->GetInventoryComponent();
	check(InventoryComponent);
	
	InventoryComponent->OnEquippedWeaponChanged.AddDynamic(this, &ThisClass::OnEquippedWeaponChanged);
}

void UDemAnimInstance::NativeUninitializeAnimation()
{
	const ADemCharacter* Character = Cast<ADemCharacter>(TryGetPawnOwner());
	UDemInventoryComponent* InventoryComponent = IsValid(Character) ? Character->GetInventoryComponent() : nullptr;
	
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnEquippedWeaponChanged.RemoveAll(this);
	}
	
	if (IsValid(CharacterMovementComponent))
	{
		CharacterMovementComponent->OnGaitChanged.RemoveAll(this);
	}

	Super::NativeUninitializeAnimation();
}

void UDemAnimInstance::OnEquippedWeaponChanged(const UDemItemData* InItemData)
{
	if (!IsValid(InItemData))
	{
		UE_LOG(LogDemAnimation, Error, TEXT("[%hs] ItemData is invalid"), __FUNCTION__)
		return;
	}
	
	LinkAnimClassLayers(InItemData->AnimationLayer);
	CurrentEquippedItemType = InItemData->ItemType;
}

void UDemAnimInstance::OnGaitChanged(const EDemGait InCurrentGait)
{
	CurrentGait = InCurrentGait;
}
