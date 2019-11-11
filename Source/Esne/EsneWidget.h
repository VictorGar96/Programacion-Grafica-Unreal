// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EsneWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESNE_API UEsneWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    // Native on key down
    FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    UFUNCTION(BlueprintImplementableEvent)
    void SetOverlappingElemsNumber(int Elems);
};
