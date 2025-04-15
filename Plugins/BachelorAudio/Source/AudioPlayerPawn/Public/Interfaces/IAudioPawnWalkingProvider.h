/**
 * @file IAudioPawnWalkingProvider.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAudioPawnWalkingProvider.generated.h"

class UAudioPawnWalkingComponent;
class UMovementComponent;
class USkeletalMeshComponent;

/**
 * @interface UAudioPawnWalkingProvider
 * @brief Interface duplication to get the interface into the unreal engine reflection system
 * @see UInterface
 * @see IAudioPawnWalkingProvider
 */
UINTERFACE(BlueprintType)
class AUDIOPLAYERPAWN_API UAudioPawnWalkingProvider : public UInterface {
	GENERATED_BODY()
};

/**
 * @interface IAudioPawnWalkingProvider
 * @brief Interface to get a pointer to UAudioPawnFlyingComponent.
 *
 * If you want this Interface to be overrideable in C++ and Blueprints, you have to follow this Syntax:
 * Implementation:	virtual GetAudioPawnWalkingComponent_Implementation() override;
 * Check:			GetOwner()->GetClass()->ImplementsInterface(UAudioPawnWalkingProvider::StaticClass());
 * Execution:		IAudioPawnWalkingProvider::Execute_GetAudioPawnWalkingComponent(ContextObject);
 */
class AUDIOPLAYERPAWN_API IAudioPawnWalkingProvider {
	GENERATED_BODY()

public:
	/**
	 * @brief gives a pointer to AudioPawnWalkingComponent, to be able to avoid unnecessary casts.
	 * @return pointer to AudioPawnWalkingComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Audio Component"))
	UAudioPawnWalkingComponent* GetAudioPawnWalkingComponent() const;

	/**
	 * @brief gives a pointer to UMovementComponent, to be able to avoid unnecessary casts.
	 * @return pointer to UMovementComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Movement Component"))
	UMovementComponent* GetAudioPawnWalkingMovementComponent() const;

	/**
	 * @brief gives a pointer to USkeletalMeshComponent, to be able to avoid unnecessary casts.
	 * @return pointer to USkeletalMeshComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Mesh Component"))
	USkeletalMeshComponent* GetAudioPawnWalkingMeshComponent() const;
};