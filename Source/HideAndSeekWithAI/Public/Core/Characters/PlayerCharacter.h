// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

class UThrowable;

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API APlayerCharacter : public ABase_GameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// getters
	FORCEINLINE UThrowable* GetCurrentThrowableItem() const
	{
		return CurrentThrowableItem;
	}

	// setters
	void SetCurrentThrowableItem(UThrowable* InteractingItemToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter")
	UCameraComponent* Camera = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Control
	void Forward(float amount);
	void Back(float amount);
	void Right(float amount);
	void Left(float amount);
	void Turn(float amount);	

private:

	
	UThrowable* CurrentThrowableItem = nullptr;	
	const float BaseTurnRate = 45.0f;
	
};
