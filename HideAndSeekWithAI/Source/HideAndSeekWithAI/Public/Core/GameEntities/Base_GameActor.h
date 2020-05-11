// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_GameActor.generated.h"

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_GameActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_GameActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GameActor")
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GameActor")
	USceneComponent* GameActorVisual = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
