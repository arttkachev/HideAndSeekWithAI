// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomWait.generated.h"

struct FBTRandomWaitTaskMemory
{	
	float RemainingWaitTime;
};

UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_RandomWait : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	UBTTask_RandomWait();

protected:
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Data")
		float Min = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Data")
		float Max = 0.0f;	
	
};
