// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/EQS/Contexts/EQSContext_PlayerCharacter.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Core/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UEQSContext_PlayerCharacter::ProvideContext(FEnvQueryInstance& QueryInstance,
	FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const AActor* Querier = Cast<AActor>((QueryInstance.Owner).Get());
	if (Querier)
	{
		TArray<AActor*>PlayerCharacters;
		UGameplayStatics::GetAllActorsOfClass(Querier, APlayerCharacter::StaticClass(), PlayerCharacters);
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacters);
	}
}
