// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDecorator_IsThrowableOwnedBySomeone.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTDecorator_IsThrowableOwnedBySomeone : public UBTDecorator
{
	GENERATED_BODY()

public:

	UBTDecorator_IsThrowableOwnedBySomeone();

protected:
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool IsThrowableOwned(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector ThrowableKey;
	
};


