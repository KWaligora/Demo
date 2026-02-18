// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/DemPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Controllers/Input/DemInputComponent.h"

ADemPlayerController::ADemPlayerController()
{
	DemInputComponent = CreateDefaultSubobject<UDemInputComponent>(TEXT("DemInputComponent"));
}

void ADemPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* const EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent)
	
	DemInputComponent->SetupInput(EnhancedInputComponent, GetLocalPlayer());
}
