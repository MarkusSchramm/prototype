/**
 * @file TestingHelperModuleImpl.cpp
 * @author Markus Schramm
 */

#include "TestingHelperModuleImpl.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogTestingHelper);

#define LOCTEXT_NAMESPACE "FTestingHelperModule"

void BachelorHelper::TestingHelper::FTestingHelperModule::StartupModule() {
	bIsInit = true;
}

void BachelorHelper::TestingHelper::FTestingHelperModule::ShutdownModule() {
	bIsInit = false;
}

bool BachelorHelper::TestingHelper::FTestingHelperModule::IsInitialized() const {
	return bIsInit;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(TESTINGHELPER_MODULE, TestingHelper);