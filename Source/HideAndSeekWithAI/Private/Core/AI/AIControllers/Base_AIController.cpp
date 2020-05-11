// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/AIControllers/Base_AIController.h"

void ABase_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABase_AIController::SetDetectionByAffiliation(EPerceptionType Perception, bool DetectEnemies, bool DetectNeutrals, bool DetectFriendlies) const
{
	switch (Perception)
	{
	case EPerceptionType::SightPerception:

		if (SightConfig && SightPerception)
		{
			SightConfig->DetectionByAffiliation.bDetectEnemies = DetectEnemies;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = DetectNeutrals;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = DetectFriendlies;
			SightPerception->RequestStimuliListenerUpdate();
		}
		break;

	case EPerceptionType::HearingPerception:
		
		if (HearingConfig && HearingPerception)
		{
			HearingConfig->DetectionByAffiliation.bDetectEnemies = DetectEnemies;
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = DetectNeutrals;
			HearingConfig->DetectionByAffiliation.bDetectFriendlies = DetectFriendlies;
			HearingPerception->RequestStimuliListenerUpdate();
		}		
		break;		
	}	
}
