// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "EsneHUD.generated.h"

/**
 * 
 */
UCLASS()
class ESNE_API AEsneHUD : public AHUD
{
	GENERATED_BODY()

public:

	// Widget classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UUserWidget>> Widgets;

public:

	// Begin play
	virtual void BeginPlay() override;

	/** Get all widgets */
	TArray<UUserWidget*> GetWidgets() const;

private:

	// Widget instances
	UPROPERTY(Transient)
	TArray<UUserWidget*> m_pWidgets;
};
