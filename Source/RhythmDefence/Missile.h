// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class RHYTHMDEFENCE_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	FVector StartLocation;
	FVector InitialVelocity;
	FVector Acceleration;
	FVector Velocity;
	FRotator TargetRotation;
	
	float ElapsedTime;
	float Gravity;
	FVector NewLocation;

	FVector Direction;
	float maxPitch;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
