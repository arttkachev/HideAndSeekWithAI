// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_RandomWait.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RandomWait::UBTTask_RandomWait()
{
	NodeName = TEXT("RandomWait");
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RandomWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTRandomWaitTaskMemory* MyMemory = (FBTRandomWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = UKismetMathLibrary::RandomFloatInRange(Min, Max);
	return EBTNodeResult::InProgress;
}

void UBTTask_RandomWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTRandomWaitTaskMemory* MyMemory = (FBTRandomWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f)
	{		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}