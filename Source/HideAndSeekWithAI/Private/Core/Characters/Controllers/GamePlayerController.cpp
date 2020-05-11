// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Controllers/GamePlayerController.h"
#include "Core/GameEntities/Base_GameActor.h"
#include "Core/GameLibraries/GameFunctionLibrary.h"
#include "Core/GameEntities/Interfaces/Throwable.h"
#include "Kismet/KismetMathLibrary.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// cache our controlled character in a game type one time onBeginPlay
	ControlledCharacter = Cast<ABase_GameCharacter>(GetPawn());

	// Init
	MinThrowDistance = ControlledCharacter->GetCharacterSettings().MinThrowDistance;
	MaxThrowDistance = ControlledCharacter->GetCharacterSettings().MaxThrowDistance;
	MaxChargingThrowTime = ControlledCharacter->GetCharacterSettings().ThrowChargeTime;
}


AGamePlayerController::AGamePlayerController()
{
	// Setting Player team Index (opposite to AI team index)
	SetGenericTeamId(FGenericTeamId(UGameFunctionLibrary::JoinGameTeam(ETeam::Players)));
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ChargeThrowButtonDownTime = GetInputKeyTimeDown(ChargeThrowButton);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("LCM", EInputEvent::IE_Pressed, this, &AGamePlayerController::OnLCMPressed);
		InputComponent->BindAction("LCM", EInputEvent::IE_Released, this, &AGamePlayerController::OnLCMReleased);		
	}
}

void AGamePlayerController::OnLCMPressed()
{
	if (!ControlledCharacter->GetCurrentItemInHand())
	{
		FHitResult HitResult;
		const bool IsHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

		if (IsHit)
		{			
			const bool DoesImplementInterface = HitResult.Actor->GetClass()->ImplementsInterface(UThrowable::StaticClass());

			if (DoesImplementInterface)
			{				
				IThrowable::Execute_PickUp(HitResult.GetActor(), GetPawn());				
			}
		}
	}

	else
	{
		IsChargingThrow = true;
	}
}

void AGamePlayerController::OnLCMReleased()
{
	check(ControlledCharacter);	
	if (IsChargingThrow)
	{
		IsChargingThrow = false;
		ABase_GameActor* ItemToThrow = ControlledCharacter->GetCurrentItemInHand();		
		const float ThrowDistance = UKismetMathLibrary::MapRangeClamped(ChargeThrowButtonDownTime, MinChargingThrowTime, MaxChargingThrowTime, MinThrowDistance, MaxThrowDistance);
		const FVector Velocity = FVector(1.0f, 0.0f, 0.5);
		
		ABase_GameActor* ItemToThrowByControlledPawn = ControlledCharacter->GetCurrentItemInHand();
		
		if (ItemToThrowByControlledPawn)
		{
			IThrowable::Execute_Throw(ItemToThrowByControlledPawn, GetPawn(), ThrowDistance, TEXT("ItemFallen"));
		}
		
	}
}