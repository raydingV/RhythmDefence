// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
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
		int TagOfSoldier;

	UFUNCTION()
		void ChargeThisSoldier(float DeltaTime, bool GetFirstLocation);

	UPROPERTY(EditAnywhere)
		FVector3d TargetLocation;

	FVector3d CurrentLocation;

	FVector3d FirstLocation;

	FVector Direction;

	FVector NewLocation;

	FActorSpawnParameters SpawnParameters;

	UPROPERTY(EditAnywhere)
		UClass* MissileSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
