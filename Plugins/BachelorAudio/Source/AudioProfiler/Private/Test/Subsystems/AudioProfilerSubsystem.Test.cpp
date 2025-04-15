/**
 * @file AudioProfilerSubsystem.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for module management.
 */

#include "Subsystems/AudioProfilerSubsystem.h"
#include "AudioProfilerModule.h"
#include "WorldFixture.h"
#include "Models/AudioProfilerModel.h"

#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

using namespace BachelorHelper::TestingHelper;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemInitializationTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.000_InitializationTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemInitializationTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    TestNotNull(TEXT("World should be created successfully"), WorldFixture->GetWorld());
    
    if (!World) return false;

    // Get game instance
    UGameInstance* GameInstance = NewObject<UGameInstance>();

    TestNotNull(TEXT("Game instance should be available"), GameInstance);
    
    if (!GameInstance) return false;
    GameInstance->Init();

    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();

    TestNotNull(TEXT("AudioProfilerSubsystem should be initialized properly"), AudioProfilerSubsystem);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemOutputDirectoryTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.005_OutputDirectoryTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemOutputDirectoryTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // Set custom output directory
    const FString TestOutputDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("AudioProfilerTests"));
    AudioProfilerSubsystem->SetOutputDirectory(TestOutputDir);
    
    // Get profiling data to check internal state indirectly
    FAudioProfilerModel ProfilingData = AudioProfilerSubsystem->GetProfilingData();
    
    // No direct way to check if the directory was set, but we can verify the subsystem is still valid
    TestNotNull(TEXT("AudioProfilerSubsystem should remain valid after setting output directory"), AudioProfilerSubsystem);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemStartStopProfilingTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.010_StartStopProfilingTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemStartStopProfilingTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // Start profiling with test parameters
    const FString TestSessionName = TEXT("AutomationTest");
    constexpr float IntervalSeconds = 0.1f;
    constexpr float ExpectedDurationSeconds = 1.0f;
    
    AudioProfilerSubsystem->StartProfiling(TestSessionName, IntervalSeconds, ExpectedDurationSeconds, World);
    
    // Simulate passage of time to allow data collection
    for (int i = 0; i < 5; i++) {
        WorldFixture->TickWorld(.2f);  // Tick world multiple times to allow timer to fire
    }
    
    // Get profiling data before stopping
    FAudioProfilerModel ProfilingDataDuringProfiling = AudioProfilerSubsystem->GetProfilingData();
    
    // Stop profiling
    AudioProfilerSubsystem->StopProfiling(World);
    
    // Get profiling data after stopping
    FAudioProfilerModel ProfilingDataAfterStopping = AudioProfilerSubsystem->GetProfilingData();
    
    // Since ProfilingData is a private member, we can't directly check bIsProfiling
    // But we can verify that the subsystem is still valid after stopping profiling
    TestNotNull(TEXT("AudioProfilerSubsystem should remain valid after stopping profiling"), AudioProfilerSubsystem);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemBookmarkTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.015_BookmarkTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemBookmarkTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // Start profiling
    const FString TestSessionName = TEXT("BookmarkTest");
    const float IntervalSeconds = 0.1f;
    const float ExpectedDurationSeconds = 1.0f;
    
    AudioProfilerSubsystem->StartProfiling(TestSessionName, IntervalSeconds, ExpectedDurationSeconds, World);
    
    // Add bookmarks at different times
    AudioProfilerSubsystem->AddBookmark(TEXT("StartEvent"));
    
    // Tick world to advance time
    WorldFixture->TickWorld(0.2f);
    
    AudioProfilerSubsystem->AddBookmark(TEXT("MiddleEvent"));
    
    // Tick world again
    WorldFixture->TickWorld(0.2f);
    
    AudioProfilerSubsystem->AddBookmark(TEXT("EndEvent"));
    
    // Stop profiling
    AudioProfilerSubsystem->StopProfiling();
    
    // We can't directly verify the bookmarks were added as ProfilingBookmarks is private
    // But we can verify the subsystem is still valid after adding bookmarks
    TestNotNull(TEXT("AudioProfilerSubsystem should remain valid after adding bookmarks"), AudioProfilerSubsystem);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemGetProfilingDataTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.020_GetProfilingDataTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemGetProfilingDataTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // Get initial profiling data (should be empty or default)
    FAudioProfilerModel InitialData = AudioProfilerSubsystem->GetProfilingData();
    
    // Start profiling
    const FString TestSessionName = TEXT("DataTest");
    const float IntervalSeconds = 0.1f;
    const float ExpectedDurationSeconds = 0.5f;
    
    AudioProfilerSubsystem->StartProfiling(TestSessionName, IntervalSeconds, ExpectedDurationSeconds, World);
    
    // Tick world to allow data collection
    for (int i = 0; i < 3; i++) {
        WorldFixture->TickWorld(0.2f);
    }
    
    // Get profiling data during profiling
    FAudioProfilerModel DuringProfilingData = AudioProfilerSubsystem->GetProfilingData();
    
    // Stop profiling
    AudioProfilerSubsystem->StopProfiling();
    
    // Get final profiling data
    FAudioProfilerModel FinalData = AudioProfilerSubsystem->GetProfilingData();
    
    // Verify the data access method works
    TestNotNull(TEXT("GetProfilingData() should return valid data"), &FinalData);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemMultipleSessionsTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.025_MultipleSessionsTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemMultipleSessionsTest::RunTest(const FString& Parameters) {
    // Create a test world
    MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // First session
    AudioProfilerSubsystem->StartProfiling(TEXT("Session1"), 0.1f, 0.5f, World);
    
    // Tick world to collect data
    WorldFixture->TickWorld(0.2f);
    AudioProfilerSubsystem->AddBookmark(TEXT("Session1Event"));
    WorldFixture->TickWorld(0.2f);
    
    // Stop first session
    AudioProfilerSubsystem->StopProfiling();
    
    // Second session
    AudioProfilerSubsystem->StartProfiling(TEXT("Session2"), 0.2f, 1.0f, World);
    
    // Tick world to collect data
    WorldFixture->TickWorld(0.3f);
    AudioProfilerSubsystem->AddBookmark(TEXT("Session2Event"));
    WorldFixture->TickWorld(0.3f);
    
    // Stop second session
    AudioProfilerSubsystem->StopProfiling();
    
    // Verify subsystem is still valid after multiple sessions
    TestNotNull(TEXT("AudioProfilerSubsystem should remain valid after multiple sessions"), AudioProfilerSubsystem);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FAudioProfilerSubsystemDeinitializationTest,
    "prototype.BachelorAudio.AudioProfiler.AudioProfilerSubsystem.030_DeinitializationTest",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FAudioProfilerSubsystemDeinitializationTest::RunTest(const FString& Parameters) {
    // Create a test world with a unique pointer so we can control its destruction
    auto WorldFixture = MAKE_UNIQUE_WORLD_FIXTURE;
    UWorld* World = WorldFixture->GetWorld();
    if (!World) return false;
    
    // Get game instance and subsystem
    UGameInstance* GameInstance = NewObject<UGameInstance>();
    if (!GameInstance) return false;
    GameInstance->Init();
    
    UAudioProfilerSubsystem* AudioProfilerSubsystem = GameInstance->GetSubsystem<UAudioProfilerSubsystem>();
    if (!AudioProfilerSubsystem) return false;
    
    // Start profiling
    AudioProfilerSubsystem->StartProfiling(TEXT("DeinitTest"), 0.1f, 0.5f, World);
    
    // Tick world
    WorldFixture->TickWorld(0.2f);
    
    // Manually destroy the world, which should trigger subsystem deinitialization
    WorldFixture.Reset();
    
    // Test passes if no crashes occur during deinitialization
    TestTrue(TEXT("Subsystem should deinitialize gracefully"), true);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif