// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ModifyWalkSpeed.generated.h"

UENUM(BlueprintType)
enum class EModificatorType : uint8
{
	SetDefaultWalkSpeed UMETA(DisplayName = "SetDefaultWalkSpeed"),
	DecreaseWalkSpeed 	UMETA(DisplayName = "DecreaseWalkSpeed"),
	IncreaseWalkSpeed 	UMETA(DisplayName = "IncreaseWalkSpeed"),	
};

UCLASS()
class HIDEANDSEEKWITHAI_API UBTTask_ModifyWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_ModifyWalkSpeed();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Data")
	EModificatorType ModificatorType = EModificatorType::SetDefaultWalkSpeed;

	// A value will be normalized inside a function call. For designers, it is easier to think in terms of percentage from 0% to 100%
	// A normalized value will be from 0.0f to 1.0f
	UPROPERTY(EditAnywhere, Category = "Data", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float Percentage = 20.0f;	
};
