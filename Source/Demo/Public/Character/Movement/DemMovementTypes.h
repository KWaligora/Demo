// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemMovementTypes.generated.h"

UENUM(BlueprintType)
enum class EDemGait : uint8
{
	Walking,
	Jogging,
};

static FString EnumToString(const EDemGait InGait)
{
	switch (InGait)
	{
		case EDemGait::Walking:
			return(TEXT("Walking"));
		case EDemGait::Jogging:
			return(TEXT("Jogging"));
	default:
		return {};
	}	
};

USTRUCT(BlueprintType)
struct FDemGaitSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed = -1.0f;
	
	UPROPERTY(EditAnywhere)
	float MaxAcceleration = -1.0f;
	
	UPROPERTY(EditAnywhere)
	float BreakingAcceleration = -1.0f;
	
	UPROPERTY(EditAnywhere)
	float BrakingFrictionFactor = -1.0f;
	
	UPROPERTY(EditAnywhere)
	float BrakingFriction = -1.0f;
	
	UPROPERTY(EditAnywhere)
	bool bUseSeparateBrakingFriction = false;
};