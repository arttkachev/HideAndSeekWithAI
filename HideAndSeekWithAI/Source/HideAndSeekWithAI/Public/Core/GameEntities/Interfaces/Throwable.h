// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Core/GameEntities/Projectiles/Base_Projectile.h"
#include "Core/Characters/Base_GameCharacter.h"
#include "Throwable.generated.h"

//class ABase_Projectile;

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UThrowable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HIDEANDSEEKWITHAI_API IThrowable
{
	GENERATED_BODY()

	
		// Add interface functions to this class. This is the class that will be inherited to implement this interface.		
public:

	//TSubclassOf<ABase_Projectile> ProjectileClass;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void PickUp(APawn* PawnInstigator);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void Throw(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void GetSpawnLocation(FVector& OutSpawnLocation) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	bool IsThrowableOwned() const;
	
	

protected:
	FVector SpawnLocation;
	bool IsOwned = false;
	
};
