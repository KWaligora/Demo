// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Movement/DemCharacterMovementComponent.h"

void UDemCharacterMovementComponent::SetGait(const EDemGait InNewGait)
{	
	const FDemGaitSettings* GaitSettings = GaitDataMap.Find(InNewGait);
	if (GaitSettings == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Can't find gait settings for %s"), __FUNCTION__, *EnumToString(InNewGait));
		return;
	}
	
	MaxWalkSpeed = GaitSettings->MaxWalkSpeed;
	MaxAcceleration = GaitSettings->MaxAcceleration;
	BrakingFrictionFactor = GaitSettings->BrakingFrictionFactor;
	BrakingFriction = GaitSettings->BrakingFriction;
	bUseSeparateBrakingFriction = GaitSettings->bUseSeparateBrakingFriction;
	
	CurrentGait = InNewGait;
	
	OnGaitChanged.Broadcast(CurrentGait);
}

void UDemCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetGait(InitialGait);
}
