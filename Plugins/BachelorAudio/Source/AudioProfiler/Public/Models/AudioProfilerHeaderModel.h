/**
 * @file AudioProfilerHeaderModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioProfilerHeaderModel.generated.h"

class USoundSubmix;

/**
 * @struct FAudioProfilerHeaderModel
 * @brief Data structure for capturing data needed for building up a report header
 * @details This struct collects various metrics related to audio and general system performance,
 * allowing for real-time monitoring and analysis of audio system behavior
 */
USTRUCT(BlueprintType, Category = "Audio Profiler")
struct AUDIOPROFILER_API FAudioProfilerHeaderModel {
	GENERATED_BODY()

	/**
	 * @brief PlatformSettings of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Header",
		meta = (
			DisplayName = "Session Name"
			))
	FString SessionName{};

	/**
	 * @brief PlatformSettings of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Header",
		meta = (
			DisplayName = "World Name"
			))
	FString WorldName{};

	/**
	 * @brief PlatformSettings of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Header",
		meta = (
			DisplayName = "Date"
			))
	FDateTime Date{};

	/**
	 * @brief PlatformSettings of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Header",
		meta = (
			DisplayName = "Start Time"
			))
	double StartTime{0.0};

	/**
	 * @brief Sample rate
	 * @details Sample rate of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Sample Rate"
			))
	int32 SampleRate{0};

	/**
	 * @brief Max Channels
	 * @details Max channels of audio device
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Max Channels"
			))
	int32 MaxChannels{0};
	
	/**
	 * @brief Number of buffers
	 * @details Tracks the number of buffers audio device keeps queued
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Num Buffers",
			ToolTip = "Number of buffers audio device keeps queued"
			))
	int32 NumBuffers{0};

	/**
	 * @brief Buffer length
	 * @details Tracks buffer length audio device keeps queued
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Buffer Lenght"
			))
	int32 BufferLength{0};

	/**
	 * @brief Max number of sources player at same time
	 * @details Tracks the max number of sources audio device will play
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Max Sources"
			))
	int32 MaxSources{0};

	/**
	 * @brief Number of sources player at same time
	 * @details Tracks the number of sources audio device will play
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Device",
		meta = (
			DisplayName = "Num Source Workers"
			))
	int32 NumSourceWorkers{0};

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