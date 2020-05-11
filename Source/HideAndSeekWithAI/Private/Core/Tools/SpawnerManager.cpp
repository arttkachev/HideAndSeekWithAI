// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tools/SpawnerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
	const UWorld* World = this->GetWorld();

	if (World)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, ASpawner::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors)
		{
			ASpawner* Spawner = Cast<ASpawner>(FoundActor);
			if (Spawner)
			{
				AllSpawners.Enqueue(Spawner);
				
			}
			
		}

		ExecuteNextSpawner();
	}
}

void ASpawnerManager::ExecuteNextSpawner()
{
	if (!AllSpawners.IsEmpty()) // Base case for a recursive call
	{
		ASpawner* CurrentExecuting = nullptr;
		AllSpawners.Dequeue(CurrentExecuting); // recursive case

		CurrentExecuting->OnSpawnComplete.BindUObject(this, &ASpawnerManager::OnSpawnerExecutionComplete);
		CurrentExecuting->FindRandomLocation();
	}
}

void ASpawnerManager::OnSpawnerExecutionComplete(ASpawner* CompletedSpawner)
{
	if (CompletedSpawner)
	{
		CompletedSpawner->OnSpawnComplete.Unbind();
	}

	// Proceed with the next spawner
	// Recursive call
	ExecuteNextSpawner(); 
}
