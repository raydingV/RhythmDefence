// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChargeSoldier = false;

	ChargeSoldierTag = 0;
	HealthOfCastle = 100;

	DefaultMaxSpawn = 3;
	SpawnNumForRound = 4;
	Min = 240;
	Max = 420;
	WaitForNewRound = 240;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnTime = FMath::RandRange(120,180);

	EnemyCheckActor = Cast<AEnemyCheck>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyCheck::StaticClass()));
	EnemyCheckClass = Cast<AEnemyCheck>(EnemyCheckActor);

	MaxSpawn = DefaultMaxSpawn;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnEnemys(DeltaTime);
}

void AGameManager::ChargeSoldiers()
{
	ChargeSoldier = true;
	CanMakeCombo = true;
}

void AGameManager::ButtonX()
{
	if(ChargeSoldier != true && (ButtonAInput == 0 && ButtonBInput == 0) && ChargeSoldierTag == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CHARGE"));
		ChargeSoldiers();
	}
	else if(ButtonAInput == 2 || ButtonBInput == 2)
	{
		ButtonXInput++;
	}
	else
	{
		ResetDefault();
	}
}

void AGameManager::ButtonA()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 1;
		ChargeSoldier = false;
	}
	else if(ChargeSoldier != true && CanMakeCombo == true && ButtonBInput == 0 && ButtonAInput < 2)
	{
		ButtonAInput++;
	}
	else
	{
		ResetDefault();
	}
}

void AGameManager::ButtonB()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 2;
		ChargeSoldier = false;
	}
	else if(ChargeSoldier != true && CanMakeCombo == true && ButtonAInput == 0 && ButtonBInput < 2)
	{
		ButtonBInput++;
	}
	else
	{
		ResetDefault();
	}
}

void AGameManager::ButtonY()
{
	if(ChargeSoldier == true)
	{
		ChargeSoldierTag = 3;
		ChargeSoldier = false;
	}
	else
	{
		ResetDefault();
	}
}

void AGameManager::ResetAll()
{
	ButtonXInput = 0;
	ButtonAInput = 0;
	ButtonBInput = 0;
	ButtonYInput = 0;
	ToResetCharge = true;
}

void AGameManager::ResetCharge()
{
	ChargeSoldierTag = 0;
	ChargeSoldier = false;
	CanMakeCombo = false;
	ToResetCharge = false;
}

void AGameManager::ResetDefault()
{
	ButtonXInput = 0;
	ButtonAInput = 0;
	ButtonBInput = 0;
	ButtonYInput = 0;
	ChargeSoldierTag = 0;
	ChargeSoldier = false;
	CanMakeCombo = false;
}



void AGameManager::SpawnEnemys(float _deltaTime)
{
	SpawnTime -= 1;

	if(SpawnTime <= 0 && MaxSpawn > 0)
	{
		RandomEnemy = FMath::RandRange(0,2);

		if(RandomEnemy == 2)
		{
			EnemySpawnNum = 1;
		}
		else
		{
			EnemySpawnNum = SpawnNumForRound;
		}
		
		for(int i = 0; i < EnemySpawnNum; i++)
		{
			FVector TranslationActor = FVector(FMath::RandRange(-250,20), FMath::RandRange(GetActorLocation().Y, GetActorLocation().Y + 100), GetActorLocation().Z);
			FTransform TransformActor = FTransform(GetActorRotation(), TranslationActor, FVector3d(1,1,1));
			EnemyActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnEnemy, GetActorTransform());
			EnemyClass = Cast<AEnemy>(EnemyActor);
			EnemyClass->TagOfEnemy = RandomEnemy;
			EnemyCheckClass->EnemyArr.Push(EnemyActor);
			EnemyActor->FinishSpawning(TransformActor);
		}
		
		SpawnTime = FMath::RandRange(Min,Max);
		MaxSpawn--;
	}

	if(MaxSpawn == 0 && EnemyCheckClass->EnemyArr.IsEmpty())
	{
		WaitForNewRound -= 1;
	}

	if(WaitForNewRound <= 0)
	{
		NewRound();
	}
}

void AGameManager::NewRound()
{
	WaitForNewRound = 240;
	DefaultMaxSpawn += 2;
	MaxSpawn = DefaultMaxSpawn;

	if(Min <= 120)
	{
		Min -= 60;
	}

	if(Max <= 240)
	{
		Max -= 60;
	}

	if(SpawnNumForRound <= 14)
	{
		SpawnNumForRound += 2;
	}

	UE_LOG(LogTemp, Warning, TEXT("NewRound"));
}





