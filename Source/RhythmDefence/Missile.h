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

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> MeshArray;

	UPROPERTY(EditAnywhere)
		UClass* Lava;
	
	UFUNCTION()
		void ActArrow(float DeltaTime, float Speed);
	
	UFUNCTION()
		void ActFire(float DeltaTime);

	UFUNCTION()
		void ActLog(float _DeltaTime);

	FVector TargetLocation;
	FVector CurrentLocation;
	FVector StartLocation;
	FVector InitialVelocity;
	FVector Acceleration;
	FVector Velocity;
	
	FRotator TargetRotation;
	
	float ElapsedTime;
	float Gravity;
	float Speed;
	
	FVector NewLocation;

	FVector Direction;
	float maxPitch;

	UPROPERTY(BlueprintReadOnly)
		bool Arrow;
	UPROPERTY(BlueprintReadOnly)
		bool Fire;
	UPROPERTY(BlueprintReadOnly)
		bool Log;
	UPROPERTY(BlueprintReadOnly)
		bool CanTrigger;
	
	bool SetRotation;
	bool Crate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
