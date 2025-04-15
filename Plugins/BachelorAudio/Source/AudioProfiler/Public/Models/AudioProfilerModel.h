/**
* @file AudioProfilerTimestampModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioProfilerDeveloperModel.h"
#include "AudioProfilerHeaderModel.h"
#include "AudioProfilerTimestampModel.h"
#include "AudioProfilerModel.generated.h"

/**
 * @struct FAudioProfilerModel
 * @brief Data structure for capturing and displaying audio-related performance metrics
 * @details This struct collects various metrics related to audio and general system performance,
 * allowing for real-time monitoring and analysis of audio system behavior
 */
USTRUCT(BlueprintType, Category = "Audio Profiler")
struct AUDIOPROFILER_API FAudioProfilerModel {
	GENERATED_BODY()

	/**
	 * @brief Profiling developer settings
	 * @details Stores data and information on profiling settings
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Active Sound Names",
			ShowOnlyInnerProperties
			))
	FAudioProfilerDeveloperModel AudioProfilerSettings;

	/**
	 * @brief Profiling data header
	 * @details Stores all data and information retrieved at profiling start
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Active Sound Names",
			ShowOnlyInnerProperties
			))
	FAudioProfilerHeaderModel AudioProfilerHeader;

	/**
	 * @brief all currently active sounds and audio device info
	 * @details Stores identifiers and current values for each active sound, useful for debugging and analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Active Sound Names",
			ShowOnlyInnerProperties
			))
	TArray<FAudioProfilerTimestampModel> AudioProfilerData;

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