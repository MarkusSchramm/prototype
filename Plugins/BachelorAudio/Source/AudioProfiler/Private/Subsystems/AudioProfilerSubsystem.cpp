// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/AudioProfilerSubsystem.h"

#include "AudioMixerBlueprintLibrary.h"
#include "AudioProfilerModule.h"
#include "Models/AudioProfilerDeveloperModel.h"

UAudioProfilerSubsystem::UAudioProfilerSubsystem()
: bIsProfiling(false),
  LastBookMarksNum(0),
  AudioDevice(nullptr) {
	const UAudioProfilerDeveloperSettings* settings = GetDefault<UAudioProfilerDeveloperSettings>();

	ProfilingData.AudioProfilerSettings.ProfilingMode = settings->ProfilingMode;
	ProfilingData.AudioProfilerSettings.DebugMode = settings->DebugMode;
	ProfilingData.AudioProfilerSettings.OutputPath
		= settings->OutputDirectory.IsEmpty()
			  ? (FPaths::ProjectSavedDir() + TEXT("Profiling/"))
			  : settings->OutputDirectory;

	ProfilingData.AudioProfilerSettings.Interval = settings->ProfilingInterval;

	if(ProfilingData.AudioProfilerSettings.DebugMode == EAudioProfilerDebuggingType::NoDebugging) return;

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("UAudioProfilingSubsystem constructed")
	);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Verbose,
		LogAudioProfiler,
		Log,
		TEXT("Output directory set to %s"),
		*ProfilingData.AudioProfilerSettings.OutputPath
	);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Verbose,
		LogAudioProfiler,
		Log,
		TEXT("Profiling interval set to %fs"),
		ProfilingData.AudioProfilerSettings.Interval
	);

	switch(ProfilingData.AudioProfilerSettings.ProfilingMode) {
	case EAudioProfilerProfilingType::NoProfiling:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling disabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingAudioDevice:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling on audio device metrics enabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingSounds:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling on sound metrics enabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingFull:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling enabled"));
		break;
	}
}

UAudioProfilerSubsystem::UAudioProfilerSubsystem(const FObjectInitializer& ObjectInitializer)
: bIsProfiling(false),
  LastBookMarksNum(0),
  AudioDevice(nullptr) {
	const UAudioProfilerDeveloperSettings* settings = GetDefault<UAudioProfilerDeveloperSettings>();

	ProfilingData.AudioProfilerSettings.ProfilingMode = settings->ProfilingMode;
	ProfilingData.AudioProfilerSettings.DebugMode = settings->DebugMode;
	ProfilingData.AudioProfilerSettings.OutputPath
		= settings->OutputDirectory.IsEmpty()
			  ? (FPaths::ProjectSavedDir() + TEXT("Profiling/"))
			  : settings->OutputDirectory;

	ProfilingData.AudioProfilerSettings.Interval = settings->ProfilingInterval;

	if(ProfilingData.AudioProfilerSettings.DebugMode == EAudioProfilerDebuggingType::NoDebugging) return;

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("UAudioProfilingSubsystem constructed")
	);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Verbose,
		LogAudioProfiler,
		Log,
		TEXT("Output directory set to %s"),
		*ProfilingData.AudioProfilerSettings.OutputPath
	);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Verbose,
		LogAudioProfiler,
		Log,
		TEXT("Profiling interval set to %fs"),
		ProfilingData.AudioProfilerSettings.Interval
	);

	switch(ProfilingData.AudioProfilerSettings.ProfilingMode) {
	case EAudioProfilerProfilingType::NoProfiling:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling disabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingAudioDevice:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling on audio device metrics enabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingSounds:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling on sound metrics enabled"));
		break;
	case EAudioProfilerProfilingType::ProfilingFull:
		UE_LOG(LogAudioProfiler, Log, TEXT("Profiling enabled"));
		break;
	}
}

UAudioProfilerSubsystem::~UAudioProfilerSubsystem() {
	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("UAudioProfilingSubsystem destructed")
		);
	ProfilingBookmarks.Empty();
}

void UAudioProfilerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Verbose,
		LogAudioProfiler,
		Log,
		TEXT("Base subsystem of audio profiler initialized.")
		);

	if(ProfilingData.AudioProfilerSettings.ProfilingMode == EAudioProfilerProfilingType::NoProfiling)
		return;

	SetOutputDirectory();

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("Audio profiler subsystem initialized.")
		);
}

void UAudioProfilerSubsystem::Deinitialize() {
	Super::Deinitialize();

	ProfilingBookmarks.Empty();

	if(ProfilingData.AudioProfilerSettings.ProfilingMode == EAudioProfilerProfilingType::NoProfiling)
		return;

	StopProfiling();

	Super::Deinitialize();

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("Audio Profiler deinitialized")
		);
}

