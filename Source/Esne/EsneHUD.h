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
    virtual void BeginPlay() override;

    // Widget clases
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<UUserWidget>> Widgets;

    UFUNCTION()
    TArray<UUserWidget*> GetWidgets() const;

private:

    // Widget instances
    UPROPERTY(Transient)
    TArray<UUserWidget*> m_pWidgets;

};
