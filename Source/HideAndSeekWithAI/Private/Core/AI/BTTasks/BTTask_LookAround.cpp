// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_LookAround.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

UBTTask_LookAround::UBTTask_LookAround()
{
	NodeName = FString(TEXT("LookAround"));
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);	

	// cache OwnerComp and NodeMemory to call OnLatentTaskFinished later
	OwnerCompPtr = &OwnerComp;
	NodeMemoryPtr = NodeMemory;

	// Get a value specified by a user from a UPROPERTY. Timer doesn't accept a pass in value which has UPROPERTY specification
	RotationTime = RotationTimeForEachSide;

	// Start looking around
	LookRight();		
	return EBTNodeResult::InProgress;
}

void UBTTask_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	OwnerComp.GetAIOwner()->GetPawn()->AddActorWorldRotation((UKismetMathLibrary::MakeRotator(0.0f, 0.0f, RotationSpeed) * DeltaSeconds) * TurnSide);	
}

void UBTTask_LookAround::LookRight()
{
	TurnSide = 1;
	GetWorld()->GetTimerManager().SetTimer(LookRightTimeHandle, this, &UBTTask_LookAround::LookRightComplete, RotationTime, false );
}

void UBTTask_LookAround::LookRightComplete()
{
	LookRightTimeHandle.Invalidate();
	LookLeft();
}

void UBTTask_LookAround::LookLeft()
{
	TurnSide = -1;
	GetWorld()->GetTimerManager().SetTimer(LookLeftTimeHandle, this, &UBTTask_LookAround::LookLeftComplete, RotationTime * 2, false);
}

void UBTTask_LookAround::LookLeftComplete()
{
	LookLeftTimeHandle.Invalidate();
	ReturnToOriginalRotation();
}

void UBTTask_LookAround::ReturnToOriginalRotation()
{
	TurnSide = 1;
	GetWorld()->GetTimerManager().SetTimer(ReturnToOriginalRotationTimeHandle, this, &UBTTask_LookAround::ReturnToOriginalRotationComplete, RotationTime, false);
}

void UBTTask_LookAround::ReturnToOriginalRotationComplete()
{
	ReturnToOriginalRotationTimeHandle.Invalidate();	
	FinishLatentTask(*OwnerCompPtr, EBTNodeResult::Succeeded);	
}
