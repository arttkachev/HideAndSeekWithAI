// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_GetThrowableSpawnLocation.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTTask_GetThrowableSpawnLocation::UBTTask_GetThrowableSpawnLocation()
{
	NodeName = FString(TEXT("GetThrowableSpawnLocation"));
}

EBTNodeResult::Type UBTTask_GetThrowableSpawnLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ThrowableObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ThrowableKey.SelectedKeyName);

	if (ThrowableObject && ThrowableObject->GetClass()->ImplementsInterface(UThrowable::StaticClass()))
	{
		FVector ThrowableSpawnLocation;
		IThrowable::Execute_GetSpawnLocation(ThrowableObject, ThrowableSpawnLocation);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(WhereToStoreSpawnLocation.SelectedKeyName, ThrowableSpawnLocation);
	}

	return EBTNodeResult::Succeeded;
}
