// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTDecorators/BTDecorator_IsThrowableOwnedBySomeone.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"

UBTDecorator_IsThrowableOwnedBySomeone::UBTDecorator_IsThrowableOwnedBySomeone()
{
	
	NodeName =  TEXT("IsThrowableOwnedBySomeone");	
	bNotifyTick = true;	
	FlowAbortMode = EBTFlowAbortMode::None;
	ThrowableKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsThrowableOwnedBySomeone, ThrowableKey), UObject::StaticClass());
	
}


bool UBTDecorator_IsThrowableOwnedBySomeone::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return IsThrowableOwned(OwnerComp, NodeMemory);
}


void UBTDecorator_IsThrowableOwnedBySomeone::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const bool IsOwned = IsThrowableOwned(OwnerComp, NodeMemory);
	
	if (IsOwned)	
	{		
		OwnerComp.RequestExecution(this);
	}
}

bool UBTDecorator_IsThrowableOwnedBySomeone::IsThrowableOwned(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{	
	ABase_GameCharacter* ControlledCharacter = Cast<ABase_GameCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (ControlledCharacter)
	{
		return IThrowable::Execute_IsThrowableOwned(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ThrowableKey.SelectedKeyName));
	}	
	
	return false;
}


