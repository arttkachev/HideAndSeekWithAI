// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_SetAIState.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UBTTask_SetAIState::UBTTask_SetAIState()
{
	NodeName = FString(TEXT("SetAIState"));
}

EBTNodeResult::Type UBTTask_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("AIState")), static_cast<uint8>(AIState));
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("AISubStateState")), static_cast<uint8>(AISubState));
	return EBTNodeResult::Succeeded;
}
