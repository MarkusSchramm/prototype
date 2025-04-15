/**
 * @file AudioProfilerTimestampModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioProfilerSoundModel.h"
#include "AudioProfilerTimestampModel.generated.h"

struct FAudioProfilerSoundModel;

/**
 * @struct FAudioProfilerTimestampModel
 * @brief Data structure for capturing and displaying audio-related performance metrics
 * @details This struct collects various metrics related to audio and general system performance,
 * allowing for real-time monitoring and analysis of audio system behavior
 */
USTRUCT(BlueprintType, Category = "Audio Profiler")
struct AUDIOPROFILER_API FAudioProfilerTimestampModel {
	GENERATED_BODY()

	/**
	 * @brief Current system timestamp
	 * @details Tracks when this profile data was captured, useful for chronological analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Timestamp"
			))
	double Timestamp{0.f};

	/**
	 * @brief Audio thread time elapsed since last frame
	 * @details Measures the time between successive frames, important for performance analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Current Audio Deltatime"
			))
	float CurrentAudioDelta{0.f};

	/**
	 * @brief Audio thread time elapsed
	 * @details Measures the time audio thread is been active, important for performance analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Current Audio Time"
			))
	float CurrentAudioTime{0.f};
	
	/**
	 * @brief Time elapsed since last frame
	 * @details Measures the time between successive frames, important for performance analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Current Deltatime"
			))
	float CurrentDelta{0.f};

	/**
	 * @brief Current application framerate
	 * @details Represents frames per second, a key performance indicator
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Framerate"
			))
	float Framerate{0.f};

	/**
	 * @brief Overall CPU utilization percentage
	 * @details Measures total CPU usage across all cores/threads
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "CPU Usage %"
			))
	float CPUUsage{0.f};

	/**
	 * @brief Total memory consumption in megabytes
	 * @details Monitors RAM usage, important for tracking potential memory leaks
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Metrics",
		meta = (
			DisplayName = "Memory Usage MB"
			))
	float MemoryUsageMB{0.f};

	/**
	 * @brief Master volume in linear scale (0.0 - 1.0)
	 * @details Represents the master volume as a linear value where 0 is silent and 1 is maximum
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Master",
		meta = (
			DisplayName = "Master Volume lin"
			))
	float MasterVolumeLin{0.f};

	/**
	 * @brief Headroom linear
	 * @details Represents the headroom as scalar
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Master",
		meta = (
			DisplayName = "Headroom"
			))
	float Headroom{0.f};

	/**
	 * @brief Number of sounds currently playing
	 * @details Tracks the total count of active sound instances in the audio system
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Active Sound Count"
			))
	int32 ActiveSoundCount{0};

	/**
	 * @brief Number of currently free sources
	 * @details Tracks the total count of free sources available in the audio system
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Free Sources Count"
			))
	int32 FreeSourcesCount{0};
	
	/**
	 * @brief all currently active sounds
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
	TArray<FAudioProfilerSoundModel> ActiveSounds{};

	/**
	 * @brief all currently active bookmarks
	 * @details Stores identifiers and current values for each active bookmark, useful for debugging and analysis
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Sounds",
		meta = (
			DisplayName = "Active Sound Names",
			ShowOnlyInnerProperties
			))
	TArray<FString> ActiveBookmarks{};

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