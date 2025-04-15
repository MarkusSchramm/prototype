/**
 * @file AudioPlayerPawnModuleImpl.cpp
 * @author Markus Schramm
 */

#include "AudioPlayerPawnModuleImpl.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogAudioPlayerPawnModule);

#define LOCTEXT_NAMESPACE "FAudioPlayerPawnModule"

void BachelorAudio::AudioPlayerPawn::FAudioPlayerPawnModule::StartupModule() {
	UE_LOG(LogAudioPlayerPawnModule, Log, TEXT("AudioPlayerPawnModule initialized"));
	bIsInit = true;
}

void BachelorAudio::AudioPlayerPawn::FAudioPlayerPawnModule::ShutdownModule() {
	UE_LOG(LogAudioPlayerPawnModule, Log, TEXT("AudioPlayerPawnModule shutdown"));
	bIsInit = false;
}

bool BachelorAudio::AudioPlayerPawn::FAudioPlayerPawnModule::IsInitialized() const {
	return bIsInit;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(AUDIOPLAYERPAWN_MODULE, AudioPlayerPawn);
