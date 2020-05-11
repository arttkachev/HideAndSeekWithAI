// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PickUpThrowable.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_PickUpThrowable : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_PickUpThrowable();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
