/**
 * @file AudioProfilerModule.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for module management.
 */

#include "AudioProfilerModule.h"
#include "AudioProfilerModuleImpl.h"

#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTestingHelperModuleImplLoadModuleTest,
	"prototype.BachelorAudio.AudioProfiler.AudioProfilerModule.000_LoadModuleTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FTestingHelperModuleImplLoadModuleTest::RunTest(const FString& Parameters) {
	FModuleManager& moduleManager = FModuleManager::Get();
	IModuleInterface* module = moduleManager.LoadModule("AudioProfiler");
	TestNotNull(TEXT("Module should load successfully"), module);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTestingHelperModuleImplValidateModuleTest,
	"prototype.BachelorAudio.AudioProfiler.AudioProfilerModule.005_ValidateModuleTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FTestingHelperModuleImplValidateModuleTest::RunTest(const FString& Parameters) {
	AUDIOPROFILER_MODULE& module = FModuleManager::GetModuleChecked<AUDIOPROFILER_MODULE>("AudioProfiler");
	TestTrue(TEXT("Module should be initialized"), module.IsInitialized());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
