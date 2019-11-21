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

	// ...
	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	/** Set overlapping elems number */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetOverlappingElemsNumber(int nElems);
};
