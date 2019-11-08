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

public:
    // Sets default values for this actor's properties
    AEsneActor();

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

protected:

    /** Sphere component */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        class USphereComponent* SphereComponent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FColor DebugDrawColor;
};
