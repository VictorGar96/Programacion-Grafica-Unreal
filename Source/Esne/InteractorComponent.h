// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractiveComponent.h"
#include "InteractorComponent.generated.h"

/**
 * 
 */
UCLASS()
class ESNE_API UInteractorComponent : public USphereComponent
{
	GENERATED_BODY()

public: 

	UInteractorComponent();

	/** Begin play */
	void BeginPlay() override;

	/** Begin overlap listener */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** End overlap listener */
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	AActor* GetInteractionCandidate() const;

protected:

	UPROPERTY(Transient)
	TArray<UInteractiveComponent*> m_interactivesInRange;

	UPROPERTY(Transient)
	UInteractiveComponent* m_pNearestInteractive = nullptr;
};
