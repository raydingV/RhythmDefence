// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/Actor.h"
#include "NpcSoldierParent.generated.h"

UCLASS()
class RHYTHMDEFENCE_API ANpcSoldierParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANpcSoldierParent();

	AActor* GameManager;
	AGameManager* GameManagerClass;
	
	UFUNCTION()
		void TransformToObject(float DeltaTime, bool GetFirstLocation);

	UFUNCTION()
		void ResetSoldiers();

	UPROPERTY(EditAnywhere)
	int TagOfSoldier;

	UPROPERTY(EditAnywhere)
	FVector3d TargetLocation;

	FVector3d CurrentLocation;

	FVector3d FirstLocation;

	FVector Direction;

	FVector NewLocation;

	FRotator TargetRotation;

	TArray<AActor*>SoldierFireArray;
	TArray<AActor*>SoldierArray;

	bool SoldierCanFire;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
