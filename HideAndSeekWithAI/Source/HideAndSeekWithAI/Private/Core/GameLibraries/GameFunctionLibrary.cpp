// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameLibraries/GameFunctionLibrary.h"
#include "Core/Characters/EnemyCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

uint8 UGameFunctionLibrary::JoinGameTeam(const ETeam Team)
{
	switch (Team)
	{
	case  ETeam::AIEnemies:
		
		return 0;
		
	case  ETeam::Players:

		return 1;
	}

	return 255; // No Team by default. 255 is a value for No Team specified by UE4
}

void UGameFunctionLibrary::StopGame(UObject* WorldContextObject, const TSubclassOf<UBase_GameWidget> WidgetToAppear)
{
	if (WorldContextObject)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

		if (PlayerController)
		{
			// Unpossesing a player to freeze him when he reached a game finish and focus on a UI message
			PlayerController->UnPossess();

			// Unpossesing all enemies in the world because the game finished
			TArray<AActor*>AllEnemyActors;
			UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AEnemyCharacter::StaticClass(), AllEnemyActors);

			//TODO A better way to stop the game than UnPossesing the controller 
			for (AActor* EnemyActor : AllEnemyActors)
			{
				AAIController* EnemyAIController = UAIBlueprintHelperLibrary::GetAIController(EnemyActor);

				if (EnemyAIController)
				{
					EnemyAIController->UnPossess();
				}
			}

			// Create a WinScreen

			if (WidgetToAppear)
			{
				UUserWidget* WinScreenWidget = CreateWidget<UBase_GameWidget>(PlayerController, WidgetToAppear);

				if (WinScreenWidget)
				{
					WinScreenWidget->AddToViewport();
					UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, WinScreenWidget);
				}
			}

			else
			{
				UGameplayStatics::OpenLevel(WorldContextObject, FName(*UGameplayStatics::GetCurrentLevelName(WorldContextObject)));
			}

		}
	}	
}
