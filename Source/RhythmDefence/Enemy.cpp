// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Health = 100;

	RootComponent = Mesh;
	SetTransform = false;
	TagOfEnemy = -1;

	hitByLog = false;
	hitCastle = false;

	Speed = 150;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetSkeletalMesh(MeshArray[TagOfEnemy]);
	SetTimeAttack();
	SetSpeed();

	EnemyCheckActor = Cast<AEnemyCheck>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyCheck::StaticClass()));
	EnemyCheckClass = Cast<AEnemyCheck>(EnemyCheckActor);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TargetLocation.Y >= GetActorLocation().Y && hitByLog != true)
	{
		CurrentLocation = GetActorLocation();
	
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * Speed * DeltaTime);

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
		EnemyCheckClass->EnemyArr.Remove(this);
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
			if(TagOfEnemy == 0)
			{
				Health -= 50;
			}
			
			if(TagOfEnemy == 1)
			{
				Health -= 50;
			}

			if(TagOfEnemy == 2)
			{
				Health -= 15;
			}
		}

		if(MissileClass->Fire == true)
		{
			Health -= 25;
		}

		if(MissileClass->Log == true && MissileClass->Crate == false)
		{
			if(TagOfEnemy == 1)
			{
				Health -= 100;
			}
			else
			{
				Health -= 10;
			}
		
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
	if(TagOfEnemy == 0)
	{
		SetActorRotation(FRotator3d(0,0,0));
	}
	else
	{
		SetActorLocation(FVector3d(GetActorLocation().X, GetActorLocation().Y, 430));
		SetActorRotation(FRotator3d(0,0,0));
	}
	
	TargetLocation = FVector3d(GetActorLocation().X,GetActorLocation().Y + 2800, GetActorLocation().Z);
	FirstLocation = TargetLocation;
	
	SetTransform = true;
}

float AEnemy::HitToCastle(float _Health)
{
	if(TagOfEnemy == 0)
	{
		_Health -= 1;
	}

	if(TagOfEnemy == 1)
	{
		_Health -= 8;
	}

	if(TagOfEnemy == 2)
	{
		_Health -= 30;
	}

	return _Health;
}

bool AEnemy::ArriveCastle()
{
	if(GetActorLocation().Y >= -560)
	{
		hitCastle = true;
	}
	else
	{
		hitCastle = false;
	}

	return hitCastle;
}

void AEnemy::SetTimeAttack()
{
	if(TagOfEnemy == 0)
	{
		AttackTimeDown = 1;
	}
	
	if(TagOfEnemy == 1)
	{
		AttackTimeDown = 3;
	}
	
	if(TagOfEnemy == 2)
	{
		AttackTimeDown = 6;
	}
}

void AEnemy::SetSpeed()
{
	if(TagOfEnemy == 2)
	{
		Speed = 90;
	}

	FirstSpeed = Speed;
}


void AEnemy::HitByLava()
{
	Speed /= 2;
}

void AEnemy::DefaultSpeed()
{
	Speed = FirstSpeed;
}






