/**
 * @file IWeatherScalarManager.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeatherScalarManager.generated.h"

/**
 * @interface UWeatherScalarManager
 * @brief Interface duplication to get the interface into the unreal engine reflection system
 * @see UInterface
 * @see IWeatherScalarManager
 */
UINTERFACE(BlueprintType)
class AUDIOPLAYERPAWN_API UWeatherScalarManager : public UInterface {
	GENERATED_BODY()
};

/**
 * @interface IWeatherScalarManager
 * @brief Interface for controlling weather-related scalar values
 *
 * If you want this Interface to be overrideable in C++ and Blueprints, you have to follow this Syntax:
 * Implementation:  virtual SetRain_Implementation(float RainScalar) override;
 * Check:           GetOwner()->GetClass()->ImplementsInterface(UWeatherScalarManager::StaticClass());
 * Execution:      IWeatherScalarManager::Execute_SetRain(ContextObject, RainScalar);
 */
class AUDIOPLAYERPAWN_API IWeatherScalarManager {
    GENERATED_BODY()

public:
    /**
     * Sets the rain intensity scalar value for audio/gameplay adjustments
     * @param RainScalar A normalized float value (typically 0.0-1.0) representing the current rain intensity
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Weather State")
    void SetRain(float RainScalar);

    /**
     * Sets the wind intensity scalar value for audio/gameplay adjustments
     * @param WindScalar A normalized float value (typically 0.0-1.0) representing the current wind intensity
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Weather State")
    void SetWind(float WindScalar);
    
    /**
     * Sets the temperature scalar value for audio/gameplay adjustments
     * @param TemperatureScalar A normalized float value (typically 0.0-1.0 where 0.0 is cold and 1.0 is hot)
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Weather State")
    void SetTemperature(float TemperatureScalar);
};