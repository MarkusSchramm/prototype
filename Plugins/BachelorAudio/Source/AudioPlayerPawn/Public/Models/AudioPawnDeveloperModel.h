/**
* @file AudioPawnDeveloperModel.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "AudioPawnDeveloperModel.generated.h"

/**
 * @struct FAudioPawnDeveloperModel
 * @brief Development and debugging configuration for the Audio Pawn system.
 * 
 * @details This struct contains various settings and parameters that are primarily used
 * during development, debugging, and profiling of the Audio Pawn system. It provides
 * options to enable debugging features, configure trace parameters, and reference
 * the owner actor.
 */
USTRUCT(BlueprintType, Category = "Audio")
struct AUDIOPLAYERPAWN_API FAudioPawnDeveloperModel {
    GENERATED_BODY()

    /**
     * @brief Reference to the owner actor of this audio configuration.
     * 
     * @details This pointer holds a reference to the actor that owns the component
     * using this developer model. It allows for context-specific operations and
     * debug visualizations in the editor and during runtime.
     */
    UPROPERTY(VisibleAnywhere, Category = "Developer")
    AActor* Owner{nullptr};

    /**
     * @brief Flag to enable or disable debug visualizations and logging.
     * 
     * @details When set to true, the system will display debug information such as
     * on-screen messages, trace lines, and may log additional information to help
     * with troubleshooting audio behaviors.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Developer | Debug", meta = (AllowPrivateAccess = "true"))
    bool bShouldDebug{false};

    /**
     * @brief Flag to enable or disable performance profiling.
     * 
     * @details When set to true, the system will collect and report performance metrics
     * related to audio processing. This can help identify performance bottlenecks or
     * optimization opportunities in the audio system.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Developer | Debug", meta = (AllowPrivateAccess = "true"))
    bool bShouldProfile{false};

    /**
     * @brief The length of debug trace lines.
     * 
     * @details Specifies the length of any debug visualization traces (such as raycasts)
     * that might be used to display audio-relevant information in the editor or during
     * gameplay when debugging is enabled.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Developer | Debug", meta = (AllowPrivateAccess = "true"))
    float TraceLength{20.f};

    /**
     * @brief The radius of debug trace spheres.
     * 
     * @details Specifies the radius of any debug visualization spheres that might be
     * used to represent audio sources, listeners, or areas of effect when debugging
     * is enabled.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Developer | Debug", meta = (AllowPrivateAccess = "true"))
    float TraceRadius{50.f};

    /**
     * @brief A safe pointer to an object associated with this developer model.
     * 
     * @details This pointer can be used to reference any UObject that might be
     * relevant to debugging or development features. The pointer is not exposed
     * to the UI or Blueprints and is primarily used for internal C++ operations.
     */
    UPROPERTY()
    UObject* SafeObjectPointer;
};