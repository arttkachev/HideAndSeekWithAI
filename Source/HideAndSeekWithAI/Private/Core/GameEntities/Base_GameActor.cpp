// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameEntities/Base_GameActor.h"

// Sets default values
ABase_GameActor::ABase_GameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// We use a Scene Component like some sort of container (no hard coded references to static meshes) because designers may want to
	// put more meshes at some point. They will just put them under this container. No modifications in code.
	// It also makes the code more abstract. We don't want to know details and communicate with it
	// just using a GetChildrenComponents method
	GameActorVisual = CreateDefaultSubobject<USceneComponent>("GameActorVisual");
	GameActorVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	

}

// Called when the game starts or when spawned
void ABase_GameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_GameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

