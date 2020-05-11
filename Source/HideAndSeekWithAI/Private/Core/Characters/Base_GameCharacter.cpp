// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Base_GameCharacter.h"
#include "Perception/AISense_Sight.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABase_GameCharacter::ABase_GameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// We use a Scene Component like some sort of container (no hard coded references to static meshes) because designers may want to
	// put more meshes at some point. They will just put them under this container. No modifications in code.
	// It also makes the code more abstract. We don't want to know details and communicate with it
	// just using a GetChildrenComponents method
	CharacterVisual = CreateDefaultSubobject<USceneComponent>("CharacterRepresentation");
	CharacterVisual->SetupAttachment(RootComponent);

	//CharacterInitializationData = FCharacterInitData();
}

EAITeam ABase_GameCharacter::GetAITeam_Implementation()
{
	switch (GetAITeamId())
	{
	case 0:
		return EAITeam::Players;
		break;

	case 1:
		return EAITeam::AIEnemies;
		break;

	case 255:
		return EAITeam::Neutrals;
		break;	
	}
	
	return EAITeam();
}

void ABase_GameCharacter::SetAITeam_Implementation(const EAITeam AITeamToSet)
{	
	switch (AITeamToSet)
	{
	case EAITeam::Players:
		AITeamId = FGenericTeamId(0);		
		break;

	case EAITeam::AIEnemies:
		AITeamId = FGenericTeamId(1);
		break;

	case EAITeam::Neutrals:		 
		AITeamId = FGenericTeamId(255);; // 255 is a default value for neutrals specified by UE4
		break;
	}
	
	UAIPerceptionSystem* MyPerceptionSystem = UAIPerceptionSystem::GetCurrent(this);
	if (MyPerceptionSystem)
	{
		MyPerceptionSystem->UnregisterSource(*this);
		MyPerceptionSystem->RegisterSource<UAISense_Sight>(*this);
	}
	
}

void ABase_GameCharacter::SetCurrentItemInHand(ABase_GameActor* ItemToSet)
{
	CurrentItemInHand = ItemToSet;	
}

FTransform ABase_GameCharacter::GetHandTransform() const
{
	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(true, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (Child->DoesSocketExist(HandSocketName))
		{
			return Child->GetSocketTransform(HandSocketName);
		}
	}

	return FTransform();
}

// Called when the game starts or when spawned
void ABase_GameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = CharacterSettings.DefaultWalkSpeed;	
	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(true, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Child))
		{
			StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABase_GameCharacter::OnOverlappingHappened);
		}
	}
	
	
}

// Called every frame
void ABase_GameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_GameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABase_GameCharacter::OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

