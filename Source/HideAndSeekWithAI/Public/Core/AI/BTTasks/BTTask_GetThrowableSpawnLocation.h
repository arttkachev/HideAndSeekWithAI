// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetThrowableSpawnLocation.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_GetThrowableSpawnLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_GetThrowableSpawnLocation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector ThrowableKey;

	UPROPERTY(EditAnywhere, Category = "Data")
	FBlackboardKeySelector WhereToStoreSpawnLocation;
	
};
