/**
 * @file AudioPawnFlying.h
 * @author Markus Schramm
 */


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "Interfaces/IAudioPawnFlyingProvider.h"
#include "AudioPawnFlying.generated.h"

/**
 * @class AAudioPawnFlying
 * @brief A specialized pawn class that supports flying behavior with audio components.
 * 
 * This class inherits from ADefaultPawn and implements the IAudioPawnFlyingProvider interface.
 * It is designed to represent a flying pawn with integrated support for 3D audio spatialization and movement-based sound interaction.
 */
UCLASS()
class AUDIOPLAYERPAWN_API AAudioPawnFlying
	:	public ADefaultPawn,
		public IAudioPawnFlyingProvider {
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor.
	 * 
	 * Called when the object is created without a specific initializer.
	 */
	AAudioPawnFlying();

	/**
	 * @brief Constructor with an object initializer.
	 * 
	 * Enables advanced configuration via Unreal's object initializer mechanism.
	 * 
	 * @param ObjectInitializer The initializer used to construct and configure the object.
	 */
	explicit AAudioPawnFlying(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief Called every frame to update the actor.
	* 
	* Handles time-dependent behavior such as animation or sound updates.
	* 
	* @param DeltaTime Time elapsed since the last frame.
	*/
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief Returns the pawn's flying audio component.
	 * 
	 * Used by audio systems to query the specialized audio behavior tied to this pawn.
	 * 
	 * @return Pointer to the UAudioPawnFlyingComponent.
	 */
	FORCEINLINE virtual UAudioPawnFlyingComponent* GetAudioPawnFlyingComponent_Implementation() const override {
		return AudioComponent;
	}

	/**
	 * @brief Returns the pawn's movement component.
	 * 
	 * Allows querying of velocity or acceleration for dynamic audio feedback.
	 * 
	 * @return Pointer to the UPawnMovementComponent.
	 */
	FORCEINLINE virtual UPawnMovementComponent* GetAudioPawnFlyingMovementComponent_Implementation() const override {
		return GetMovementComponent();
	}

	/**
	 * @brief Returns the pawn's mesh component.
	 * 
	 * Used for spatial positioning of sound sources relative to the pawn's visual representation.
	 * 
	 * @return Pointer to the UMeshComponent.
	 */
	FORCEINLINE virtual UMeshComponent* GetAudioPawnFlyingMeshComponent_Implementation() const override {
		return GetMeshComponent();
	}
	
protected:
	/**
	 * @brief Called when the game starts or when the pawn is spawned.
	 * 
	 * Use this function to initialize components, bind events, or configure runtime properties.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Flying audio component responsible for spatialized sound behavior.
	 * 
	 * This component can be assigned in the editor and is used to drive sound behavior related to flying mechanics.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<UAudioPawnFlyingComponent> AudioComponent;
};
