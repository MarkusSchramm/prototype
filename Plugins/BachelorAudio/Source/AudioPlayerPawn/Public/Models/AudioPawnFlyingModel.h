/**
 * @file AudioPawnFlyingModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioPawnDeveloperModel.h"
#include "AudioPawnScalarModel.h"
#include "Definitions/AudioPawnDefinitions.h"
#include "AudioPawnFlyingModel.generated.h"

/**
 * @struct FAudioPawnFlyingModel
 * @brief Data model for flying pawn audio configurations in Unreal Engine.
 * 
 * @details This struct encapsulates all audio-related parameters and settings for flying pawns,
 * organizing scalar values and developer settings that control sound behavior during flight.
 * The struct is exposed to Blueprint and can be fully configured from the Unreal Editor.
 */
USTRUCT(BlueprintType, Category = "Audio")
struct AUDIOPLAYERPAWN_API FAudioPawnFlyingModel {
	GENERATED_BODY()

	/**
	 * @brief Array of scalar models that control various audio parameters for flying pawns.
	 * 
	 * @details Each scalar represents a different gamified audio parameter (such as speed, mood, energy, etc.)
	 * that can be adjusted to create dynamic flight sound effects. These scalars are 
	 * automatically initialized by the InitScalars() method.
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
	 * @brief Development and debugging settings for the flying pawn audio system.
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
	* @note This should be called during component initialization to ensure all required
	* scalar types are available for the audio system.
	* 
	* @see EAudioPawnScalarType
	* @see ScalarTypeAsInt()
	* @see ScalarTypeAsFName()
	*/
	void InitScalars() {
		Scalars.Empty();
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
	 * @brief Destructor for the FAudioPawnFlyingModel struct.
	 * 
	 * @details Ensures proper cleanup by emptying the Scalars array when the struct is destroyed,
	 * preventing potential memory leaks or dangling references.
	 */
	~FAudioPawnFlyingModel() {
		Scalars.Empty();
	}
};