/**
 * @file AudioPawnFlyingComponent.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioPlayerPawnModule.h"
#include "Components/AudioComponent.h"
#include "Models/AudioPawnFlyingModel.h"
#include "Definitions/AudioPawnDefinitions.h"
#include "Interfaces/IMoodScalarManager.h"
#include "Interfaces/IWeatherScalarManager.h"
#include "AudioPawnFlyingComponent.generated.h"

/**
 * @class UAudioPawnFlyingComponent
 * @brief Audio component that handles dynamic sound playback for flying pawns
 * 
 * This component manages audio playback for flying pawns with support for mood, energy,
 * weather conditions and various physical state scalars that affect sound parameters.
 * It implements both IMoodScalarManager and IWeatherScalarManager interfaces to respond
 * to environmental and gameplay state changes.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AUDIOPLAYERPAWN_API UAudioPawnFlyingComponent
    :  public UAudioComponent,
       public FAudioPawnFlyingModel,
       public IMoodScalarManager,
       public IWeatherScalarManager {
    GENERATED_BODY()

public:
    /**
     * Default constructor for UAudioPawnFlyingComponent
     * Initializes component defaults and setup
     */
    UAudioPawnFlyingComponent();

    /**
     * Constructor with object initializer
     * @param ObjectInitializer The FObjectInitializer used to construct this instance
     */
    explicit UAudioPawnFlyingComponent(const FObjectInitializer& ObjectInitializer);
   
    /**
     * Performs per-frame updates for the audio component
     * Updates audio parameters based on current scalar values
     * 
     * @param DeltaTime Time elapsed since last tick
     * @param TickType Type of tick (normal, during physics, etc.)
     * @param ThisTickFunction Pointer to this component's tick function
     */
    virtual void TickComponent(
       float DeltaTime,
       ELevelTick TickType,
       FActorComponentTickFunction* ThisTickFunction
    ) override;
   
    /**
     * Called when a property is changed in the editor
     * Updates audio parameters when properties are modified
     * 
     * @param PropertyChangedEvent Information about which property changed
     */
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
   
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
   
    /**
     * Verifies sound asset is loaded and playable
     * Blueprint-exposed function for manual audio checks
     */
    UFUNCTION(BlueprintCallable)
    void CheckSound();

    /**
     * Forces an update of all scalar values affecting audio
     * Blueprint-exposed function to refresh audio parameters
     */
    UFUNCTION(BlueprintCallable)
    void UpdateScalars();
    
protected:
    /**
     * Called when the component is first initialized
     * Sets up initial audio state and begins playback if configured
     */
    virtual void BeginPlay() override;

    /**
     * Called before the component is destroyed
     * Ensures proper cleanup of audio resources
     */
    virtual void BeginDestroy() override;

private:
    /**
     * Determines the appropriate method to update a scalar based on its configuration
     * 
     * @param InScalar The scalar model containing update method and parameters
     * @param InOutCurrent Reference to the current scalar value to be updated
     */
    void ChooseScalarUpdateMethod(const FAudioPawnScalarModel& InScalar, float& InOutCurrent) const;

    /**
     * Updates the speed scalar based on pawn's current velocity
     * 
     * @param InOutCurrent Reference to the current speed scalar value to be updated
     */
    void SetSpeedScalar(float& InOutCurrent) const;

    /**
     * Updates the weight scalar based on pawn's current mass or load
     * 
     * @param InOutCurrent Reference to the current weight scalar value to be updated
     */
    void SetWeightScalar(float& InOutCurrent) const;

    /**
     * Updates the surface scalar based on the surface the pawn is interacting with
     * 
     * @param InOutCurrent Reference to the current surface scalar value to be updated
     */
    void SetSurfaceScalar(float& InOutCurrent) const;

    /**
     * Updates the impact scalar based on recent collisions or landings
     * 
     * @param InOutCurrent Reference to the current impact scalar value to be updated
     */
    void SetImpactScalar(float& InOutCurrent) const;

    /**
     * Updates the lubrication scalar affecting friction sounds
     * 
     * @param InOutCurrent Reference to the current lubrication scalar value to be updated
     */
    void SetLubricationScalar(float& InOutCurrent) const;

    /**
     * Type-safe method to set Metasound parameters based on input type
     * Uses template and concepts to handle different parameter types automatically
     * 
     * @param Name The name of the parameter to set in the Metasound
     * @param Value The value to set (will be converted to appropriate type)
     */
    FORCEINLINE void SetInputMetasound(const FName Name, const PawnAudioInput auto Value) {
       if(std::is_integral_v<decltype(Value)>) {
          this->SetIntParameter(Name, static_cast<int32>(Value));
          return;
       }
       if(std::is_floating_point_v<decltype(Value)>) {
          this->SetFloatParameter(Name, static_cast<float>(Value));
          return;
       }
       if(std::is_same_v<decltype(Value), bool>) {
          this->SetBoolParameter(Name, static_cast<bool>(Value));
          return;
       }
       UE_LOG(LogAudioPlayerPawnModule, Error, TEXT("Type is not supported."))
    }

    /**
     * Audio model containing all scalar parameters used by this component
     * Editable in Blueprint and used to configure audio behavior
     */
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Scalar", meta=(AllowPrivateAccess, DisplayName="Audio Scalars"))
    FAudioPawnFlyingModel Model;
};