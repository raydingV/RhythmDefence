// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "Missile.h"
#include "NpcSoldierParent.h"
#include "GameFramework/Actor.h"
#include "SoldierNpc.generated.h"

UCLASS()
class RHYTHMDEFENCE_API ASoldierNpc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldierNpc();

	AActor* GameManager;
	AGameManager* GameManagerClass;

	UPROPERTY(EditAnywhere)
	AActor* Parent;
	ANpcSoldierParent* ParentClass;

	AActor* Arrow;
	AMissile* ArrowClass;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Mesh;
	
	FActorSpawnParameters SpawnParameters;

	UPROPERTY(EditAnywhere)
	UClass* MissileSpawn;

	bool SingleFire;

	UFUNCTION()
		void SoldierArrow();

	UFUNCTION()
		void SoldierFire();

	UFUNCTION()
		void SoldierLog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
