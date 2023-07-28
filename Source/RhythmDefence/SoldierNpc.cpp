// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierNpc.h"

#include "ComponentUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASoldierNpc::ASoldierNpc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SingleFire = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	IsAttacking = false;
	Waiter = 60;
	SingleFire = false;
}

// Called when the game starts or when spawned
void ASoldierNpc::BeginPlay()
{
	Super::BeginPlay();
	
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);
	
	Parent = GetAttachParentActor();
	ParentClass = Cast<ANpcSoldierParent>(Parent);

	if(ParentClass != nullptr)
	{
		ParentClass->SoldierArray.Push(this);
	}

	SetActorRotation(FRotator3d(0,180,0));
	
	_TagOfSoldier = ParentClass->TagOfSoldier;
	
	FirstLocation = GetActorLocation();
}

// Called every frame
void ASoldierNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	OldLocation = GetActorLocation();
	
	SoldierArrow();
	SoldierFire();
	SoldierLog();

	if(IsAttacking == true)
	{
		Waiter -= 1;
		UE_LOG(LogTemp,Warning,TEXT("%d"), Waiter);
	}
}

void ASoldierNpc::SoldierArrow()
{
	if(ParentClass != nullptr && GameManagerClass->ChargeSoldierTag == 2)
	{
		if(GameManagerClass->ChargeSoldierTag == ParentClass->TagOfSoldier)
		{
			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonYInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->MeshComponent->SetStaticMesh(ArrowClass->MeshArray[2]);
					ArrowClass->Arrow = true;
					ArrowClass->Speed = 1600;
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}

			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->MeshComponent->SetStaticMesh(ArrowClass->MeshArray[2]);
					ArrowClass->Arrow = true;
					ArrowClass->Speed = 600;
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}
		}
	}
}

void ASoldierNpc::SoldierFire()
{
	if(ParentClass != nullptr && GameManagerClass->ChargeSoldierTag == 1)
	{
		if(GameManagerClass->ChargeSoldierTag == ParentClass->TagOfSoldier)
		{
			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, FVector3d(GetActorLocation().X,GetActorLocation().Y - 2120,960), FRotator3d(0,180,180), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->Meteor = true;
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,Arrow->GetActorLocation().Y,170);
					ArrowClass->SetRotation = false;
					ArrowClass->Fire = true;
					ArrowClass->Speed = 1000;
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}

			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonBInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,-3120.0,170);
					ArrowClass->Fire = true;
					ArrowClass->Speed = 2000;
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}
		}
	}
}

void ASoldierNpc::SoldierLog()
{
	if(ParentClass != nullptr && GameManagerClass->ChargeSoldierTag == 3)
	{
		if(GameManagerClass->ChargeSoldierTag == ParentClass->TagOfSoldier)
		{
			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, FVector3d(-40, GetActorLocation().Y - 200, GetActorLocation().Z), FRotator(0,0,0), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(-40,50,820);
					ArrowClass->Log = true;
					ArrowClass->Speed = 1000;
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}

			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonBInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				IsAttacking = true;
				if(MissileSpawn != nullptr && SingleFire == true && Waiter <= 0)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, FVector3d(GetActorLocation().X, GetActorLocation().Y - 200, GetActorLocation().Z + 200), GetActorRotation(), SpawnParameters);
					Arrow->SetActorScale3D(FVector3d(1,1,1));
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,-3000,170);
					ArrowClass->Log = true;
					ArrowClass->Crate = true;
					ArrowClass->Speed = 1500;
					ArrowClass->MeshComponent->SetStaticMesh(ArrowClass->MeshArray[1]);
					ParentClass->SoldierFireArray.Push(Arrow);
					Waiter = 60;
				}
			}
		}
	}
}

bool ASoldierNpc::IsWalking()
{
	if(OldLocation.Y != GetActorLocation().Y)
	{
		if(ParentClass->IsFırstLocation == true && ParentClass->FirstLocation.Y > ParentClass->CurrentLocation.Y)
		{
			SetActorRotation(FRotator3d(0,0,0));
		}
		else
		{
			SetActorRotation(FRotator3d(0,180,0));
		}
		return true;
	}
	else
	{
		SetActorRotation(FRotator3d(0,180,0));
		return false;
	}
}








