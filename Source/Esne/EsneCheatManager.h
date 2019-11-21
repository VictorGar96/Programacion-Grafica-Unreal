// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "EsneCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class ESNE_API UEsneCheatManager : public UCheatManager
{
    GENERATED_BODY()


public:

    UFUNCTION(Exec)
    void Sillycheat();

    UFUNCTION(Exec)
    void AddBallToHand(const FName& socketName);

};