void UAudioProfilerSubsystem::SetOutputDirectory(const FString& InOutputDirectory) {
	if (!InOutputDirectory.IsEmpty()) ProfilingData.AudioProfilerSettings.OutputPath = InOutputDirectory;

	if(IFileManager::Get().DirectoryExists(*ProfilingData.AudioProfilerSettings.OutputPath))
		return;

	IFileManager::Get().MakeDirectory(*ProfilingData.AudioProfilerSettings.OutputPath, true);

	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Warning,
		LogAudioProfiler,
		Log,
		TEXT("Audio Profiler output directory is set to %s"),
		*ProfilingData.AudioProfilerSettings.OutputPath
		);
}

void UAudioProfilerSubsystem::StartProfiling(
	const FString& InSessionName,
	float IntervalSeconds,
	float ExpectedDurationSeconds,
	const UWorld* WorldContext
) {
	ProfilingData.AudioProfilerData.Empty();
	if(ProfilingData.AudioProfilerSettings.ProfilingMode == EAudioProfilerProfilingType::NoProfiling)
		return;

	if(bIsProfiling) {
		UE_CLOG(
			ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Warning,
			LogAudioProfiler,
			Log,
			TEXT("Profiler is already capturing")
			);
		return;
	}

	ProfilingData.AudioProfilerSettings.CurrentSessionName = InSessionName.IsEmpty()
		? BuildSessionString("AudioProfilingSession")
		: BuildSessionString(InSessionName);

	ProfilingData.AudioProfilerSettings.Interval = IntervalSeconds == 0.f
		? ProfilingData.AudioProfilerSettings.Interval
		: IntervalSeconds;

	const UWorld* World = !WorldContext
		? GetWorld()
		: WorldContext;

	AudioDevice = World->GetAudioDevice().GetAudioDevice();
	if(AudioDevice != nullptr) {
		ProfilingData.AudioProfilerHeader.SampleRate = AudioDevice->GetSampleRate();
		ProfilingData.AudioProfilerHeader.MaxChannels = AudioDevice->GetMaxChannels();
		ProfilingData.AudioProfilerHeader.MaxSources = AudioDevice->GetMaxSources();
	}

	ProfilingTimerDelegate = FTimerDelegate::CreateUObject(this, &UAudioProfilerSubsystem::CaptureProfilingData);
	
	ProfilingData.AudioProfilerHeader.Date = FDateTime::Now();
	ProfilingData.AudioProfilerHeader.WorldName = World->GetName();

	
	if(World == nullptr) {
		UE_CLOG(
			ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Error,
			LogAudioProfiler,
			Error,
			TEXT("Can not profile without world")
			);
		return;
	}

	World->GetTimerManager().SetTimer(
		ProfilingTimerHandle,
		ProfilingTimerDelegate,
		ProfilingData.AudioProfilerSettings.Interval,
		true
	);


	UAudioMixerBlueprintLibrary::StartRecordingOutput(
		World,
		ExpectedDurationSeconds
		);
	UAudioMixerBlueprintLibrary::StartAnalyzingOutput(World);
	
	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("%s started with...\n Path: %s\nInterval: %fs"),
		*ProfilingData.AudioProfilerSettings.CurrentSessionName,
		*ProfilingData.AudioProfilerSettings.OutputPath,
		ProfilingData.AudioProfilerSettings.Interval
		);

	bIsProfiling = true;
	
}

void UAudioProfilerSubsystem::StopProfiling(const UWorld* WorldContext) {
	if(!bIsProfiling) return;

	bIsProfiling = false;

	const UWorld* World = !WorldContext
	? GetWorld()
	: WorldContext;

	if(World == nullptr) return;

	World->GetTimerManager().ClearTimer(ProfilingTimerHandle);

	//UAudioMixerBlueprintLibrary::StopAnalyzingOutput(World);
	UAudioMixerBlueprintLibrary::StopRecordingOutput(
		World,
		EAudioRecordingExportType::WavFile,
		ProfilingData.AudioProfilerSettings.CurrentSessionName,
		ProfilingData.AudioProfilerSettings.OutputPath
		);

	ExportProfilingData();

	ProfilingBookmarks.Empty();
	UE_CLOG(
		ProfilingData.AudioProfilerSettings.DebugMode >= EAudioProfilerDebuggingType::Log,
		LogAudioProfiler,
		Log,
		TEXT("Profiling stopped")
		);
}

