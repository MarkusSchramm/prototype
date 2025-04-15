// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IAttachedNotifyManager.h"
#include "Interfaces/IMoodScalarManager.h"
#include "Interfaces/IWeatherScalarManager.h"
#include "Models/AudioPawnWalkingModel.h"
#include "AudioPawnWalkingComponent.generated.h"

// Begin ThirdPersonTemplate
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
// End ThirdPersonTemplate

class UAudioComponent;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AUDIOPLAYERPAWN_API UAudioPawnWalkingComponent
	:	public UActorComponent,
		public FAudioPawnWalkingModel,
		public IMoodScalarManager,
		public IWeatherScalarManager,
		public IAttachedNotifyManager {
	GENERATED_BODY()

public:
	// Begin construction
	/**
	 * Default constructor for UAudioPawnFlyingComponent
	 * Initializes component defaults and setup
	 */
	UAudioPawnWalkingComponent();

	/**
	 * Constructor with object initializer
	 * @param ObjectInitializer The FObjectInitializer used to construct this instance
	 */
	explicit UAudioPawnWalkingComponent(const FObjectInitializer& ObjectInitializer);
	// End construction

	// Begin override public UActorComponent
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
	// End override public UActorComponent

	// Begin override public UOpject
	/**
	 * Called when a property is changed in the editor
	 * Updates audio parameters when properties are modified
	 * 
	 * @param PropertyChangedEvent Information about which property changed
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End override public UObject
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UAudioComponent>> AudioComponents;
};
