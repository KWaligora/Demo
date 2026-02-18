// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemPlayerController.generated.h"

class UDemInputComponent;
/**
 * 
 */
UCLASS()
class DEMO_API ADemPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADemPlayerController();
	
protected:
	//~ Begin APlayerController interface
	virtual void SetupInputComponent() override;
	//~ End APlayerController interface
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UDemInputComponent> DemInputComponent;
};
