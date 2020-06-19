// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TrialAndErrorCPPCharacter.generated.h"

class APodManager;
UENUM(BlueprintType)
enum class ECameraStatus : uint8
{
	ECS_Idle		   UMETA(DisplayName = "Idle"),
	ECS_LookingUp      UMETA(DisplayName = "LookingUp"),
	ECS_GettingBack    UMETA(DisplayName = "GettingBack"),
	ECS_LockingOn	   UMETA(DisplayName = "LockingOn")

};

UCLASS(config=Game)
class ATrialAndErrorCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

															/*Pod Components Section*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ShoulderLocations, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* LeftShoulder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ShoulderLocations, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RightShoulder;

public:
	ATrialAndErrorCPPCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

															/*Pod Variables Section*/
	/* For Spawning Pod at BeginPlay*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PodProperties)
	bool bSpawnPod;

	/* Spawning Pod Manager */
	UPROPERTY(EditDefaultsOnly, Category = PodProperties)
	TSubclassOf<APodManager> PodManagerToSpawn;

																/*Camera Section*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraProperties)
	ECameraStatus CameraStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraProperties)
	float CameraYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraProperties)
	bool bCameraPropertiesChange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraProperties)
	uint8 bUseAccelerationForPaths : 1;

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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SpawnThePod();
	void CheckCameraStates();
	bool CameraNotLookingForward();
	bool CameraPitchBiggerOrEqualTo(float PitchValue);

	FORCEINLINE void SetCameraStatus(ECameraStatus Status) {CameraStatus = Status; }
	FORCEINLINE ECameraStatus GetCameraStatus() { return CameraStatus; }
};

