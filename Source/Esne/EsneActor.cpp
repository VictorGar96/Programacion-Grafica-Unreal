// Fill out your copyright notice in the Description page of Project Settings.


#include "EsneActor.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEsneActor, Display, All);

// Sets default values
AEsneActor::AEsneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CodeSphereComp"));
}

// Called when the game starts or when spawned
void AEsneActor::BeginPlay()
{
	Super::BeginPlay();

	// Reference component created from BP
	//
	//UActorComponent* pSphereComp = GetComponentByClass(USphereComponent::StaticClass());	
	//if (pSphereComp != nullptr)
	//{
	//	SphereComponent = Cast<USphereComponent>(pSphereComp);
	//}
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
	if (SphereComponent != nullptr)
	{
		SphereComponent->SetSphereRadius(SphereComponent->GetScaledSphereRadius() * 2.0f);
	}
}



