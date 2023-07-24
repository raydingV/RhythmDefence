// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	Speed = 0;
	TargetLocation = FVector3d(0,0,0);

	Arrow = false;
	Fire = false;
	Log = false;
	SetRotation = true;
	Crate = false;
	CanTrigger = true;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	// İlk hız, ivme ve yerçekimini ayarla.
	InitialVelocity = FVector(0.f, 1000.f, 1000.f); // İleri hız ve yükseklik
	Acceleration = FVector(0.f, 0.f, -980.f);
	Gravity = 980.f;
	
	NewLocation = GetActorLocation();
	TargetRotation = FRotator3d(0,-180,-70);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Arrow == true)
	{
		ActArrow(DeltaTime, Speed);
	}
	
	if(Fire == true)
	{
		ActFire(DeltaTime);
	}

	if(Log == true)
	{
		ActLog(DeltaTime);
	}
	
	SetActorLocation(NewLocation);
	
	if(SetRotation == true)
	{
		SetActorRotation(TargetRotation);
	}

}

void AMissile::ActArrow(float DeltaTime, float speed)
{
	// N şekline fizik uygula.
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->WakeRigidBody();
	
	// Hesaplamaları güncelle.
	ElapsedTime += DeltaTime;
	
	// Yükseklik hesaplaması.
	float Height = StartLocation.Z + (InitialVelocity.Z * ElapsedTime) + (0.5f * Acceleration.Z * FMath::Square(ElapsedTime));
	NewLocation.Z = Height;

	NewLocation.Y -= speed * DeltaTime;

	if(TargetRotation.Roll <= 40)
	{
		TargetRotation.Roll += 50 * DeltaTime;
	}
	
	if(GetActorLocation().Z <= 435)
	{
		MeshComponent->SetSimulatePhysics(false);
		MeshComponent->WakeRigidBody();
		Arrow = false;
		CanTrigger = false;
		TargetRotation = FRotator3d(GetActorRotation().Pitch, 0, 130);
	}
}

void AMissile::ActFire(float DeltaTime)
{
	CurrentLocation = GetActorLocation();
	
	Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	NewLocation = CurrentLocation + (Direction * Speed * DeltaTime);
	
	TargetRotation = FMath::Lerp(GetActorRotation(), NewLocation.Rotation(), DeltaTime * 2);

	if(GetActorLocation().Z <= 435)
	{
		this->Destroy();
	}
}

void AMissile::ActLog(float _DeltaTime)
{
	if(Crate == false)
	{
		if(GetActorLocation().Y <= 120)
		{
			CanTrigger = true;
			TargetLocation.Z = 435;
			if(GetActorLocation().Z <= 435)
			{
				if(GetActorLocation().Y >= -2200)
				{
					TargetLocation = FVector3d(GetActorLocation().X, -2200, GetActorLocation().Z);
				}
				else
				{
					this->Destroy();
				}
			}
		}
		else
		{
			TargetRotation = FRotator3d(-90,0,0);
		}
	}
	else
	{
		CanTrigger = false;
		if(GetActorLocation().Z <= 435)
		{
			this->Destroy();
		}
		TargetRotation = FRotator3d(TargetRotation.Pitch + (300 * _DeltaTime),TargetRotation.Yaw + (300 * _DeltaTime),TargetRotation.Roll + (300 * _DeltaTime));
	}
	
	CurrentLocation = GetActorLocation();
	
	Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	NewLocation = CurrentLocation + (Direction * Speed * _DeltaTime);
}




