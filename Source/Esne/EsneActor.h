// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/SphereComponent.h"
#include "EsneActor.generated.h"

UCLASS()
class ESNE_API AEsneActor : public AActor
{
	GENERATED_BODY()
	
public:

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEsneDelegate, int, FrameNum);
    UPROPERTY(BlueprintAssignable)
    FEsneDelegate OnEsneTick;

	/** Interactive component */
	UPROPERTY(EditAnywhere)
	class UInteractiveComponent* InteractiveComponent;

public:	
	// Sets default values for this actor's properties
	AEsneActor();

	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Call a C++ method from BP
    UFUNCTION(BlueprintCallable)
    void FromBPToCpp();

    // Call a BP method from C++
    UFUNCTION(BlueprintImplementableEvent)
    void CppMethod();

	/** Begin overlap listener */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** End overlap listener */
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	/** Sphere component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColor DebugDrawColor;

	
};
