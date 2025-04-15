/**
 * @file AudioCaveSystem.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IMoodScalarManager.h"
#include "Interfaces/IWeatherScalarManager.h"
#include "AudioCaveSystem.generated.h"

/**
 * @struct FSoundDropInfo
 * @brief Stores metadata related to a falling audio source.
 * 
 * This struct is used to represent a sound drop instance, including its audio component,
 * starting and ending position, timing, and duration.
 */
USTRUCT()
struct FSoundDropInfo {
	GENERATED_USTRUCT_BODY()

	/**
	 * The audio component assigned to this sound drop.
	 */
	UPROPERTY()
	UAudioComponent* AudioComponent;

	/**
	 * World-space location where the drop starts.
	 */
	FVector StartLocation;

	
	/**
	 * World-space location where the drop ends (i.e., ground hit point).
	 */
	FVector EndLocation;

	/**
	 * Timestamp when the drop started. */
	float StartTime;

	/**
	 * Time the drop should take from start to impact.
	 */
	float Duration;
};

/**
 * @class AAudioCaveSystem
 * @brief Manages a pool of falling audio sources simulating sound events within a cave system.
 * 
 * This actor is designed to spawn, animate, and spatialize falling sound sources in a physical environment.
 * It uses line traces to determine drop paths and triggers impact sounds dynamically.
 */
UCLASS()
class AUDIOPLAYERPAWN_API AAudioCaveSystem
	:	public AActor,
		public IMoodScalarManager,
		public IWeatherScalarManager {
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor.
	 */
	AAudioCaveSystem();

protected:
	/**
	 * @brief Called when the game starts or when the actor is spawned.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Called every frame.
	 * @param DeltaTime Time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Spawns a new sound drop from a roof point to a ground hit.
	 */
	UFUNCTION()
	void SpawnAudioSource();
	
	/**
	 * @brief Processes all currently active/pending sound drops.
	 * 
	 * Animates movement and triggers impact sounds upon completion.
	 */
	void ProcessPendingSoundDrops();

	/**
	 * @brief Initializes a sound drop for the given audio component.
	 * @param AudioComponent The audio component to move and play.
	 * @param StartLocation The start position for the falling motion.
	 */
	void DropComponentToGroundAndPlay(UAudioComponent* AudioComponent, FVector StartLocation);

	/**
	 * Implementation of IMoodScalarManager::SetMood
	 * Updates the mood scalar affecting audio characteristics
	 * 
	 * @param MoodScalar Normalized value (0.0-1.0) representing current mood state
	 */
	virtual void SetMood_Implementation(float MoodScalar) override;

	/**
	 * Implementation of IMoodScalarManager::SetEnergy
	 * Updates the energy scalar affecting audio intensity
	 * 
	 * @param EnergyScalar Normalized value (0.0-1.0) representing current energy level
	 */
	virtual void SetEnergy_Implementation(float EnergyScalar) override;
   
	/**
	 * Implementation of IWeatherScalarManager::SetRain
	 * Updates the rain intensity scalar affecting audio
	 * 
	 * @param RainScalar Normalized value (0.0-1.0) representing rain intensity
	 */
	virtual void SetRain_Implementation(float RainScalar) override;

	/**
	 * Implementation of IWeatherScalarManager::SetWind
	 * Updates the wind intensity scalar affecting audio
	 * 
	 * @param WindScalar Normalized value (0.0-1.0) representing wind intensity
	 */
	virtual void SetWind_Implementation(float WindScalar) override;

	/**
	 * Implementation of IWeatherScalarManager::SetTemperature
	 * Updates the temperature scalar affecting audio
	 * 
	 * @param TemperatureScalar Normalized value (0.0-1.0) representing temperature (0=cold, 1=hot)
	 */
	virtual void SetTemperature_Implementation(float TemperatureScalar) override;

	/** Collection of sound assets played during the drop phase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> DropSounds;

	/** Collection of sound assets played upon impact with the ground. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> ImpactSounds;

	/** Size of the audio component pool used to recycle components for sound drops. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	int32 PoolSize = 10;

	/** Time interval between sound spawns. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float CustomSpawnTime = .2f;

	/** Whether to visualize trace lines in the editor for debugging purposes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Tracer")
	bool DrawDebugLines = true;

	/** Maximum distance used when tracing from the roof downward. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Tracer")
	float MaxRoofTraceDistance = 3000.f;

	/** Maximum distance used when tracing toward the ground. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Tracer")
	float MaxGroundTraceDistance = 5000.f;

	/** Minimum falling distance required to trigger a sound drop. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Tracer")
	float MinFallingDistance = 500.f;

	/** Speed multiplier applied to control the falling motion. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Tracer")
	float FallSpeedModifier = 1000.f;

	/** Queue of currently active or pending sound drop events. */
	TArray<FSoundDropInfo> PendingDrops;

private:
	/**
	 * @brief Retrieves an available audio component from the pool, or nullptr if all are active.
	 * 
	 * @return Pointer to a reusable UAudioComponent.
	 */
	UAudioComponent* GetAvailableAudioComponent();

	/** Timer handle for spawning sound events at a fixed interval. */
	FTimerHandle TimerHandle;

	/** Pool of reusable audio components used for efficient sound playback. */
	TArray<UAudioComponent*> AudioComponentPool;
};