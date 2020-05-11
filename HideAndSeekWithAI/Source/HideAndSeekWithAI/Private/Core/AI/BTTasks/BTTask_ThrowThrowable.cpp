// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_ThrowThrowable.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTTask_ThrowThrowable::UBTTask_ThrowThrowable()
{
	NodeName = FString(TEXT("ThrowThrowable"));
}

EBTNodeResult::Type UBTTask_ThrowThrowable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	UObject* ObjectToThrow = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ThrowableKey.SelectedKeyName);
	
	if (ObjectToThrow && ObjectToThrow->GetClass()->ImplementsInterface(UThrowable::StaticClass()))
	{
		IThrowable::Execute_Throw(ObjectToThrow, OwnerComp.GetAIOwner()->GetPawn(), 0.0f, FName(TEXT("None")));
	}

	return EBTNodeResult::Succeeded;
}
