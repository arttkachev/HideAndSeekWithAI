// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/EQS/Contexts/EQSContext_OtherGameActors.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "Kismet/GameplayStatics.h"

void UEQSContext_OtherGameActors::ProvideContext(FEnvQueryInstance& QueryInstance,
	FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	const AActor* Querier = Cast<AActor>((QueryInstance.Owner).Get());
	if (Querier)
	{		
		TArray<AActor*>OtherGameActors;
		UGameplayStatics::GetAllActorsOfClass(Querier, ABase_GameActor::StaticClass(), OtherGameActors);
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, OtherGameActors);
	}	
}
