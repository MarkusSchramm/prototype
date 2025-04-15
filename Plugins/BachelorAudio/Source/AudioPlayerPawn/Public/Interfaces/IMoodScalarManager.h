/**
 * @file IMoodScalarManager.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMoodScalarManager.generated.h"

/**
 * @interface UMoodScalarManager
 * @brief Interface duplication to get the interface into the unreal engine reflection system
 * @see UInterface
 * @see IMoodScalarManager
 */
UINTERFACE(BlueprintType)
class AUDIOPLAYERPAWN_API UMoodScalarManager : public UInterface {
	GENERATED_BODY()
};

/**
 * @interface IMoodScalarManager
 * @brief Interface for controlling mood and energy scalar values
 *
 * If you want this Interface to be overrideable in C++ and Blueprints, you have to follow this Syntax:
 * Implementation:  virtual SetMood_Implementation(float MoodScalar) override;
 * Check:			GetOwner()->GetClass()->ImplementsInterface(UMoodScalarManager::StaticClass());
 * Execution:		IMoodScalarManager::Execute_SetMood(ContextObject, MoodScalar);
 */
class AUDIOPLAYERPAWN_API IMoodScalarManager {
	GENERATED_BODY()

public:
	/**
	 * Sets the mood scalar value for audio/gameplay adjustments
	 * @param MoodScalar A normalized float value (typically 0.0-1.0) representing the current mood state
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Game State")
	void SetMood(float MoodScalar);

	/**
	 * Sets the energy scalar value for audio/gameplay adjustments
	 * @param EnergyScalar A normalized float value (typically 0.0-1.0) representing the current energy level
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Game State")
	void SetEnergy(float EnergyScalar);
};