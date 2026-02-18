// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemCharacter.generated.h"

class UDemInventoryComponent;

UCLASS()
class DEMO_API ADemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADemCharacter(const FObjectInitializer& InObjectInitializer);

	UFUNCTION(BlueprintGetter, Category = "Inventory")
	UDemInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	
protected:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UDemInventoryComponent> InventoryComponent;
};
