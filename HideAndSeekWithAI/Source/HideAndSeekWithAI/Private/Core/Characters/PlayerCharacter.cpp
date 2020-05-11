// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

}

void APlayerCharacter::SetCurrentThrowableItem(UThrowable* InteractingItemToSet)
{
	CurrentThrowableItem = InteractingItemToSet;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	

	// Binding the camera to the HEAD SOCKET. We don't make this in ctr
	// because children components of character representation weren't initialized when ctr is called
	// If we find the HEAD SOCKET the camera gets attached to it, otherwise it uses default attachment to Root Component made in ctr
	TArray<USceneComponent*> ChildrenComponents;
	CharacterVisual->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* Child : ChildrenComponents)
	{
		if (Child->DoesSocketExist("Head"))
		{
			Camera->AttachToComponent(Child, FAttachmentTransformRules::KeepRelativeTransform, "Head");
			break;
		}
	}	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::Forward);
		PlayerInputComponent->BindAxis("Back", this, &APlayerCharacter::Back);
		PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::Right);
		PlayerInputComponent->BindAxis("Left", this, &APlayerCharacter::Left);
		PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
		
		
	}
	


}

void APlayerCharacter::Forward(float amount) 
{
	AddMovementInput(GetActorForwardVector(), amount);
}

void APlayerCharacter::Back(float amount)
{
	AddMovementInput(-GetActorForwardVector(), amount);
}

void APlayerCharacter::Right(float amount)
{
	AddMovementInput(GetActorRightVector(), amount);
}

void APlayerCharacter::Left(float amount)
{
	AddMovementInput(-GetActorRightVector(), amount);
}

void APlayerCharacter::Turn(float amount)
{
	AddControllerYawInput(amount);	
}

