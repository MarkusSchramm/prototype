/**
 * @file BachelorMetasoundModuleImpl.cpp
 * @author Markus Schramm
 */

#include "BachelorMetasoundModuleImpl.h"

#include "Logging/LogMacros.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogBachelorMetasound);

#define LOCTEXT_NAMESPACE "FBachelorAudioModule"

void BachelorAudio::BachelorMetasound::FBachelorMetasoundModule::StartupModule() {
	bIsInit = true;
}

void BachelorAudio::BachelorMetasound::FBachelorMetasoundModule::ShutdownModule() {
	bIsInit = false;
}

bool BachelorAudio::BachelorMetasound::FBachelorMetasoundModule::IsInitialized() const {
	return bIsInit;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(BACHELORMETASOUND_MODULE, BachelorMetasound);