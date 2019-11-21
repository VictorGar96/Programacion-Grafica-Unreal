// Fill out your copyright notice in the Description page of Project Settings.


#include "EsneActor.h"
#include "EsneCharacter.h"
#include "InteractiveComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEsneActor, Display, All);

// Sets default values
AEsneActor::AEsneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CodeSphereComp"));
	InteractiveComponent = CreateDefaultSubobject<UInteractiveComponent>(TEXT("Interactive"));
	InteractiveComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEsneActor::BeginPlay()
{
	Super::BeginPlay();

	// Listen to sphere's begin overlap
	//
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEsneActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AEsneActor::OnEndOverlap);

	// Delayed initialization 
	//
	/*


	if (character is initialized)
	{
		update whatever
	}
	else
	{
		subscribe to character.OnCharacterInitialized
			then -> update whatever
	}


	*/
}

// Called every frame
void AEsneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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


void AEsneActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEsneCharacter* pEsneCharacter = Cast<AEsneCharacter>(OtherActor))
	{
		pEsneCharacter->IncrementOverlaps();
	}
}

void AEsneActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEsneCharacter * pEsneCharacter = Cast<AEsneCharacter>(OtherActor))
	{
		pEsneCharacter->DecrementOverlaps();
	}
}


