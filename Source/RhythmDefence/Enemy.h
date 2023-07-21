// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class RHYTHMDEFENCE_API AEnemy : public AActor
{
	GENERATED_BODY()

	AMissile* MissileClass;

	UFUNCTION(BlueprintCallable)
		void HitByMissile(AActor* _MissileClass);

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Mesh;

	int Health;

	UPROPERTY(EditAnywhere)
	FVector3d TargetLocation;

	FVector3d CurrentLocation;

	FVector3d FirstLocation;

	FVector Direction;

	FVector NewLocation;

	FRotator TargetRotation;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
