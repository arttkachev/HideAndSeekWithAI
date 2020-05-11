// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameEntities/Item.h"
#include "Core/GameEntities/Projectiles/ItemProjectile.h"
#include "Kismet/GameplayStatics.h"

void AItem::BeginPlay()
{
	Super::BeginPlay();

	// if the game will implement Save/Load system, SpawnLocation will be read from a file on Load
	SpawnLocation = GetActorLocation();
}

void AItem::PickUp_Implementation(APawn* PawnInstigator)
{
	// A pointer to ABase_GameCharacter guarantees that any game character will be able to throw items.
	// If someone will come tomorrow and say "we want NPCs to throw items too". Okay, no problem.
	// You can pass in any pawn that will be casted to ABase_GameCharacter because it is our base character
	if (!IsThrowableOwned()) // We can pick up if only no one has already picked it up
	{
		ABase_GameCharacter* Character = Cast<ABase_GameCharacter>(PawnInstigator);
		const bool IsAtAllowedDistance = Character->GetDistanceTo(this) <= Character->GetCharacterSettings().MinDistanceToPickUItems;

		if (IsAtAllowedDistance && Character)
		{
			SetActorEnableCollision(false);
			IsOwned = true;
			SetActorLocationAndRotation(Character->GetHandTransform().GetLocation(), Character->GetHandTransform().GetRotation());
			AttachToComponent(Character->GetCharacterVisual(), FAttachmentTransformRules::KeepWorldTransform, Character->GetHandSocketName());
			Character->SetCurrentItemInHand(this);
		}
	}	
}

void AItem::Throw_Implementation(APawn* PawnInstigator, float DistanceToThrow, FName NoiseTag)
{
	// A pointer to ABase_GameCharacter guarantees that any game character will be able to throw items.
	// If someone will come tomorrow and say "we want NPCs to throw items too". Okay, no problem.
	// You can pass in any pawn that will be casted to ABase_GameCharacter because it is our base game character representation
	ABase_GameCharacter* Character = Cast<ABase_GameCharacter>(PawnInstigator);

	if (ABase_GameActor* CurrentItemInHand = Character->GetCurrentItemInHand())
	{
		CurrentItemInHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UWorld* World = Character->GetWorld();
		if (World)
		{			
			ABase_Projectile* Projectile = World->SpawnActorDeferred<AItemProjectile>(AItemProjectile::StaticClass(), FTransform(CurrentItemInHand->GetActorLocation()), CurrentItemInHand, Character);

			if (Projectile)
			{
				// For projectile calculations we will use the location of the character (not the hand)
				// to minimize the error of the SuggestProjectileVelocity_CustomArc method
				Projectile->SetProjectileStartLocation(Character->GetActorLocation());
				Projectile->SetProjectileEndLocation((Character->GetActorForwardVector() * DistanceToThrow) + Character->GetActorLocation());
				Projectile->SetAttachedActor(this);
				Projectile->SetNoiseTag(NoiseTag);
				UGameplayStatics::FinishSpawningActor(Projectile, FTransform(CurrentItemInHand->GetActorRotation(), CurrentItemInHand->GetActorLocation()));
				CurrentItemInHand->AttachToActor(Projectile, FAttachmentTransformRules::KeepWorldTransform);
				Character->SetCurrentItemInHand(nullptr);
				SetActorEnableCollision(true);
				IsOwned = false;
			}
		}
	}
}



