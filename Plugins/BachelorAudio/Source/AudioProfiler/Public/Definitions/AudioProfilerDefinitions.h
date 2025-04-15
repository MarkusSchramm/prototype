/**
 * @file AudioProfilerDefinitions.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioProfilerDefinitions.generated.h"

/**
 * @enum EAudioProfilerProfilingType
 * @brief Defines the different profiling modes available in the Audio Profiler
 * @details Controls what audio elements are profiled and the depth of profiling information collected.
 * This affects performance overhead and the level of detail in profiling data.
 */
UENUM(BlueprintType)
enum class EAudioProfilerProfilingType : uint8 {
	/**
	 * @brief Disables all audio profiling
	 *  @details No profiling data will be collected, minimizing any performance impact
	 */
	NoProfiling = 0 UMETA(DisplayName = "No Profiling"),

	/**
	 * @brief Profiles only the audio device itself
	 *  @details Collects performance metrics about the audio device including CPU usage and memory consumption
	 */
	ProfilingAudioDevice = 1 UMETA(DisplayName = "Profiling Audio Device"),

	/**
	 * @brief Profiles individual sound instances
	 * @details Collects information about active sounds, their volumes, and properties 
	 */
	ProfilingSounds = 2 UMETA(DisplayName = "Profiling Sounds"),

	/**
	 * @brief Complete profiling of all audio systems
     * @details Comprehensive profiling of both the audio device and all sound instances.
     * Provides the most detailed information but may have higher performance impact
	 */
	ProfilingFull = 3 UMETA(DisplayName = "Profiling Full"),

	/**
	 * @brief Default profiling setting (No Profiling)
	 * @details Used as the initial value when creating new profiler instances
	 */
	Default = NoProfiling,
};

/**
 * @enum EAudioProfilerDebuggingType
 * @brief Defines the verbosity levels for Audio Profiler debugging output
 * @details Controls what types of messages are logged during profiling operations.
 * Higher verbosity levels include all lower level messages.
 */
UENUM(BlueprintType)
enum class EAudioProfilerDebuggingType : uint8 {
	/**
	 * @brief Disables all debug logging
	 *  @details No debug messages will be output 
	 */
	NoDebugging	= 0 UMETA(DisplayName = "No Debugging"),

	/**
	 * @brief Only logs critical errors
	 * @details Reports only issues that prevent proper operation
	 */
	Error = 1 UMETA(DisplayName = "Debugging Errors only"),

	/**
	 * @brief Logs errors and warnings
	 * @details Reports both critical issues and potential problems
	 */
	Warning	= 2 UMETA(DisplayName = "Debugging Errors and Warnings"),

	/**
	 * @brief Standard logging level
	 * @details Includes errors, warnings, and general information messages
	 */
	Log	= 3 UMETA(DisplayName = "Debugging Errors, Warnings and Logs"),

	/**
	 * @brief Detailed logging
     * @details Provides additional information useful for development and troubleshooting
	 */
	Verbose	= 4 UMETA(DisplayName = "Debugging Verbose"),

	/**
	 * @brief Most extensive logging
	 * @details Outputs all possible debugging information, including low-level details
	 */
	VeryVerbose	= 5 UMETA(DisplayName = "Debugging Full"),

	/**
	 * @brief Default debugging setting (No Debugging)
	 * @details Used as the initial value when creating new profiler instances
	 */
	Default	= NoDebugging,
};