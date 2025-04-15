/**
 * @file AudioProfilerSoundModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioProfilerSoundModel.generated.h"

/**
 * @struct FAudioProfilerSoundModel
 * @brief Data structure for capturing and displaying information of currently active sound
 * @details This struct collects various metrics related to audio and general system performance,
 * allowing for real-time monitoring and analysis of audio system behavior
 */
USTRUCT(BlueprintType, Category = "Audio Profiler")
struct AUDIOPROFILER_API FAudioProfilerSoundModel {
	GENERATED_BODY()
	
	/**
	 * @brief Name of active sounds
	 * @details Stores identifiers for active sound, useful for debugging and analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (
			DisplayName = "Active Sound Name"
			))
	FString ActiveSoundName{TEXT("")};
	
	/**
	 * @brief Volume level of active sounds
	 * @details Stores the volume level (0.0 -1.0) of active sound in the system
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (
			DisplayName = "Active Sound Volume"
			))
	float ActiveSoundVolume{0.f};

	/**
	 * @brief Additional custom values associated with active sounds
	 * @details Key-value pairs that can store any sound-specific metrics or properties
	 * for more detailed audio profiling and analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (
			DisplayName = "Active Sound Values",
			ShowOnlyInnerProperties
			))
	TMap<FString, float> ActiveSoundValues{};

	/**
	* @brief A safe pointer to an object associated with this profiling data.
	* 
	* @details This pointer can be used to reference any UObject that might be
	* relevant to this profiling data's functionality, such as an audio component or
	* other game object. The pointer is not exposed to the UI or Blueprints
	* and is primarily used for internal C++ operations.
	*/
	UPROPERTY()
	UObject* SafeObjectPointer;
};