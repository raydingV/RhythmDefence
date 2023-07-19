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
	CanMakeCombo = true;
}

void AGameManager::ButtonX()
{
	if(ChargeSoldier != true && (ButtonAInput == 0 && ButtonBInput == 0))
	{
		ChargeSoldierTag = 0;
		ChargeSoldiers();
	}
	else if(ButtonAInput == 2 || ButtonBInput == 2)
	{
		ButtonXInput++;
	}
	else
	{
		ResetAll();
	}
}

void AGameManager::ButtonA()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 1;
		ChargeSoldier = false;
	}
	else if(ChargeSoldier != true && CanMakeCombo == true && ButtonBInput == 0)
	{
		ButtonAInput++;
	}
	else
	{
		ResetAll();
	}
}

void AGameManager::ButtonB()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 2;
		ChargeSoldier = false;
	}
	else if(ChargeSoldier != true && CanMakeCombo == true && ButtonAInput == 0)
	{
		ButtonBInput++;
	}
	else
	{
		ResetAll();
	}
}

void AGameManager::ButtonY()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 3;
		ChargeSoldier = false;
	}
	else
	{
		ResetAll();
	}
}

void AGameManager::ResetAll()
{
	ChargeSoldierTag = 0;
	ButtonXInput = 0;
	ButtonAInput = 0;
	ButtonBInput = 0;
	ButtonYInput = 0;
	ChargeSoldier = false;
	CanMakeCombo = false;
}



