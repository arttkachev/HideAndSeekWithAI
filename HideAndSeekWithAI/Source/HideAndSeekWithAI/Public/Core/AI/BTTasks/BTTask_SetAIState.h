// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Core/AI/AIControllers/EnemyAIController.h"
#include "BTTask_SetAIState.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_SetAIState : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SetAIState();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Data")
	EAIState AIState;

	UPROPERTY(EditAnywhere, Category = "Data")
	EAISubState AISubState;
	
};
