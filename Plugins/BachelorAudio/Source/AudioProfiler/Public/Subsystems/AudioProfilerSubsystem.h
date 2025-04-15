/**
 * @file AudioProfilerSubsystem.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Models/AudioProfilerModel.h"
#include "AudioProfilerSubsystem.generated.h"

enum class EAudioProfilerDebuggingType : uint8;
enum class EAudioProfilerProfilingType : uint8;

/**
 * A subsystem for profiling audio performance in a game instance.
 * Captures and records audio performance metrics at specified intervals during gameplay.
 * Data can be exported to CSV and Markdown formats for analysis.
 */
UCLASS(config=Game, ClassGroup="Audio")
class AUDIOPROFILER_API UAudioProfilerSubsystem final : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:
	/**
	 * Default constructor for the Audio Profiler Subsystem.
	 * Initializes member variables and sets up the subsystem.
	 */
	UAudioProfilerSubsystem();

	/**
	 * Default constructor for the Audio Profiler Subsystem.
	 * Initializes member variables and sets up the subsystem.
	 */
	explicit UAudioProfilerSubsystem(const FObjectInitializer& ObjectInitializer);

	/**
	 * Virtual destructor for the Audio Profiler Subsystem.
	 * Ensures proper cleanup of resources when the subsystem is destroyed.
	 */
	virtual ~UAudioProfilerSubsystem() override;

	/**
	 * Initializes the Audio Profiler Subsystem.
	 * Sets up log categories and prints initialization message.
	 * @param Collection The collection of subsystems that this subsystem belongs to.
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * Deinitializes the Audio Profiler Subsystem.
	 * Ensures profiling is stopped before shutdown.
	 */
	virtual void Deinitialize() override;

	/**
	 * Sets the directory where profiling data will be exported.
	 * If empty, uses the default directory.
	 * @param InOutputDirectory Path to the directory where data will be saved.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio Profiling")
	void SetOutputDirectory(const FString& InOutputDirectory = TEXT(""));

	/**
	 * Starts an audio profiling session.
	 * Configures the profiling timer and begins data collection at specified intervals.
	 * Will log a warning if profiling is already running.
	 * 
	 * @param InSessionName Name of the profiling session, used in filenames and reports.
	 * @param IntervalSeconds Time interval between data captures in seconds.
	 * @param ExpectedDurationSeconds Expected duration of the profiling session.
	 * @param WorldContext Reference to the world in which profiling is taking place.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio Profiling")
	void StartProfiling(
		const FString& InSessionName = TEXT(""),
		float IntervalSeconds = 0.f,
		float ExpectedDurationSeconds = 60.f,
		const UWorld* WorldContext = nullptr
	   );
	
	/**
	 * Stops the current profiling session and exports collected data.
	 * Cleans up the timer and exports data to CSV and Markdown files.
	 * No effect if profiling is not currently active.
	 * @param WorldContext Reference to the world in which profiling is taking place.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio Profiling")
	void StopProfiling(const UWorld* WorldContext = nullptr);
	
	/**
	 * Adds a named bookmark to the profiling session at the current time.
	 * Useful for marking significant events during profiling.
	 * @param InName Name of the bookmark for later reference.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio Profiling")
	void AddBookmark(const FString& InName);

	/**
	 * Retrieves the current profiling data model.
	 * @return The current audio profiler model containing all collected data.
	 */
	UFUNCTION(BlueprintCallable, Category = "Audio Profiling")
	const FAudioProfilerModel& GetProfilingData() const;
	
private:
	/**
	 * Captures a snapshot of the current audio state.
	 * Collects audio metrics from the active audio engine and adds them to the profiling data.
	 * Called periodically during profiling based on the specified interval.
	 * @param AudioDevice the audio device to capture
	 */
	void CaptureProfilingData();

	/**
	 * Exports the collected profiling data to CSV and Markdown files.
	 * Called when profiling is stopped.
	 */
	void ExportProfilingData() const;
	
	/**
	 * Builds a formatted session string from the session name.
	 * Adds timestamp and sanitizes the name for file system compatibility.
	 * @param InSessionName The base name of the session.
	 * @return A formatted session string suitable for use in filenames.
	 */
	static FString BuildSessionString(const FString& InSessionName);
	
	/**
	 * Builds a full file path for a session output file.
	 * Combines the output directory with session name and file type.
	 * @param InFileType The file extension/type (e.g., "csv", "md").
	 * @return Full path to the output file.
	 */
	FString BuildSessionPath(const FString& InFileType) const;

	/**
	 * Builds the content for the CSV export file.
	 * Formats all collected data points into CSV rows.
	 * @return String containing the formatted CSV data.
	 */
	FString BuildCSVContent() const;
	
	/**
	 * Builds the header section for the Markdown report.
	 * Creates a title, summary, and link to the CSV data.
	 * @param CSVFilepath Path to the CSV file referenced in the markdown.
	 * @return String containing the markdown header content.
	 */
	FString BuildMDHeader(const FString& CSVFilepath) const;

	/**
	 * Builds the full Markdown report content.
	 * Adds detailed analytics and bookmarks to the header.
	 * @param MDHeader The header section of the markdown report.
	 * @return String containing the complete markdown report.
	 */
	FString BuildMDContent(const FString& MDHeader) const;

	/**
	 * The data model containing all captured audio profiling information.
	 * Stores metrics like CPU usage, memory consumption, and active sounds.
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Audio Profiling",
		meta = (
			AllowPrivateAccess = "true",
			ShowOnlyInnerProperties
			))
	FAudioProfilerModel ProfilingData;

	/**
	 * Map of timestamps to bookmark names.
	 * Used to mark significant events during the profiling session.
	 */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category="Audio Profiling",
		meta = (
			AllowPrivateAccess = "true",
			ShowOnlyInnerProperties
			))
	TMap<float, FString> ProfilingBookmarks;

	/**
	 * Timer delegate for periodic data capture.
	 * Binds to the CaptureProfilingData method.
	 */
	FTimerDelegate ProfilingTimerDelegate;

	/**
	 * Timer handle for the profiling update timer.
	 * Used to manage the timing of data captures.
	 */
	FTimerHandle ProfilingTimerHandle;

	/**
	 * Flag indicating whether profiling is currently active.
	 * Prevents starting multiple profiling sessions simultaneously.
	 */
	bool bIsProfiling;

	/**
	 * Value of Bookmark map size.
	 * To prepare data in right order for csv.
	 */
	int LastBookMarksNum;
	
	/**
	 * Pointer to audio device
	 */
	FAudioDevice* AudioDevice;
};