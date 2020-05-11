// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "Core/Tools/Spawner.h"
#include "SpawnerManager.generated.h"



UCLASS()
class HIDEANDSEEKWITHAI_API ASpawnerManager : public ABase_GameActor
{
	GENERATED_BODY()	
	
protected:

	virtual void BeginPlay() override;

	void ExecuteNextSpawner();
	void OnSpawnerExecutionComplete(ASpawner* CompletedSpawner);

private:

	TQueue<ASpawner*> AllSpawners;	
};
