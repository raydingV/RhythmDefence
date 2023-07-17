// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "Blueprint/UserWidget.h"
#include "GeneralWidget.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMDEFENCE_API UGeneralWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	AActor* GameManager;
	AGameManager* GameManagerClass;
	
	UPROPERTY(BlueprintReadWrite)
		bool CanClick;
	
	UFUNCTION(BlueprintCallable, Category = "ButtonX")
		void ButtonX();

	UFUNCTION(BlueprintCallable, Category = "ButtonA")
		void ButtonA();

	UFUNCTION(BlueprintCallable, Category = "ButtonB")
		void ButtonB();

	UFUNCTION(BlueprintCallable, Category = "ButtonY")
		void ButtonY();
};
