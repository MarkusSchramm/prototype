/**
 * @file AudioPawnScalarModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Definitions/AudioPawnDefinitions.h"
#include "AudioPawnScalarModel.generated.h"

/**
 * @struct FAudioPawnScalarModel
 * @brief Represents a single scalar parameter for the pawn audio system.
 * 
 * @details This struct encapsulates a scalar value that can be used to control various audio
 * parameters in the pawn audio system. Each scalar has a type, name, and corresponding 
 * Metasound input name, along with current and previous values. The scalars are used
 * to modulate audio properties like speed, energy, etc based on scalars built on response
 * to pawn movement or state changes.
 */
USTRUCT(BlueprintType, Category = "Audio")
struct AUDIOPLAYERPAWN_API FAudioPawnScalarModel {
    GENERATED_BODY()

    /**
     * @brief The type of scalar parameter (e.g., Velocity, Throttle, etc.).
     * 
     * @details This enumeration defines what aspect of the pawn's movement or state
     * this scalar value represents. It is used to properly map the scalar to the
     * appropriate audio parameter in the sound system.
     * 
     * @see EAudioPawnScalarType
     */
    UPROPERTY(
       VisibleAnywhere,
       BlueprintReadOnly,
       meta = (
          DisplayName = "Scalar Type"
          ))
    EAudioPawnScalarType Type = EAudioPawnScalarType::NumAudioPawnScalars;
    
    /**
     * @brief The display name for this scalar parameter.
     * 
     * @details This name is used for identification in the UI and is
     * derived from the scalar type.
     */
    UPROPERTY(
       VisibleAnywhere,
       BlueprintReadWrite,
       meta = (
          DisplayName = "Scalar Name"
          ))
    FName Name{""};

    /**
     * @brief The input parameter name used in Metasound for this scalar.
     * 
     * @details This name is automatically generated based on the scalar name and
     * is used to bind the scalar value to the corresponding input in a Metasound patch.
     * Custom Metasound implementations should use this name for their input triggers.
     */
    UPROPERTY(
       VisibleAnywhere,
       BlueprintReadonly,
       meta = (
          DisplayName = "Metasound Input Name",
          ShortTooltip = "Implement a trigger with this name, if you want to use a custom Metasound."
          ))
    FName MetasoundInputName{""};

    /**
     * @brief The current value of the scalar parameter.
     * 
     * @details This is the active value that will be sent to the audio system.
     * It is clamped between 0.0 and 1.0 to ensure consistent behavior across
     * different audio parameters.
     */
    UPROPERTY(
       EditAnywhere, 
       BlueprintReadWrite,
       Category = "Scalar",
       meta = (
          DisplayName = "Scalar Value",
          ClampMin = "0.0",
          UIMin = "0.0",
          ClampMax = "1.0",
          UIMax = "1.0"
          ))
    float Value{0.f};

    /**
     * @brief The previous value of the scalar parameter.
     * 
     * @details This stores the last value that was applied, which can be used
     * to calculate deltas or determine if the value has changed since the last update.
     * This is particularly useful for optimizing audio parameter updates.
     */
    UPROPERTY(
       VisibleAnywhere,
       BlueprintReadOnly,
       Category = "Scalar",
       meta = (
          DisplayName = "Scalar Last Value",
          ClampMin = "0.0",
          UIMin = "0.0",
          ClampMax = "1.0",
          UIMax = "1.0"
          ))
    float LastValue{0.f};

    /**
     * @brief A safe pointer to an object associated with this scalar.
     * 
     * @details This pointer can be used to reference any UObject that might be
     * relevant to this scalar's functionality, such as an audio component or
     * other game object. The pointer is not exposed to the UI or Blueprints
     * and is primarily used for internal C++ operations.
     */
    UPROPERTY()
    UObject* SafeObjectPointer;
};