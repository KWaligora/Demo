// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemMovementTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DemCharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDemOnGaitChanged, EDemGait, InCurrentGait);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UDemCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter, Category = "Gait")
	const TMap<EDemGait, FDemGaitSettings>& GetGaitMap() const { return GaitDataMap; }
	
	UFUNCTION(BlueprintGetter, Category = "Gait")
	EDemGait GetCurrentGait() const { return CurrentGait; }
	
	UFUNCTION(BlueprintCallable, Category="Gait")
	void SetGait(const EDemGait InNewGait);

	//~ Begin UActorComponent interface
	virtual void BeginPlay() override;
	//~ End UActorComponent interface
	
	UPROPERTY(BlueprintAssignable, Category = "Gait")
	FDemOnGaitChanged OnGaitChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Gait")
	EDemGait InitialGait = EDemGait::Jogging;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gait")
	TMap<EDemGait, FDemGaitSettings> GaitDataMap;
	
	EDemGait CurrentGait = EDemGait::Walking;
};
