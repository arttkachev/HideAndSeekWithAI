// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_SetSpawnTransform.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"


UBTTask_SetSpawnTransform::UBTTask_SetSpawnTransform()
{
	NodeName = TEXT("SetSpawnTransform");
}

EBTNodeResult::Type UBTTask_SetSpawnTransform::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	const FVector SpawnLocation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(TEXT("SpawnLocation"));
	const FRotator SpawnRotation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsRotator(TEXT("SpawnRotation"));
	OwnerComp.GetAIOwner()->GetPawn()->SetActorLocation(SpawnLocation);
	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(SpawnRotation);
	return EBTNodeResult::Succeeded;
}

