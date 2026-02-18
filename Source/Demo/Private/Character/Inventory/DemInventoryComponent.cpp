// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Inventory/DemInventoryComponent.h"
#include "Items/DemItemData.h"

UDemInventoryComponent::UDemInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDemInventoryComponent::SetEquippedWeapon(const UDemItemData* InNewItemData)
{
	if (InNewItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] ItemData is nullptr"), __FUNCTION__);
		return;
	}
	
	WeaponSlotsMap[InNewItemData->ItemType] = InNewItemData;
}

void UDemInventoryComponent::SetCurrentWeaponSlot(const EDemItemType InNewSlot)
{
	TObjectPtr<const UDemItemData>* ItemData = WeaponSlotsMap.Find(InNewSlot);
	if (ItemData == nullptr)
	{
		return;
	}
	
	CurrentWeaponSlot = InNewSlot;
	
	OnEquippedWeaponChanged.Broadcast(*ItemData);
}

void UDemInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetCurrentWeaponSlot(CurrentWeaponSlot);
}

