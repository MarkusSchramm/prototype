/**
 * @file AudioProfilerModuleImpl.cpp
 * @author Markus Schramm
 */

#include "AudioProfilerModuleImpl.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogAudioProfiler);

#define LOCTEXT_NAMESPACE "FTestingHelperModule"

void BachelorAudio::AudioProfiler::FAudioProfilerModule::StartupModule() {
	bIsInit = true;
}

void BachelorAudio::AudioProfiler::FAudioProfilerModule::ShutdownModule() {
	bIsInit = false;;
}
bool BachelorAudio::AudioProfiler::FAudioProfilerModule::IsInitialized() const {
	return bIsInit;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(AUDIOPROFILER_MODULE, AudioProfiler);