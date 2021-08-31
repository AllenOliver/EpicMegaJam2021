// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/Color.h"
#include "EMJ_2021Character.generated.h"

#pragma region Forward Declarations
class UAC_Health;
class UAC_Shift;
class AEscapeGameMode_Base;
class APointLight;
#pragma endregion

UCLASS(config = Game)
class AEMJ_2021Character : public ACharacter
{
	GENERATED_BODY()

		//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShift);

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	AEMJ_2021Character();

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void TakeHit(int Amount, E_COLOR _attackingColor);

	//UPROPERTY(BlueprintAssignable)
	//FShift ShiftedEvent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Health* PlayerHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Shift* Shift;

	UPROPERTY(EditAnywhere)
		float BoomLength;

	UFUNCTION(BlueprintCallable, Category = "Shifting")
		void ShiftColors();

	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnShift();

	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDie();

private:
	AEscapeGameMode_Base* _escapeGameMode;

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

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
