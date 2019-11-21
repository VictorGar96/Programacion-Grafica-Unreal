// Fill out your copyright notice in the Description page of Project Settings.


#include "EsneWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogEsneWidget, Display, All);

FReply UEsneWidget::NativeOnKeyDown(const FGeometry& InGeometry,
	const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogEsneWidget, Display, TEXT("Key [%s] down"), *InKeyEvent.GetKey().ToString());
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}