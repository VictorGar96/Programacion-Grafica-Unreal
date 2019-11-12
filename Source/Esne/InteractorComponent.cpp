// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"
#include "DrawDebugHelpers.h"

UInteractorComponent::UInteractorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInteractorComponent::BeginPlay()
{
    Super::BeginPlay();
    SetComponentTickEnabled(true);
    OnComponentBeginOverlap.AddUniqueDynamic(this, &UInteractorComponent::OnBeginOverlap);
    OnComponentEndOverlap.AddUniqueDynamic(this, &UInteractorComponent::OnEndOverlap);

}

void UInteractorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (UInteractiveComponent* interactive = Cast<UInteractiveComponent>(OtherComp))
    {
        interactiveInRange.AddUnique(interactive);
        UE_LOG(LogTemp, Warning, TEXT("Interactive in range added"));
    }
}

void UInteractorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (UInteractiveComponent* interactive = Cast<UInteractiveComponent>(OtherComp))
    {
        interactiveInRange.Remove(interactive);
        UE_LOG(LogTemp, Warning, TEXT("Interactive no longer range, removed"));
    }
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Find nearest Candidate

    if (interactiveInRange.Num() > 0)
    {
        float minDistance = TNumericLimits<float>::Max();
        FVector interactorPosition = GetComponentLocation();
        for (auto* interactive : interactiveInRange)
        {
            float dist = FVector::Distance(interactorPosition, interactive->GetComponentLocation());
            if (dist < minDistance)
            {
                nearestInteractive = interactive;
                minDistance = dist;
            }
        }
    }
    else
    {
        nearestInteractive = nullptr;
    }
    if (nearestInteractive)
    {
        DrawDebugSphere
        (
            GetWorld(),
            nearestInteractive->GetComponentLocation(),
            50.f,
            10,
            FColorList::Blue,
            false,
            -1.0f,
            0,
            5.0f
        );
    }
}

AActor* UInteractorComponent::GetInteractorCandidate() const
{
    if (nearestInteractive != nullptr)
    {
        return nearestInteractive->GetOwner();
    }
    return nullptr;
}
