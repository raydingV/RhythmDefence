// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCheck.h"
#include "Missile.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class RHYTHMDEFENCE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(BlueprintReadWrite)
		AMissile* MissileClass;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;

	FActorSpawnParameters SpawnParameters;
	
	AActor* EnemyCheckActor;
	AEnemyCheck* EnemyCheckClass;

	UFUNCTION(BlueprintCallable)
	void HitByMissile(AActor* _MissileClass);

	UFUNCTION(BlueprintCallable)
		float HitToCastle(float _Health);

	UFUNCTION(BlueprintCallable)
		bool ArriveCastle();

	UFUNCTION()
		void SetTimeAttack();

	UFUNCTION()
		void TransformActor();

	UFUNCTION(BlueprintCallable)
		void HitByLava();

	UFUNCTION(BlueprintCallable)
		void DefaultSpeed();

	UFUNCTION()
		void SetSpeed();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> MeshArray;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Health;

	UPROPERTY(EditAnywhere)
	FVector3d TargetLocation;

	FVector3d CurrentLocation;

	FVector3d FirstLocation;

	FVector Direction;

	FVector NewLocation;

	FRotator TargetRotation;

	UPROPERTY(BlueprintReadOnly)
	int TagOfEnemy;
	
	UPROPERTY(BlueprintReadOnly)
		int AttackTimeDown;
	
	bool SetTransform;
	bool hitByLog;
	bool hitCastle;
	
	float Speed;
	float FirstSpeed;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
