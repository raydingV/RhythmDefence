// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Health = 100;

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = FVector3d(GetActorLocation().X,GetActorLocation().Y + 1700,GetActorLocation().Z);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TargetLocation.Y >= GetActorLocation().Y)
	{
		CurrentLocation = GetActorLocation();
	
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 150 * DeltaTime);

		SetActorLocation(NewLocation);
	}
	
	if(Health <= 0)
	{
		this->Destroy();
	}
}

void AEnemy::HitByMissile(AActor* _MissileClass)
{
	MissileClass = Cast<AMissile>(_MissileClass);

	if(MissileClass != nullptr)
	{
		if(MissileClass->Arrow == true)
		{
			Health -= 50;
		}

		if(MissileClass->Fire == true)
		{
			Health -= 25;
		}

		if(MissileClass->Log == true)
		{
			Health -= 10;
			SetActorLocation(FVector3d(GetActorLocation().X, GetActorLocation().Y - 100, GetActorLocation().Z));
		}

		UE_LOG(LogTemp, Warning, TEXT("%d"), Health);

		MissileClass = nullptr;
		_MissileClass = nullptr;
	}
}


