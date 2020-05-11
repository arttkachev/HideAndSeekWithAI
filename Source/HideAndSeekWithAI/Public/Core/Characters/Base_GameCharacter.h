// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Core/AI/Interfaces/AIRecognizable.h"
#include "Core/Widgets/Base_GameWidget.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/DataTable.h"
#include "Base_GameCharacter.generated.h"

class ABase_GameActor;

USTRUCT(BlueprintType)
struct HIDEANDSEEKWITHAI_API FCharacterSettings : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	float DefaultWalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	float MinDistanceToPickUItems = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	float MinThrowDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	float MaxThrowDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	float ThrowChargeTime = 2.0f;	
	
};

UCLASS(Blueprintable)
class HIDEANDSEEKWITHAI_API ABase_GameCharacter : public ACharacter, public IGenericTeamAgentInterface, public IAIRecognizable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_GameCharacter();

	// getters
	FORCEINLINE FCharacterSettings GetCharacterSettings() const
	{
		return  CharacterSettings;
	}
	
	FORCEINLINE USceneComponent* GetCharacterVisual() const
	{
		return CharacterVisual;
	}

	FORCEINLINE FName GetHandSocketName() const
	{
		return  HandSocketName;
	}
	
	FORCEINLINE ABase_GameActor* GetCurrentItemInHand() const
	{
		return  CurrentItemInHand;
	}

	// interfaces
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIRecognizable")
	EAITeam GetAITeam();
	EAITeam GetAITeam_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,  Category = "AIRecognizable")
	void SetAITeam(const EAITeam AITeamToSet);
	void SetAITeam_Implementation(const EAITeam AITeamToSet);
	
	void SetCurrentItemInHand(ABase_GameActor* ItemToSet);
	FTransform GetHandTransform() const;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlappingHappened(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterSettings")
	FCharacterSettings CharacterSettings;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterSettings")
	TSubclassOf<UBase_GameWidget> WidgetOnTrigger;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "CharacterSettings")
	USceneComponent* CharacterVisual = nullptr;

	UPROPERTY()
	ABase_GameActor* CurrentItemInHand = nullptr;
	
	const FName HandSocketName = TEXT("Hand");	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSettings")
	EAITeam Team = EAITeam::AIEnemies;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

};