void UAudioProfilerSubsystem::AddBookmark(const FString& InName) {
	if(ProfilingData.AudioProfilerSettings.ProfilingMode < EAudioProfilerProfilingType::ProfilingSounds)
		return;
	
	double timestamp = FPlatformTime::Seconds();
	ProfilingBookmarks.Add(timestamp, InName);
}

const FAudioProfilerModel& UAudioProfilerSubsystem::GetProfilingData() const {
	return ProfilingData;
}

void UAudioProfilerSubsystem::CaptureProfilingData() {
	UE_LOG(LogAudioProfiler, Warning, TEXT("Timestamp capture"));
	FAudioProfilerTimestampModel timestamp;
	if(ProfilingBookmarks.Num() != LastBookMarksNum) {
		for(const auto& bookmark : ProfilingBookmarks) {
			timestamp.ActiveBookmarks.Add(FString::Printf(TEXT("%s: %f"), *bookmark.Value, bookmark.Key));
			ProfilingBookmarks.Remove(bookmark.Key);
		}
		LastBookMarksNum = ProfilingBookmarks.Num();
	}
	
	if(AudioDevice != nullptr) {
		TArray<FActiveSound*> activeSounds;
		for(const auto& sound : AudioDevice->GetActiveSounds()) {
			activeSounds.Add(sound);
		}
	
		timestamp.Timestamp = FPlatformTime::Seconds();
		timestamp.CurrentAudioDelta = AudioDevice->GetDeviceDeltaTime();
		timestamp.CurrentAudioTime = AudioDevice->GetAudioTime();
		timestamp.CurrentDelta = FApp::GetDeltaTime();
		timestamp.Framerate = FMath::Clamp(1 / timestamp.CurrentDelta, 0.f, 1000.f);
		timestamp.CPUUsage = FPlatformTime::GetCPUTime().CPUTimePct;
		timestamp.MemoryUsageMB = FPlatformMemory::GetStats().UsedPhysical / 1024.0f / 1024.0f;
		timestamp.MasterVolumeLin =  AudioDevice->GetPrimaryVolume();
		timestamp.Headroom =  AudioDevice->GetPlatformAudioHeadroom();
		timestamp.ActiveSoundCount = AudioDevice->GetNumActiveSources();
		timestamp.FreeSourcesCount = AudioDevice->GetNumFreeSources();

		FAudioProfilerSoundModel activeSound;
		for(const auto& sound : activeSounds) {
			activeSound.ActiveSoundName = sound->GetSound()->GetName();
			activeSound.ActiveSoundVolume = sound->GetVolume();
			for(const auto& value: activeSound.ActiveSoundValues) {
				activeSound.ActiveSoundValues.Add(value);
			}
			timestamp.ActiveSounds.Add(activeSound);
		}
	}
	
	UE_LOG(LogAudioProfiler, Warning, TEXT("Timestamp added"));

	ProfilingData.AudioProfilerData.Add(timestamp);
}

void UAudioProfilerSubsystem::ExportProfilingData() const {
	if(ProfilingData.AudioProfilerData.Num() == 0) {
		UE_LOG(LogAudioProfiler, Warning, TEXT("Profiling data is empty"));
		return;
	}

	const FString& CSVFilePath = BuildSessionPath(TEXT(".csv"));
	const FString& MDFilePath = BuildSessionPath(TEXT(".md"));
	FString CSVContent = BuildCSVContent();
	FFileHelper::SaveStringToFile(CSVContent, *CSVFilePath);

	UE_LOG(LogAudioProfiler, Error, TEXT("Data written to %s"), *CSVFilePath);

	FString MDHeader = BuildMDHeader(CSVFilePath);
	FString MDContent = BuildMDContent(MDHeader);
	FFileHelper::SaveStringToFile(MDContent, *MDFilePath);

	UE_LOG(LogAudioProfiler, Error, TEXT("Report written to %s"), *CSVFilePath);
}

FString UAudioProfilerSubsystem::BuildSessionString(const FString& InSessionName) {
	const FString time = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));
	return FString::Printf(TEXT("%s_%s"),*InSessionName, *time);
}

FString UAudioProfilerSubsystem::BuildSessionPath(
	const FString& InFileType = TEXT("")
	) const {
	const FString& name = ProfilingData.AudioProfilerSettings.CurrentSessionName;
	const FString& path = ProfilingData.AudioProfilerSettings.OutputPath;

	const FString& type = InFileType.IsEmpty()
		? TEXT(".txt")
		: InFileType;

	FString filepath = FString::Printf(TEXT("%s/%s%s"), *path, *name, *type);

	UE_LOG(LogAudioProfiler, Error, TEXT("%s does not exist"), *filepath);

	if(!IFileManager::Get().DirectoryExists(*path)) {
		UE_LOG(LogAudioProfiler, Error, TEXT("%s does not exist"), *filepath);
	};

	return filepath;
}

