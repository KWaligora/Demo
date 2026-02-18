// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/DemItemTypes.h"
#include "DemInventoryComponent.generated.h"

enum class EDemItemType : uint8;
class UDemItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDemOnEquippedWeaponChanged, const UDemItemData*, InItemData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UDemInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDemInventoryComponent();
	
	UFUNCTION(BlueprintCallable)
	void SetEquippedWeapon(const UDemItemData* InNewItemData);
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentWeaponSlot(const EDemItemType InNewSlot);

	//~ Begin UActorComponent interface
	virtual void BeginPlay() override;
	//~ End UActorComponent interface
	
	UPROPERTY(BlueprintAssignable, Category = "Weapons")
	FDemOnEquippedWeaponChanged OnEquippedWeaponChanged;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	TMap<EDemItemType, TObjectPtr<const UDemItemData>> WeaponSlotsMap;
	
private:
	EDemItemType CurrentWeaponSlot = EDemItemType::UnArmed;
};
