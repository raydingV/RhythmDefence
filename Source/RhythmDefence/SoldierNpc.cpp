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
}

// Called every frame
void ASoldierNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SoldierArrow();
	SoldierFire();
	SoldierLog();
}

void ASoldierNpc::SoldierArrow()
{
	if(ParentClass != nullptr && GameManagerClass->ChargeSoldierTag == 2)
	{
		if(GameManagerClass->ChargeSoldierTag == ParentClass->TagOfSoldier)
		{
			if(GameManagerClass->ButtonBInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->Arrow = true;
					ArrowClass->Speed = 1500;
					ParentClass->SoldierFireArray.Push(Arrow);
				}
			}

			if(GameManagerClass->ButtonAInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->Arrow = true;
					ArrowClass->Speed = 300;
					ParentClass->SoldierFireArray.Push(Arrow);
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
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, FVector3d(GetActorLocation().X,GetActorLocation().Y - 1120,960), FRotator3d(0,180,180), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,Arrow->GetActorLocation().Y,170);
					ArrowClass->SetRotation = false;
					ArrowClass->Fire = true;
					ArrowClass->Speed = 1000;
					ParentClass->SoldierFireArray.Push(Arrow);
				}
			}

			if(GameManagerClass->ButtonBInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,-2100,170);
					ArrowClass->Fire = true;
					ArrowClass->Speed = 2000;
					ParentClass->SoldierFireArray.Push(Arrow);
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
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					Arrow->SetActorScale3D(FVector3d(1,1,1));
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(-290,50,820);
					ArrowClass->Log = true;
					ArrowClass->Speed = 1000;
					ArrowClass->MeshComponent->SetStaticMesh(ArrowClass->MeshArray[0]);
					ParentClass->SoldierFireArray.Push(Arrow);
				}
			}

			if(GameManagerClass->ButtonBInput == 2 && GameManagerClass->ButtonXInput == 1)
			{
				SingleFire = ParentClass->SoldierCanFire;
				if(MissileSpawn != nullptr && SingleFire == true)
				{
					Arrow = GetWorld()->SpawnActor<AActor>(MissileSpawn, GetActorLocation(), GetActorRotation(), SpawnParameters);
					Arrow->SetActorScale3D(FVector3d(1,1,1));
					ArrowClass = Cast<AMissile>(Arrow);
					ArrowClass->TargetLocation = FVector3d(GetActorLocation().X,-1590,170);
					ArrowClass->Log = true;
					ArrowClass->Crate = true;
					ArrowClass->Speed = 1500;
					ArrowClass->MeshComponent->SetStaticMesh(ArrowClass->MeshArray[1]);
					ParentClass->SoldierFireArray.Push(Arrow);
				}
			}
		}
	}
}







