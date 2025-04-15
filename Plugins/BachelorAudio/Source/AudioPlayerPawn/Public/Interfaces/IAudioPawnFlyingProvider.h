/**
 * @file IAudioPawnFlyingProvider.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAudioPawnFlyingProvider.generated.h"

class UAudioPawnFlyingComponent;
class UPawnMovementComponent;

/**
 * @interface UAudioPawnFlyingProvider
 * @brief Interface duplication to get the interface into the unreal engine reflection system
 * @see UInterface
 * @see IAudioPawnFlyingProvider
 */
UINTERFACE(BlueprintType)
class AUDIOPLAYERPAWN_API UAudioPawnFlyingProvider : public UInterface {
	GENERATED_BODY()
};

/**
 * @interface IAudioPawnFlyingProvider
 * @brief Interface to get a pointer to UAudioPawnFlyingComponent.
 *
 * If you want this Interface to be overrideable in C++ and Blueprints, you have to follow this Syntax:
 * Implementation:	virtual GetAudioPawnFlyingComponent_Implementation() override;
 * Check:			GetOwner()->GetClass()->ImplementsInterface(UAudioPawnFlyingProvider::StaticClass());
 * Execution:		IAudioPawnFlyingProvider::Execute_GetAudioPawnFlyingComponent(ContextObject);
 */
class AUDIOPLAYERPAWN_API IAudioPawnFlyingProvider {
	GENERATED_BODY()

public:
	/**
	 * @brief gives a pointer to UAudioPawnFlyingComponent, to be able to avoid unnecessary casts.
	 * @return pointer to UAudioPawnFlyingComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Audio Component"))
	UAudioPawnFlyingComponent* GetAudioPawnFlyingComponent() const;

	/**
	 * @brief gives a pointer to UPawnMovementComponent, to be able to avoid unnecessary casts.
	 * @return pointer to UPawnMovementComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Movement Component"))
	UPawnMovementComponent* GetAudioPawnFlyingMovementComponent() const;

	/**
	 * @brief gives a pointer to UMeshComponent, to be able to avoid unnecessary casts.
	 * @return pointer to UMeshComponent
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio", meta = (DisplayName = "Get Mesh Component"))
	UMeshComponent* GetAudioPawnFlyingMeshComponent() const;
};