// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemItemTypes.h"
#include "Engine/DataAsset.h"
#include "DemItemData.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemItemData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Item")
	EDemItemType ItemType = EDemItemType::Pistol;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	TSubclassOf<UAnimInstance> AnimationLayer;
};
