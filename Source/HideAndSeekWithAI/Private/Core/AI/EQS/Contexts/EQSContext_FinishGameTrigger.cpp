// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/EQS/Contexts/EQSContext_FinishGameTrigger.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Core/GameEntities/Triggers/FinishGameTrigger.h"
#include "Kismet/GameplayStatics.h"

void UEQSContext_FinishGameTrigger::ProvideContext(FEnvQueryInstance& QueryInstance,
	FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const AActor* Querier = Cast<AActor>((QueryInstance.Owner).Get());
	if (Querier)
	{
		TArray<AActor*>OtherFinishGameTriggers;
		UGameplayStatics::GetAllActorsOfClass(Querier, AFinishGameTrigger::StaticClass(), OtherFinishGameTriggers);
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, OtherFinishGameTriggers);
	}
}
