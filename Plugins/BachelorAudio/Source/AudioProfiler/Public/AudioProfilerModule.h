/**
 * @file AudioProfilerModule.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAudioProfiler, Log, All);

namespace BachelorAudio::AudioProfiler {
	/**
	 * @interface IAudioProfilerModule
	 * @brief Abstract interface for the Audio Profiler Module
	 * 
	 * Defines the interface for the Audio Profiler Module within the Unreal Engine plugin architecture.
	 * Derives from IModuleInterface to integrate with the Unreal Engine module system, allowing for
	 * proper loading, unloading, and lifecycle management of the Audio Profiler functionality.
	 * 
	 * This interface serves as the entry point for the Audio Profiler plugin and enables other engine
	 * components and modules to access audio profiling capabilities through the module system.
	 * 
	 * @see IModuleInterface - The base Unreal Engine interface for all modules
	 * @see FModuleManager - Used to access this module at runtime
	 */
	class AUDIOPROFILER_API IAudioProfilerModule : public IModuleInterface {};
}