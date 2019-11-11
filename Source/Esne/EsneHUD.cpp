// Fill out your copyright notice in the Description page of Project Settings.


#include "EsneHUD.h"

void AEsneHUD::BeginPlay()
{
    Super::BeginPlay();

    for (TSubclassOf<UUserWidget>& pWidget : Widgets)
    {
        if (pWidget != nullptr)
        {
            UUserWidget* pUserWidget = NewObject<UUserWidget>(this, *pWidget);
            if (pUserWidget != nullptr)
            {
                m_pWidgets.Add(pUserWidget);
                pUserWidget->AddToViewport();
            }
        }
    }
}

TArray<UUserWidget*> AEsneHUD::GetWidgets() const
{
    return m_pWidgets;
}
