// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_ThrowOwningThrowable.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "Core/Characters/Base_GameCharacter.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTTask_ThrowOwningThrowable::UBTTask_ThrowOwningThrowable()
{
	NodeName = TEXT("ThrowOwningThrowable");
}

EBTNodeResult::Type UBTTask_ThrowOwningThrowable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABase_GameCharacter* TaskCharacter = Cast<ABase_GameCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (TaskCharacter)
	{
		ABase_GameActor* ObjectToThrow = TaskCharacter->GetCurrentItemInHand();

		if (ObjectToThrow && ObjectToThrow->GetClass()->ImplementsInterface(UThrowable::StaticClass()))
		{
			IThrowable::Execute_Throw(ObjectToThrow, OwnerComp.GetAIOwner()->GetPawn(), 0.0f, FName(TEXT("None")));
		}
	}
	
	return EBTNodeResult::Succeeded;
}

