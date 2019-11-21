// Fill out your copyright notice in the Description page of Project Settings.

#include "EsneActor.h"
#include "EsneCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EsneCheatManager.h"

void UEsneCheatManager::Sillycheat()
{
    // Destroy all esneActors
    TArray<AActor*> allEsneActors;

    UGameplayStatics::GetAllActorsOfClass(this, AEsneActor::StaticClass(), allEsneActors);

    for (AActor* pActor : allEsneActors)
    {
        if (pActor != nullptr)
        {
            pActor->Destroy();
        }
    }

}

void UEsneCheatManager::AddBallToHand(const FName& socketName)
{

    if (AEsneCharacter* myCharacter = Cast<AEsneCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        USceneComponent* characterMesh = Cast<USceneComponent>(myCharacter->GetMesh());
    
        if (AActor* spawnActor = GetWorld()->SpawnActor(myCharacter->actorToAttach.Get()))
        {
           spawnActor->AttachToComponent(characterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), socketName);
        }
    }
}