FString UAudioProfilerSubsystem::BuildCSVContent() const {
	FString CSVContent = TEXT(
		"Timestamp,AudioDeltaTime,AudioTime,DeltaTime,Framerate,CPUUsage,MemoryUsage,MasterVolume,Headroom,ActiveSoundCount,ActiveSoundNames\n"
		);
	for(const auto& data : ProfilingData.AudioProfilerData) {
		FString ActiveSoundNamesStr;
		for(const auto& sound : data.ActiveSounds) {
			ActiveSoundNamesStr += sound.ActiveSoundName + TEXT(";");
		}
		ActiveSoundNamesStr.RemoveFromEnd(TEXT(";"));
		CSVContent += FString::Printf(TEXT("%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%s\n"),
			data.Timestamp,
			data.CurrentAudioDelta,
			data.CurrentAudioTime,
			data.CurrentDelta,
			data.Framerate,
			data.CPUUsage,
			data.MemoryUsageMB,
			data.MasterVolumeLin,
			data.Headroom,
			data.ActiveSoundCount,
			*ActiveSoundNamesStr
		);
	}
	return CSVContent;
}

FString UAudioProfilerSubsystem::BuildMDHeader(const FString& CSVFilepath) const {
	FString MDHeader = FString::Printf(TEXT("# %s\n\n"), *ProfilingData.AudioProfilerHeader.SessionName);
	MDHeader += FString::Printf(TEXT("**Tester:** Markus Schramm\t **Date:** %s\n**Time:** %s\t\t**World:** %s\n"),
		*ProfilingData.AudioProfilerHeader.Date.ToFormattedString(TEXT("%d.%m.%Y")),
		*ProfilingData.AudioProfilerHeader.Date.ToFormattedString(TEXT("%H:%M:%S")),
		*ProfilingData.AudioProfilerHeader.WorldName
		);
	MDHeader += FString::Printf(TEXT("**CSV Path:**\t%s\n"), *CSVFilepath);
	MDHeader += FString::Printf(TEXT("**Sample Rate:**\t%d\n"), ProfilingData.AudioProfilerHeader.SampleRate);
	MDHeader += FString::Printf(TEXT("**Max Channels:**\t%d\n"), ProfilingData.AudioProfilerHeader.MaxChannels);
	MDHeader += FString::Printf(TEXT("**Max Sources:**\t%d\n"), ProfilingData.AudioProfilerHeader.MaxSources);
	MDHeader += FString::Printf(TEXT("**Audio Buffer Length:**\t%d\n"), ProfilingData.AudioProfilerHeader.BufferLength);
	MDHeader += FString::Printf(TEXT("**Num Audio Buffers:**\t%d\n"), ProfilingData.AudioProfilerHeader.NumBuffers);
	MDHeader += FString::Printf(TEXT("**Num Source Workers:**\t%d\n"), ProfilingData.AudioProfilerHeader.NumSourceWorkers);
	FString CSVFooter = TEXT("\n------------------\n\n**Profiling start**");
	return MDHeader;
}

FString UAudioProfilerSubsystem::BuildMDContent(const FString& MDHeader) const {
	FString MDContent = MDHeader;
	MDContent += TEXT("\n## Profiling Data\n");
	MDContent += TEXT("| Timestamp | AudioDeltaTime | AudioTime | DeltaTime | Framerate | CPUUsage | MemoryUsage | MasterVolume | Headroom | ActiveSoundCount | ActiveBookmarks |\n");
	MDContent += TEXT("| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |\n");
	for(const auto& timestamp : ProfilingData.AudioProfilerData) {
		MDContent += FString::Printf(TEXT("| %f "), timestamp.Timestamp);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.CurrentAudioDelta);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.CurrentAudioTime);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.CurrentDelta);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.Framerate);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.CPUUsage);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.MemoryUsageMB);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.MasterVolumeLin);
		MDContent += FString::Printf(TEXT("| %f "), timestamp.Headroom);
		MDContent += FString::Printf(TEXT("| %d |"), timestamp.ActiveSoundCount);
		if(timestamp.ActiveBookmarks.Num() > 0) {
			int i = 0;
			for(const auto& bookmark : timestamp.ActiveBookmarks) {
				if(i == 0) 
					MDContent += FString::Printf(TEXT("| %s |\n"), *bookmark);
				else 
					MDContent += FString::Printf(TEXT("|  |  |  |  |  |  |  |  |  |  | %s |\n"), *bookmark);
			}
		} else 
			MDContent += TEXT("\n");
	}
	MDContent += TEXT("\n");
	return MDContent;
}