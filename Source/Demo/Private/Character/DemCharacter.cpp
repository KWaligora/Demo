// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DemCharacter.h"

#include "Character/Inventory/DemInventoryComponent.h"
#include "Character/Movement/DemCharacterMovementComponent.h"

ADemCharacter::ADemCharacter(const FObjectInitializer& OutObjectInitializer)
	: Super(OutObjectInitializer.SetDefaultSubobjectClass<UDemCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	
	InventoryComponent = CreateDefaultSubobject<UDemInventoryComponent>("InventoryComponent");
}