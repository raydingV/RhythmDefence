// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	bool ChargeSoldier;
	bool CanMakeCombo;

	int ChargeSoldierTag;

	int ButtonXInput;
	int ButtonAInput;
	int ButtonBInput;
	int ButtonYInput;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
