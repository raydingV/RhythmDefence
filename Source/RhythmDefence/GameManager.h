// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyCheck.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class RHYTHMDEFENCE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UFUNCTION()
		void ChargeSoldiers();

	UFUNCTION()
		void ButtonX();

	UFUNCTION()
		void ButtonA();

	UFUNCTION()
		void ButtonB();

	UFUNCTION()
		void ButtonY();

	UFUNCTION()
		void ResetAll();

	UFUNCTION()
		void SpawnEnemys(float _deltaTime);

	UFUNCTION(BlueprintCallable)
		void ResetCharge();

	UFUNCTION()
		void ResetDefault();

	UFUNCTION()
		void NewRound();

	bool ChargeSoldier;
	bool CanMakeCombo;

	UPROPERTY(BlueprintReadOnly)
	bool ToResetCharge;

	int ChargeSoldierTag;

	int ButtonXInput;
	int ButtonAInput;
	int ButtonBInput;
	int ButtonYInput;

	int RandomEnemy;

	int EnemySpawnNum;
	int SpawnNumForRound;
	int MaxSpawn;
	int DefaultMaxSpawn;
	
	int Min;
	int Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HealthOfCastle;
	
	float SpawnTime;
	float WaitForNewRound;
	
	UPROPERTY(EditAnywhere)
		FVector EnemySpawnLocation;
	UPROPERTY(EditAnywhere)
		FRotator EnemeySpawnRotation;

	UPROPERTY(EditAnywhere)
		UClass* SpawnEnemy;

	AActor* EnemyActor;
	AEnemy* EnemyClass;

	AActor* EnemyCheckActor;
	AEnemyCheck* EnemyCheckClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
