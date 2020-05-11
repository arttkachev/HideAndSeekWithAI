// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "Math/RandomStream.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Spawner.generated.h"

class ASpawner;

DECLARE_DELEGATE_OneParam(FParamDelegateSignature, ASpawner*)

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ASpawner : public ABase_GameActor
{
	GENERATED_BODY()	

protected:

	UPROPERTY(EditAnywhere, Category = "Settings")
	uint32 NumberToSpawn = 24;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FRandomStream Seed = 27394;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AActor> ClassToSpawn = nullptr;

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool UseRandomRotation = false;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UEnvQuery * EQSQueryTemplate = nullptr;	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FParamDelegateSignature OnSpawnComplete;
	
	void FindRandomLocation();
	void OnEQSQueryFinished(TSharedPtr<FEnvQueryResult> Result);	
	void SpawnActorAtRandomLocation(TSharedPtr<FEnvQueryResult> Result);

	
};