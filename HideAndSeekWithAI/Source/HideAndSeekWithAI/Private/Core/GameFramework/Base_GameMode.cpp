// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameFramework/Base_GameMode.h"
#include "Engine/World.h"
#include "Core/Tools/SpawnerManager.h"
#include "Kismet/GameplayStatics.h"

void ABase_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn a SpawnerManager which will control an execution sequence of all spawners
	// This is an implicit step for designers that guarantees correct initialization
	UWorld* World = this->GetWorld();

	if (World)
	{
		// make sure we have a singleton. We need only one SpawnManager
		TArray<AActor*>FoundSpawnerManagers;
		UGameplayStatics::GetAllActorsOfClass(World, ASpawnerManager::StaticClass(), FoundSpawnerManagers);

		if (FoundSpawnerManagers.Num() == 0)
		{
			World->SpawnActor<ASpawnerManager>(ASpawnerManager::StaticClass(), FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
		}
	}	
}

