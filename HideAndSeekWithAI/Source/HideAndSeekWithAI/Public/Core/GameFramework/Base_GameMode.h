// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Base_GameMode.generated.h"

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	
};
