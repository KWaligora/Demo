// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemAnimationTypes.generated.h"

UENUM(BlueprintType)
enum class EDemLocomotionDirection : uint8
{
	Forward,
	Backward,
	Right,
	Left
};

USTRUCT(BlueprintType)
struct FDemCycleAnimations
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimSequence> Forward;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimSequence> Backward;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimSequence> Right;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimSequence> Left;
};