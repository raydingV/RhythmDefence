// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcSoldierParent.h"

#include "VectorTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANpcSoldierParent::ANpcSoldierParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcSoldierParent::BeginPlay()
{
	Super::BeginPlay();

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);
	
	FirstLocation = GetActorLocation();
}

// Called every frame
void ANpcSoldierParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameManagerClass != nullptr)
	{
		if(TagOfSoldier == GameManagerClass->ChargeSoldierTag)
		{
			TransformToObject(DeltaTime, false);
			SoldierCanFire = true;
		}
		else
		{
			TransformToObject(DeltaTime, true);
			SoldierCanFire = false;
		}
	}

	if(SoldierArray.Num() == SoldierFireArray.Num())
	{
		ResetSoldiers();
	}
}

void ANpcSoldierParent::TransformToObject(float DeltaTime, bool GetFirstLocation)
{
	CurrentLocation = GetActorLocation();
	// TargetRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
	// TargetRotation = FRotator3d(0, TargetRotation.Yaw / 4, 0);
	
	if(TargetLocation.Y <= CurrentLocation.Y && GetFirstLocation == false)
	{
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);
	}
	// else
	// {
	// 	TargetRotation = FMath::Lerp(GetActorRotation(), FRotator3d(0,0,0), DeltaTime * 2);
	// }

	if(GetFirstLocation == true && FirstLocation.Y >= CurrentLocation.Y)
	{
		Direction = (FirstLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);
	}

	IsFırstLocation = GetFirstLocation;
	SetActorRotation(TargetRotation);
}

void ANpcSoldierParent::ResetSoldiers()
{
	SoldierFireArray.Empty();
	SoldierFireArray.SetNum(0);
	GameManagerClass->ResetAll();
}



