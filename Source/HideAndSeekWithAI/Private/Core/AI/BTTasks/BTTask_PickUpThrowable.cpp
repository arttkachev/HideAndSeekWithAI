// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_PickUpThrowable.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTTask_PickUpThrowable::UBTTask_PickUpThrowable()
{
	NodeName = TEXT("PickUpThrowable");
}

EBTNodeResult::Type UBTTask_PickUpThrowable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ObjectToPickUp = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	
	if (ObjectToPickUp && ObjectToPickUp->GetClass()->ImplementsInterface(UThrowable::StaticClass()))
	{		
		IThrowable::Execute_PickUp(ObjectToPickUp, OwnerComp.GetAIOwner()->GetPawn());
	}
	
	return EBTNodeResult::Succeeded;
	
	
}
