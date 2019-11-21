// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractorComponent, Display, All);

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
	if (UInteractiveComponent * pInteractive = Cast<UInteractiveComponent>(OtherComp))
	{
		m_interactivesInRange.AddUnique(pInteractive);
		UE_LOG(LogInteractorComponent, Display, TEXT("Elems : %d"), m_interactivesInRange.Num());
	}
}

void UInteractorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UInteractiveComponent * pInteractive = Cast<UInteractiveComponent>(OtherComp))
	{
		m_interactivesInRange.Remove(pInteractive);
		UE_LOG(LogInteractorComponent, Display, TEXT("Elems : %d"), m_interactivesInRange.Num());
	}
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Find nearest interactive
	//
	if (m_interactivesInRange.Num() > 0)
	{
		float minDistance = TNumericLimits<float>::Max();
		FVector InteractorPosition = GetComponentLocation();
		for (auto* pInteractive : m_interactivesInRange)
		{
			float dist = FVector::Distance(InteractorPosition, pInteractive->GetComponentLocation());
			if (dist < minDistance)
			{
				m_pNearestInteractive = pInteractive;
				minDistance = dist;
			}
		}
	}
	else
	{
		m_pNearestInteractive = nullptr;
	}

	if (m_pNearestInteractive)
	{
		DrawDebugSphere(GetWorld(), m_pNearestInteractive->GetComponentLocation(), 30.0f, 10, FColorList::DustyRose, false, -1.0f, 0, 5.0f);
	}
}

AActor* UInteractorComponent::GetInteractionCandidate() const
{
	if (m_pNearestInteractive != nullptr)
	{
		return m_pNearestInteractive->GetOwner();
	}
	return nullptr;
}


