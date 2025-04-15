/**
 * @file AudioProfilerDeveloperModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Definitions/AudioProfilerDefinitions.h"
#include "AudioProfilerDeveloperModel.generated.h"

/**
 * Data structure to store developer-focused settings and state for the Audio Profiler.
 * Contains configuration parameters and current state information used by the profiling system.
 */
USTRUCT(BlueprintType)
struct AUDIOPROFILER_API FAudioProfilerDeveloperModel {
	GENERATED_BODY()

	/**
	 * The name of the currently active profiling session.
	 * Used for identifying the session in logs and output files.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CurrentSessionName;
	
	/**
	 * The directory path where profiling data will be exported.
	 * Determines where CSV and Markdown reports are saved.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString OutputPath;

	/**
	 * The current profiling mode being used.
	 * Determines what type of audio metrics are being collected.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAudioProfilerProfilingType ProfilingMode = EAudioProfilerProfilingType::Default;

	/**
	 * The current debugging mode for the audio profiler.
	 * Controls additional debug information that may be collected or displayed.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAudioProfilerDebuggingType DebugMode = EAudioProfilerDebuggingType::Default;

	/**
	 * The time interval between profiling data captures in seconds.
	 * Controls how frequently audio metrics are sampled during a profiling session.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Interval = 1.f;

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

/**
 * @class UAudioProfilerDeveloperSettings
 * @brief Configuration settings for the Audio Profiler plugin
 * @details Provides customizable settings for the Audio Profiler that can be configured
 * in the Project Settings under the Developer Settings section. These settings
 * control how audio profiling data is collected, stored, and displayed.
 */
UCLASS(config=Game, meta=(DisplayName="Audio Profiler"))
class AUDIOPROFILER_API UAudioProfilerDeveloperSettings : public UDeveloperSettings {
	GENERATED_BODY()

public:
	/**
	 * @brief Directory where profiling data will be saved
	 * @details Specifies the filesystem path where profiling output files will be stored.
	 * Defaults to the project's Saved/Profiling directory.
	 * @note Changing this value requires an editor restart to take effect.
	 */
	UPROPERTY(
		EditAnywhere,
		Config,
		Category = "Bachelor Audio | Audio Profiling",
		meta = (ConfigRestartRequired = true)
		)
	FString OutputDirectory;

	/**
	 * @brief The type of audio profiling to perform
	 * @details Determines what metrics are collected and how profiling is conducted.
	 * Uses the EAudioProfilerProfilingType enum to specify different profiling modes.
	 * @note Changing this value requires an editor restart to take effect.
	 */
	UPROPERTY(
		EditAnywhere,
		Config,
		Category = "Bachelor Audio | Audio Profiling",
		meta = (ConfigRestartRequired = true)
		)
	EAudioProfilerProfilingType ProfilingMode;

	/**
	 * @brief Controls the verbosity and target of debug logging
	 * @details Configures how much information is logged during profiling.
	 * Uses EAudioProfilerDebuggingType enum to specify different logging modes.
	 */
	UPROPERTY(
		EditAnywhere,
		Config,
		Category = "Bachelor Audio | Audio Profiling"
		)
	EAudioProfilerDebuggingType DebugMode;

	/**
	 * @brief Time interval between profiling data captures in seconds
	 * @details Controls how frequently the profiler collects data points. Lower values
	 * provide more detailed profiling but may impact performance. Higher values
	 * reduce overhead but provide less granular data.
	 * @note Value is clamped between 0.00005 seconds (50 microseconds) and 10 seconds.
	 */
	UPROPERTY(
		EditAnywhere,
		Config,
		Category = "Bachelor Audio | Audio Profiling",
		meta = (
			UIMin = 0.00005,
			ClampMin = 0.00005,
			UIMax = 10,
			ClampMax = 10
			))
	float ProfilingInterval;
};