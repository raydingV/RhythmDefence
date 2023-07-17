// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChargeSoldier = false;

	ChargeSoldierTag = 0;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManager::ChargeSoldiers()
{
	ChargeSoldier = true;
}

void AGameManager::ButtonX()
{
	if(ChargeSoldier != true)
	{
		ChargeSoldierTag = 0;
		ChargeSoldiers();
	}
}

void AGameManager::ButtonA()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 1;
		ChargeSoldier = false;
	}
}

void AGameManager::ButtonB()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 2;
		ChargeSoldier = false;
	}
}

void AGameManager::ButtonY()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 3;
		ChargeSoldier = false;
	}
}


