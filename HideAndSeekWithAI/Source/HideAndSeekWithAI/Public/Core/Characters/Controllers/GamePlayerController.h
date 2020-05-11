// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/Base_GameCharacter.h"
#include "Core/Characters/Controllers/Base_PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API AGamePlayerController : public ABase_PlayerController
{
	GENERATED_BODY()

public:

	AGamePlayerController();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnLCMPressed();
	void OnLCMReleased();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY()
	ABase_GameCharacter* ControlledCharacter = nullptr;

private:	

	// keep in mind future possible remapping by the user
	// this is a different pattern that will take a time more than a recommended time for the test assignment
	const FKey ChargeThrowButton = EKeys::LeftMouseButton;		
	
	bool IsChargingThrow = false;
	float ChargeThrowButtonDownTime = 0.0f;

	// We don't use magic numbers, so, we're gonna assign default values to const variables and use them in code
	// if the value needs to be changed, we change it in one place here, not going through the whole game code	
	float MinThrowDistance = 100.0f; 
	float MaxThrowDistance = 1500.0f; 
	float MinChargingThrowTime = 0.0f; // in seconds
	float MaxChargingThrowTime = 2.0f; // in seconds
};
