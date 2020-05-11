// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAround.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_LookAround : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_LookAround();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

	UPROPERTY(EditAnywhere, Category = "Data")
	float RotationSpeed = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Data")
	float RotationTimeForEachSide = 3.0f;
	
	void LookRight();
	void LookRightComplete();
	void LookLeft();
	void LookLeftComplete();
	void ReturnToOriginalRotation();
	void ReturnToOriginalRotationComplete();

	UPROPERTY()
	UBehaviorTreeComponent* OwnerCompPtr = nullptr;
	
	uint8* NodeMemoryPtr = nullptr;

private:
	
	float RotationTime = 3.0f;
	int32 TurnSide = 1;
	FTimerHandle LookRightTimeHandle;
	FTimerHandle LookLeftTimeHandle;
	FTimerHandle ReturnToOriginalRotationTimeHandle;

	
	
	
};
