// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierNpc.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASoldierNpc::ASoldierNpc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TagOfSoldier = 0;
}

// Called when the game starts or when spawned
void ASoldierNpc::BeginPlay()
{
	Super::BeginPlay();
	
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);

	FirstLocation = GetActorLocation();
}

// Called every frame
void ASoldierNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameManagerClass != nullptr)
	{
		if(TagOfSoldier == GameManagerClass->ChargeSoldierTag)
		{
			ChargeThisSoldier(DeltaTime, false);
		}
		else
		{
			ChargeThisSoldier(DeltaTime, true);
		}
	}
}

void ASoldierNpc::ChargeThisSoldier(float DeltaTime, bool GetFirstLocation)
{
	CurrentLocation = GetActorLocation();
	
	if(TargetLocation.Y <= CurrentLocation.Y && GetFirstLocation == false)
	{
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);
	}
	if(TargetLocation.Y >= CurrentLocation.Y)
	{
		GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
	}

	if(GetFirstLocation == true && FirstLocation.Y >= CurrentLocation.Y)
	{
		Direction = (FirstLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);
	}
}


