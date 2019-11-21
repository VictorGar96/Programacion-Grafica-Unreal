// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EsneCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "DrawDebugHelpers.h"

//
#include "EsneWidget.h"
#include "EsneHUD.h"
#include "EsneActor.h"
#include "Kismet/GameplayStatics.h"
//
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEsneCharacter, Display, All);


//////////////////////////////////////////////////////////////////////////
// AEsneCharacter

AEsneCharacter::AEsneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	m_pInteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor"));
	m_pInteractorComponent->SetupAttachment(RootComponent);
	m_pInteractorComponent->SetSphereRadius(InteractionRadius);

	// Collision settings
	//

	m_pInteractorComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	//m_pInteractorComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//m_pInteractorComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//m_pInteractorComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);


	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

    
}

void AEsneCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Bind to player input
	//
	if (InputComponent)
	{		
		InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AEsneCharacter::InteractPressed);
	}

	// Find all overlapping spheres
	//
	UCapsuleComponent* pCapsule = GetCapsuleComponent();
	if (pCapsule != nullptr)
	{
		TSet<AActor*> OverlappingActors;
		pCapsule->GetOverlappingActors(OverlappingActors, nullptr);

		for (AActor* pActor : OverlappingActors)
		{
			if (AEsneActor * pEsneActor = Cast<AEsneActor>(pActor))
			{
				// Found esne actor that overlaps with player's capsule
				IncrementOverlaps();
			}
		}
	}

	m_bInitialized = true;
	OnCharacterInitialized.Broadcast();
}

void AEsneCharacter::IncrementOverlaps()
{
	m_NumOverlaps++;
	UpdateWidgetInfo();
}

void AEsneCharacter::DecrementOverlaps()
{
	m_NumOverlaps--;
	UpdateWidgetInfo();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEsneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEsneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEsneCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEsneCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEsneCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEsneCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEsneCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AEsneCharacter::OnResetVR);
}

UEsneWidget* AEsneCharacter::GetEsneWidget(AEsneHUD* pEsneHUD) const
{
	// boilerplate code
	//
	 TArray<UUserWidget*> pWidgets = pEsneHUD->GetWidgets();

	 // Obtain esne widget by predicate using a lambda function
	 //
	 UUserWidget** pUserWidget = pWidgets.FindByPredicate([&](UUserWidget* pWidget) 
		 {
			 UEsneWidget* pEsneWidget = Cast<UEsneWidget>(pWidget);
			 return pEsneWidget != nullptr;
		 });

	 if (pUserWidget != nullptr)
	 {
		 return (UEsneWidget*) *pUserWidget;
	 }

	 
	 // Simple way of obtaining the esne widget
	 //
	 //for (UUserWidget* pWidget : pWidgets)
	 //{
		// UEsneWidget* pEsneWidget = Cast<UEsneWidget>(pWidget);
		// if (pEsneWidget != nullptr)
		// {
		//	 return pEsneWidget;
		// }
	 //}

	 return nullptr;
}


void AEsneCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEsneCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AEsneCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AEsneCharacter::UpdateWidgetInfo() const
{
	// Obtain EsneWidget object
	// Call SetOverlappingElemsNumber

	if (APlayerController * pController = Cast<APlayerController>(GetController()))
	{
		if (AEsneHUD * pEsneHUD = Cast<AEsneHUD>(pController->GetHUD()))
		{
			UEsneWidget* pEsneWidget = GetEsneWidget(pEsneHUD);
			if (pEsneWidget != nullptr)
			{
				pEsneWidget->SetOverlappingElemsNumber(m_NumOverlaps);
			}
		}
	}

	// Alternative way of obtaining player controller
	//
	//if (APlayerController * pController = UGameplayStatics::GetPlayerController(this, 0))
	//{

	//}
}

void AEsneCharacter::InteractPressed()
{
	UE_LOG(LogEsneCharacter, Display, TEXT("Interact pressed"));

	if (m_pInteractorComponent != nullptr)
	{
		AActor* pActor = m_pInteractorComponent->GetInteractionCandidate();
		if (AEsneActor * pEsneActor = Cast<AEsneActor>(pActor))
		{
			pEsneActor->OnInteract();
		}
	}
}


void AEsneCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEsneCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AEsneCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEsneCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
