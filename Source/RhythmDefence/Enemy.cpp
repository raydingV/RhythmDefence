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
	SetTransform = false;
	TagOfEnemey = -1;

	hitByLog = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TargetLocation.Y >= GetActorLocation().Y && hitByLog != true)
	{
		CurrentLocation = GetActorLocation();
	
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 150 * DeltaTime);

		SetActorLocation(NewLocation);
	}

	if(hitByLog == true)
	{
		if(TargetLocation.Y <= GetActorLocation().Y)
		{
			CurrentLocation = GetActorLocation();
	
			Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
			NewLocation = CurrentLocation + (Direction * 400 * DeltaTime);

			SetActorLocation(NewLocation);
		}
		else
		{
			TargetLocation = FirstLocation;
			hitByLog = false;
		}
	}
	
	if(Health <= 0)
	{
		this->Destroy();
	}

	if(SetTransform != true)
	{
		TransformActor();
	}
}

void AEnemy::HitByMissile(AActor* _MissileClass)
{
	MissileClass = Cast<AMissile>(_MissileClass);

	if(MissileClass != nullptr)
	{
		if(MissileClass->Arrow == true && MissileClass->CanTrigger == true)
		{
			Health -= 15;
		}

		if(MissileClass->Fire == true)
		{
			Health -= 25;
		}

		if(MissileClass->Log == true && MissileClass->Crate == false)
		{
			Health -= 10;
			TargetLocation.Y = GetActorLocation().Y - 200;
			hitByLog = true;
		}

		UE_LOG(LogTemp, Warning, TEXT("%d"), Health);

		MissileClass = nullptr;
		_MissileClass = nullptr;
	}
}

void AEnemy::TransformActor()
{
	if(TagOfEnemey == 0)
	{
		SetActorRotation(FRotator3d(0,0,-270));
	}
	else
	{
		SetActorLocation(FVector3d(GetActorLocation().X, GetActorLocation().Y, 150));
		SetActorRotation(FRotator3d(0,0,0));
	}
	
	TargetLocation = FVector3d(GetActorLocation().X,GetActorLocation().Y + 1800, GetActorLocation().Z);
	FirstLocation = TargetLocation;
	
	SetTransform = true;
}



