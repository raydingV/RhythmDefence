// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// İlk hız, ivme ve yerçekimini ayarla.
	InitialVelocity = FVector(0.f, 1000.f, 1000.f); // İleri hız ve yükseklik
	Acceleration = FVector(0.f, 0.f, -980.f); // Yerçekimi ivmesi, -980 birim/s^2 olsun
	Gravity = 980.f; // Yerçekimi ivmesi, 980 birim/s^2 olsun

	// N şekline fizik uygula.
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->WakeRigidBody();
	NewLocation = GetActorLocation();
	TargetRotation = FRotator3d(-50.000000,270.000000,-359.999999);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Hesaplamaları güncelle.
	ElapsedTime += DeltaTime;
	
	// Yükseklik hesaplaması.
	float Height = StartLocation.Z + (InitialVelocity.Z * ElapsedTime) + (0.5f * Acceleration.Z * FMath::Square(ElapsedTime));
	NewLocation.Z = Height;

	NewLocation.Y -= 1000 * DeltaTime;
	
	TargetRotation = FRotationMatrix::MakeFromX(NewLocation).Rotator();
	TargetRotation.Pitch -= 150;
	
	// Konumu güncelle.
	SetActorLocation(NewLocation);
	SetActorRotation(TargetRotation);
}

