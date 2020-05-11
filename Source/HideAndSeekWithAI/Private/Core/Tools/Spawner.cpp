// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tools/Spawner.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"


// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();			
}


// The method starts EQS testing for best random locations in the world to get better randomness
// and exclude cases of overlapping and poor distribution of spawned actors (when we want to spawn multiple actors at once)
// and, of course, with this approach we have control of randomness using a seed parameter
void ASpawner::FindRandomLocation()
{
	if (NumberToSpawn > 0) // Base case for a recursive call
	{
		NumberToSpawn--; // Recursive case

		// We execute a direct query request
		FEnvQueryRequest QueryRequest(EQSQueryTemplate, this);
		QueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &ASpawner::OnEQSQueryFinished);		
	}

	else
	{
		OnSpawnComplete.ExecuteIfBound(this);
	}
}

void ASpawner::OnEQSQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	// Once EQS Query finished its work we spawn a new actor on the best location
	SpawnActorAtRandomLocation(Result);
}


void ASpawner::SpawnActorAtRandomLocation(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccsessful())
	{
		TArray<FVector> ResultLocations;
		Result->GetAllAsLocations(ResultLocations);
		
		// We use a seed parameter to control randomness
		const int32 Index = Seed.RandRange(0, ResultLocations.Num() - 1);
		const FVector ResultLocation = ResultLocations[Index];
		
		UWorld* World = this->GetWorld();
		if (World)
		{
			FRotator SpawnRotation;
			
			if (UseRandomRotation)
			{
				SpawnRotation = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, UKismetMathLibrary::RandomFloatInRangeFromStream(-180.0f, 180.0f, Seed));
			}
			
			else
			{
				SpawnRotation = FRotator::ZeroRotator;
			}			
			
			AActor* SpawnedActor = World->SpawnActor<AActor>(ClassToSpawn, ResultLocation, SpawnRotation);

			
		}

	}

	// IMPORTANT! We use recursion and make a new call to find a new random location every time after a new actor spawned
//  because for "beautiful randomness" EQS needs to know about other actors which had already been spawned to find best random locations.
//  If we spawn all actors in one call it can get poor distribution and won't be much different from just using "GetRandomLocation".
//  In this case, EQS has a chance to test minimum distance between actors, for example
	FindRandomLocation();
}

