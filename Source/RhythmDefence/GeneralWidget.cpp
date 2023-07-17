// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralWidget.h"

#include "Kismet/GameplayStatics.h"

void UGeneralWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);
}

void UGeneralWidget::ButtonX()
{
	if(GameManagerClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("X button"));
		GameManagerClass->ButtonX();
	}
}

void UGeneralWidget::ButtonA()
{
	if(GameManagerClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("A button"));
		GameManagerClass->ButtonA();
	}
}

void UGeneralWidget::ButtonB()
{
	if(GameManagerClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("B button"));
		GameManagerClass->ButtonB();
	}
}

void UGeneralWidget::ButtonY()
{
	if(GameManagerClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Y button"));
		GameManagerClass->ButtonY();
	}
}



