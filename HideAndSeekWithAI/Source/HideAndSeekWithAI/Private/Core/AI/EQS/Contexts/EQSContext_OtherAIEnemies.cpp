// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/EQS/Contexts/EQSContext_OtherAIEnemies.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Core/Characters//Base_GameCharacter.h"
#include "Kismet/GameplayStatics.h"

void UEQSContext_OtherAIEnemies::ProvideContext(FEnvQueryInstance& QueryInstance,
	FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const AActor* Querier = Cast<AActor>((QueryInstance.Owner).Get());
	if (Querier)
	{
		TArray<AActor*>OtherGameCharacters;
		UGameplayStatics::GetAllActorsOfClass(Querier, ABase_GameCharacter::StaticClass(), OtherGameCharacters);
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, OtherGameCharacters);
	}
}
