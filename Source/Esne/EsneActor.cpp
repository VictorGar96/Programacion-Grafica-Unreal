// Fill out your copyright notice in the Description page of Project Settings.


#include "EsneActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogEsneActor, Display, All);

// Sets default values
AEsneActor::AEsneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEsneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEsneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UE_LOG(LogEsneActor, Display, TEXT("Hello"));
    CppMethod();

    // Broadcast the delegate, send parameter
    OnEsneTick.Broadcast(GFrameNumber);
}

// 
void AEsneActor::FromBPToCpp()
{
    FVector ActorPos = GetActorLocation();

    // Print every N frames
    if (GFrameNumber % 55 == 0)
    {
        /*
            UE_LOG(
                Category,
                LogLevel,
                Text,
                (variadic) Text parameters
        */
        UE_LOG(LogEsneActor, Warning, TEXT("Esto es un string, la posicion del actor es : %s"), *ActorPos.ToString());
    }
}



