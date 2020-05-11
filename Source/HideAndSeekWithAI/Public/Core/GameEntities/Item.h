// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API AItem : public ABase_GameActor, public IThrowable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void PickUp(APawn* PawnInstigator);
	void PickUp_Implementation(APawn* PawnInstigator);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void Throw(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag);
	void Throw_Implementation(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	void GetSpawnLocation(FVector& OutSpawnLocation) const;
	FORCEINLINE void GetSpawnLocation_Implementation(FVector& OutSpawnLocation) const
	{
		OutSpawnLocation = SpawnLocation;
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Throwable")
	bool IsThrowableOwned() const;
	FORCEINLINE bool IsThrowableOwned_Implementation() const
	{
		return IsOwned;
	}

protected:

	virtual void BeginPlay() override;
	
	
	
};
