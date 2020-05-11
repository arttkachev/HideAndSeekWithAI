// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Controllers/Base_PlayerController.h"

ABase_PlayerController::ABase_PlayerController()
{
	bShowMouseCursor = 1;	
}

void ABase_PlayerController::BeginPlay()
{
	Super::BeginPlay();	
}

