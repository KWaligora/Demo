// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "DemInputComponent.generated.h"

class UDemCharacterMovementComponent;
class UDemInventoryComponent;
class UInputMappingContext;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UDemInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDemInputComponent();

	void SetupInput(UEnhancedInputComponent* InEnhanceInputComponent, const ULocalPlayer* InLocalPlayer);

	//~ Begin UActorComponent interface
	virtual void BeginPlay() override;
	//~ End UActorComponent interface
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MainMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> SwitchWeaponInput;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AimInput;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookInput;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveInput;
	
private:
	void CacheInventoryComponent();
	
	void SwitchWeapon(const FInputActionValue& InInputActionValue);
	
	void StartAiming();
	void StopAiming();
	
	void Look(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);
	
	TWeakObjectPtr<UDemInventoryComponent> InventoryComponentWeak;
	TWeakObjectPtr<UDemCharacterMovementComponent> DemCharacterMovementComponentWeak;
};
