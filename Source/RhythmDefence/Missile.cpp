// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	// BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	Speed = 0;
	TargetLocation = FVector3d(0,0,0);

	Arrow = false;
	Fire = false;
	Log = false;
	SetRotation = true;
	Crate = false;
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
	TargetRotation = FRotator3d(-50.000000,270.000000,-359.999999);
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
	
	TargetRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
	TargetRotation.Pitch -= 150;
}

void AMissile::ActFire(float DeltaTime)
{
	CurrentLocation = GetActorLocation();
	
	Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	NewLocation = CurrentLocation + (Direction * Speed * DeltaTime);
	
	TargetRotation = FMath::Lerp(GetActorRotation(), Direction.Rotation(), DeltaTime * 2);
}

void AMissile::ActLog(float _DeltaTime)
{
	if(Crate == false)
	{
		if(GetActorLocation().Y <= 120)
		{
			TargetLocation.Z = 170;
			if(GetActorLocation().Z <= 170)
			{
				TargetLocation = FVector3d(GetActorLocation().X, -2200, GetActorLocation().Z);
			}
		}
		else
		{
			TargetRotation = FRotator3d(-90,0,0);
		}
	}
	else
	{
		if(GetActorLocation().Z <= 170)
		{
			this->Destroy();
		}
		TargetRotation = FRotator3d(TargetRotation.Pitch + (300 * _DeltaTime),TargetRotation.Yaw + (300 * _DeltaTime),TargetRotation.Roll + (300 * _DeltaTime));
	}
	
	CurrentLocation = GetActorLocation();
	
	Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	NewLocation = CurrentLocation + (Direction * Speed * _DeltaTime);
}




