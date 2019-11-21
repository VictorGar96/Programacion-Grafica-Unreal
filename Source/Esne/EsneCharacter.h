// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractorComponent.h"
#include "EsneCharacter.generated.h"

UCLASS(config=Game)
class AEsneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Boom", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:

	/** Character initialized delegate */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterInitialized);
	FCharacterInitialized OnCharacterInitialized;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Interaction radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	float InteractionRadius = 200.0f;

    UPROPERTY(Editanywhere, BlueprintReadWrite, Category = ActorToAttach)
    TSubclassOf<AActor> actorToAttach;

public:

	AEsneCharacter();

	/** Begin play */
	void BeginPlay() override;

	/** Increment Overlaps */
	void IncrementOverlaps();

	/** Decrement Overlaps */
	void DecrementOverlaps();

	/** Get num overlaps */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetNumOverlaps() { return m_NumOverlaps; }

	/** Is character initialized */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsCharacterInitialized() const { return m_bInitialized; }

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Update widget info */
	void UpdateWidgetInfo() const;

	/** Interact pressed handler */
	void InteractPressed();

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Get the esne widget instance */
	class UEsneWidget* GetEsneWidget(class AEsneHUD* pEsneHUD) const;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	/** Num of overlapping elements */
	UPROPERTY(Transient)
	int32 m_NumOverlaps = 0;

	/** Has the character been initialized */
	UPROPERTY(Transient)
	bool m_bInitialized = false;

	/** Interactor component */
	UPROPERTY(Transient)
	class UInteractorComponent* m_pInteractorComponent;
};

