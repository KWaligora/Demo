// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Movement/DemMovementTypes.h"
#include "Items/DemItemData.h"
#include "DemAnimInstance.generated.h"

class UDemCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class DEMO_API UDemAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//~ Begin UAnimInstance interface
	virtual void NativeBeginPlay() override;
	virtual void NativeUninitializeAnimation() override;
	//~ End UAnimInstance interface
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDemCharacterMovementComponent> CharacterMovementComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="Gait")
	EDemGait CurrentGait = EDemGait::Jogging;
	
	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	EDemItemType CurrentEquippedItemType = EDemItemType::UnArmed;
	
private:
	UFUNCTION()
	void OnEquippedWeaponChanged(const UDemItemData* InItemData);
	
	UFUNCTION()
	void OnGaitChanged(const EDemGait InCurrentGait);
};
