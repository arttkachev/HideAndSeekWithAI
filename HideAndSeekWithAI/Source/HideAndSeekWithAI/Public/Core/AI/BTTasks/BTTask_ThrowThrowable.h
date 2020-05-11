// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ThrowThrowable.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_ThrowThrowable : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	UBTTask_ThrowThrowable();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector ThrowableKey;
	
};
