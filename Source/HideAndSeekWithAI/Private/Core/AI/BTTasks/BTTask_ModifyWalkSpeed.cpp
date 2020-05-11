// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/BTTask_ModifyWalkSpeed.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


UBTTask_ModifyWalkSpeed::UBTTask_ModifyWalkSpeed()
{
	// Assign a node name in ctr
	// Standard tasks use GetNodeIconName() that runs in Editor
	// We will do it inside ctr
	NodeName = TEXT("ModifyWalkSpeed");
}


EBTNodeResult::Type UBTTask_ModifyWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABase_GameCharacter* OwnerCharacter = Cast<ABase_GameCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (OwnerCharacter)
	{
		const float CharacterDefaultSpeed = OwnerCharacter->GetCharacterSettings().DefaultWalkSpeed;
		switch (ModificatorType)
		{
		case EModificatorType::SetDefaultWalkSpeed:

			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = CharacterDefaultSpeed;
			break;

		case EModificatorType::DecreaseWalkSpeed:
			
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = CharacterDefaultSpeed * UKismetMathLibrary::MapRangeClamped(Percentage, 0.0f, 100.0f, 0.0f, 1.0f);
			break;

		case EModificatorType::IncreaseWalkSpeed:
			
			OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = CharacterDefaultSpeed + (CharacterDefaultSpeed * UKismetMathLibrary::MapRangeClamped(Percentage, 0.0f, 100.0f, 0.0f, 1.0f));
			break;
		}
	}
	
	return EBTNodeResult::Succeeded;
}

