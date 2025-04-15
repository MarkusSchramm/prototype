/**
 * @file AudioPawnWalking.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IAudioPawnWalkingProvider.h"
#include "AudioPawnWalking.generated.h"

class UAudioPawnWalkingComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * @class AAudioPawnWalking
 * @brief Character class with walking movement and spatial audio support.
 * 
 * This class is based on ACharacter and provides support for camera handling, input mapping,
 * and audio feedback for walking interactions using a UAudioPawnWalkingComponent.
 */
UCLASS(config=Game)
class AUDIOPLAYERPAWN_API AAudioPawnWalking
	:	public ACharacter,
		public IAudioPawnWalkingProvider {
	GENERATED_BODY()

public:
	/**
	 * @brief Constructs a new AAudioPawnWalking.
	 * 
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	AAudioPawnWalking();

	/**
	 * @brief Constructs a new AAudioPawnWalking.
	 * @param ObjectInitializer for init about commandline or automation.
	 * 
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	explicit AAudioPawnWalking(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Destructs a AAudioPawnWalking.
	 * 
	 * Right now only for logging and tracing purposes
	 */
	virtual ~AAudioPawnWalking() override;

	/**
	 * @brief AAudioCharacter::Tick
	 * @param DeltaTime Delta actor should Tick.
	 * @see ACharacter::Tick
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief AAudioCharacter::SetupPlayerInputComponent
	 * @param PlayerInputComponent @see UInputComponent
	 * @see ACharacter::SetupPlayerInputComponent
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief inline getter for camera boom
	 * @return spring arm component
	 */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/**
	 * @brief inline getter for follow camera
	 * @return camera component
	 */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/**
	 * @interface IAudioPawnWalkingProvider
	 * @brief inline implementation of the audio pawn walking provider
	 * @return provides the underlying actor component to manage skeletal mesh based sounds
	 */
	FORCEINLINE virtual UAudioPawnWalkingComponent* GetAudioPawnWalkingComponent_Implementation() const override {
		return AudioComponent;
	}

protected:
	/**
	 * @brief AAudioCharacter::BeginPlay
	 * @see ACharacter::BeginPlay
	 */
	virtual void BeginPlay() override;
	
	/**
	 * @brief moves the character based on enhanced input
	 * @param Value enhanced input action that should be applied
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * @brief rotates the camera around the character based on enhanced input
	 * @param Value enhanced input action that should be applied
	 */
	void Look(const FInputActionValue& Value);

private:
    /**
     * @brief Spring arm component for positioning the camera behind the character.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /**
     * @brief Camera component that follows the character.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    /**
     * @brief Input mapping context for defining input configuration.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    /**
     * @brief Input action used for triggering jump.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /**
     * @brief Input action used for character movement.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /**
     * @brief Input action used for rotating the camera view.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    /**
     * @brief Audio component responsible for footstep and walking sound feedback.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAudioPawnWalkingComponent> AudioComponent;

    /**
     * @brief Configures this pawn to behave like a third-person character.
     */
    void ConstructAsThirdPerson();

    /**
     * @brief Initializes audio and camera behavior for third-person gameplay on BeginPlay.
     */
    void BeginPlayAsThirdPerson() const;

    /**
     * @brief Binds third-person specific input actions.
     * 
     * @param PlayerInputComponent Input component for bindings.
     */
    void SetupInputAsThirdPerson(UInputComponent* PlayerInputComponent);

    /**
     * @brief Handles movement input specifically for third-person configuration.
     * 
     * @param Value Movement input value.
     */
    void MoveAsThirdPerson(const FInputActionValue& Value);

    /**
     * @brief Handles camera look input for third-person mode.
     * 
     * @param Value Look input value.
     */
    void LookAsThirdPerson(const FInputActionValue& Value);
};
