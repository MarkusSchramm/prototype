/**
 * @file AudioPawnWalkingModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioPawnDeveloperModel.h"
#include "AudioPawnScalarModel.h"
#include "AudioPawnWalkingModel.generated.h"

/**
 * @struct FAudioPawnWalkingModel
 * @brief Data model for walking character audio configurations in Unreal Engine.
 * 
 * @details This struct encapsulates all audio-related parameters and settings for walking pawns,
 * organizing scalar values, trigger names, and developer settings that control sound behavior 
 * during ground movement on foot. The struct is exposed to Blueprint and can be fully configured 
 * from the Unreal Editor.
 */
USTRUCT(BlueprintType, Category = "Audio")
struct AUDIOPLAYERPAWN_API FAudioPawnWalkingModel {
    GENERATED_BODY()

    /**
     * @brief The name of the trigger used to play walking sounds.
     * 
     * @details This name is used as an identifier for the trigger event that initiates
     * footstep or other walking-related sounds. Custom Metasound implementations should
     * use this name for their play triggers.
     */
    UPROPERTY(
       VisibleAnywhere,
       BlueprintReadOnly,
       Category = "Audio Manipulation",
       meta = (
          DisplayName = "Play Trigger Name",
          ShortTooltip = "Implement a trigger with this name, if you want to use a custom Metasound.",
          AllowPrivateAccess = "true"
          ))
    FName PlayTriggerName;
    
    /**
     * @brief Array of scalar models that control various audio parameters for walking pawns.
     * 
     * @details Each scalar represents a different audio parameter (such as speed, ground type,
     * character weight, etc.) that can be adjusted to create dynamic walking sound effects. These
     * scalars are automatically initialized by the InitScalars() method.
     * 
     * @see FAudioPawnScalarModel
     * @see InitScalars()
     */
    UPROPERTY(
       EditAnywhere, 
       BlueprintReadWrite,
       Category = "Scalars",
       meta = (
          DisplayName = "Flying Pawn Audio Scalars",
          ExposeOnSpawn,
          ShowOnlyInnerProperties,
          AllowPrivateAccess = "true"
          ))
    TArray<FAudioPawnScalarModel> Scalars;

    /**
     * @brief Development and debugging settings for the walking pawn audio system.
     * 
     * @details Contains configuration options that are primarily used during development
     * and testing phases. These settings allow for fine-tuning and debugging of the
     * audio behavior without modifying the core audio parameters.
     * 
     * @see FAudioPawnDeveloperModel
     */
    UPROPERTY(
       EditAnywhere, 
       BlueprintReadWrite,
       Category = "Developer Settings",
       meta = (
          ShowOnlyInnerProperties,
          AllowPrivateAccess = "true"
          ))
    FAudioPawnDeveloperModel DeveloperSettings;

    /**
     * @brief Initializes the Scalars array with default values for all scalar types.
     * 
     * @details This method clears any existing scalars and populates the Scalars array
     * with one entry for each scalar type defined in EAudioPawnScalarType. Each scalar
     * is initialized with default values and properly named according to its type.
     * The method also sets up the MetasoundInputName for each scalar by appending "In"
     * to the scalar name.
     * 
     * Additionally, this method initializes the PlayTriggerName to "PlayShot".
     * 
     * @note This should be called during component initialization to ensure all required
     * scalar types are available for the audio system.
     * 
     * @see EAudioPawnScalarType
     * @see ScalarTypeAsInt()
     * @see ScalarTypeAsFName()
     */
    void InitScalars() {
       Scalars.Empty();
       PlayTriggerName = FName("PlayShot");
       auto model = FAudioPawnScalarModel();
       model.Value = 0.f;
       model.LastValue = 0.f;
       for (int i = 0; i < ScalarTypeAsInt(SCALAR_NUM); ++i) {
          model.Type = static_cast<EAudioPawnScalarType>(i);
          model.Name = ScalarTypeAsFName(model.Type);
          model.MetasoundInputName
             = FName(FString::Printf(TEXT("%sIn"), *model.Name.ToString()));
          Scalars.Add(model);
       }
    }

    /**
     * @brief Destructor for the FAudioPawnWalkingModel struct.
     * 
     * @details Ensures proper cleanup by emptying the Scalars array when the struct is destroyed,
     * preventing potential memory leaks or dangling references.
     */
    ~FAudioPawnWalkingModel() {
       Scalars.Empty();
    }
};