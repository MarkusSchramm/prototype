/**
 * @file AudioPawnFlyingComponent.cpp
 * @author Markus Schramm
 */

#include "Components/AudioPawnFlyingComponent.h"

#include "Actors/AudioPawnFlying.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Subsystems/AudioProfilerSubsystem.h"

UAudioPawnFlyingComponent::UAudioPawnFlyingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	DeveloperSettings.Owner = GetOwner();
	Model.InitScalars();
	UE_LOG(LogAudioPlayerPawnModule, Log, TEXT("UAudioPawnFlyingComponent constructed"));
}

UAudioPawnFlyingComponent::UAudioPawnFlyingComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	DeveloperSettings.Owner = GetOwner();
	Model.InitScalars();
	UE_LOG(LogAudioPlayerPawnModule, Log, TEXT("UAudioPawnFlyingComponent with ObjectInitializer constructed"));
}

void UAudioPawnFlyingComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName
		= (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UAudioPawnFlyingComponent, Sound)) {
		UE_LOG(LogAudioPlayerPawnModule, Display, TEXT("Sound changed"));
		CheckSound();
	}
}

void UAudioPawnFlyingComponent::SetMood_Implementation(float MoodScalar) {
	Model.Scalars[ScalarTypeAsInt(EAudioPawnScalarType::MoodScalar)].Value = MoodScalar;
	if(!DeveloperSettings.bShouldProfile) return;
	if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
		subsystem->AddBookmark(FString::Printf(TEXT("Mood scalar set to %f"), MoodScalar));
	}
}

void UAudioPawnFlyingComponent::SetEnergy_Implementation(float EnergyScalar) {
	Model.Scalars[ScalarTypeAsInt(EAudioPawnScalarType::EnergyScalar)].Value = EnergyScalar;
	if(!DeveloperSettings.bShouldProfile) return;
	if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
		subsystem->AddBookmark(FString::Printf(TEXT("Energy scalar set to %f"), EnergyScalar));
	}
}

void UAudioPawnFlyingComponent::SetRain_Implementation(float RainScalar) {
	Model.Scalars[ScalarTypeAsInt(EAudioPawnScalarType::RainScalar)].Value = RainScalar;
	if(!DeveloperSettings.bShouldProfile) return;
	if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
		subsystem->AddBookmark(FString::Printf(TEXT("Rain scalar set to %f"), RainScalar));
	}
}

void UAudioPawnFlyingComponent::SetWind_Implementation(float WindScalar) {
	Model.Scalars[ScalarTypeAsInt(EAudioPawnScalarType::WindScalar)].Value = WindScalar;
	if(!DeveloperSettings.bShouldProfile) return;
	if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
		subsystem->AddBookmark(FString::Printf(TEXT("Wind scalar set to %f"), WindScalar));
	}
}

void UAudioPawnFlyingComponent::SetTemperature_Implementation(float TemperatureScalar) {
	Model.Scalars[ScalarTypeAsInt(EAudioPawnScalarType::TemperatureScalar)].Value = TemperatureScalar;
	if(!DeveloperSettings.bShouldProfile) return;
	if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
		subsystem->AddBookmark(FString::Printf(TEXT("Temperature scalar set to %f"), TemperatureScalar));
	}
}

void UAudioPawnFlyingComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateScalars();
}

void UAudioPawnFlyingComponent::CheckSound() {
	if(Sound == nullptr) return;
	for(const auto& scalar : Model.Scalars) {
		if(!Sound->IsParameterValid(scalar.MetasoundInputName)) {
			UE_LOG(LogAudioPlayerPawnModule, Display,
				TEXT("Your sound is not supported by this component.\nPlease use the scalar parameters "));
			UE_LOG(LogAudioPlayerPawnModule, Display,
				TEXT("Please use the scalar.MetaSoundInputName '%s' parameters as input for your sound"),
				*scalar.MetasoundInputName.ToString());
			return;
		}
	}
}

void UAudioPawnFlyingComponent::UpdateScalars() {
	for(auto& scalar : Model.Scalars) {
		ChooseScalarUpdateMethod(scalar, scalar.Value);
		if(FMath::IsNearlyEqual(scalar.Value ,scalar.LastValue))
			break;
		SetInputMetasound(scalar.MetasoundInputName, scalar.Value);
		scalar.LastValue = scalar.Value;
	}
}

void UAudioPawnFlyingComponent::BeginPlay() {
	Super::BeginPlay();
	CheckSound();
	UpdateScalars();
	FadeIn(1.f, 1.f);
}

void UAudioPawnFlyingComponent::BeginDestroy() {
	Super::BeginDestroy();
	FadeOut(1.f, 0.f);
}

void UAudioPawnFlyingComponent::ChooseScalarUpdateMethod(const FAudioPawnScalarModel& InScalar, float& InOutCurrent) const {
	switch(InScalar.Type) {
	case EAudioPawnScalarType::SpeedScalar: 
		SetSpeedScalar(InOutCurrent);
		if(!DeveloperSettings.bShouldProfile) return;
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Speed scalar set to %f"), InOutCurrent));
		}
		break;
		
	case EAudioPawnScalarType::WeightScalar:
		SetWeightScalar(InOutCurrent);
		if(!DeveloperSettings.bShouldProfile) return;
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Weight scalar set to %f"), InOutCurrent));
		}
		break;
		
	case EAudioPawnScalarType::SurfaceScalar:
		SetSurfaceScalar(InOutCurrent);
		if(!DeveloperSettings.bShouldProfile) return;
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Surface scalar set to %f"), InOutCurrent));
		}
		break;
		
	case EAudioPawnScalarType::ImpactScalar:
		SetImpactScalar(InOutCurrent);
		if(!DeveloperSettings.bShouldProfile) return;
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Impact scalar set to %f"), InOutCurrent));
		}
		break;
		
	case EAudioPawnScalarType::LubricationScalar:
		SetLubricationScalar(InOutCurrent);
		if(!DeveloperSettings.bShouldProfile) return;
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Lubrication scalar set to %f"), InOutCurrent));
		}
		break;
		
	case EAudioPawnScalarType::MoodScalar:
	case EAudioPawnScalarType::EnergyScalar:
	case EAudioPawnScalarType::RainScalar:
	case EAudioPawnScalarType::WindScalar:
	case EAudioPawnScalarType::TemperatureScalar:
		break;
		
	case EAudioPawnScalarType::NumAudioPawnScalars:
	default:
		UE_LOG(LogAudioPlayerPawnModule, Error, TEXT("Scalar is not supported."));
		break;
	}
}

void UAudioPawnFlyingComponent::SetSpeedScalar(float& InOutCurrent) const {
	if(!DeveloperSettings.Owner->GetClass()->ImplementsInterface(UAudioPawnFlyingProvider::StaticClass()))
		return;
	float maxSpeed
		= IAudioPawnFlyingProvider::Execute_GetAudioPawnFlyingMovementComponent(DeveloperSettings.Owner)->GetMaxSpeed();
	if(maxSpeed > 0)
		InOutCurrent = GetOwner()->GetVelocity().Length() / maxSpeed;
}

void UAudioPawnFlyingComponent::SetWeightScalar(float& InOutCurrent) const {
	if(!DeveloperSettings.Owner->GetClass()->ImplementsInterface(UAudioPawnFlyingProvider::StaticClass()))
		return;
	InOutCurrent
		= FMath::Clamp(
			IAudioPawnFlyingProvider::Execute_GetAudioPawnFlyingMeshComponent(DeveloperSettings.Owner)->GetMass()
				/ 200.f ,
			0.f,
			1.f
			);
}

void UAudioPawnFlyingComponent::SetSurfaceScalar(float& InOutCurrent) const {
	InOutCurrent = 0.f;
}

void UAudioPawnFlyingComponent::SetImpactScalar(float& InOutCurrent) const {
	InOutCurrent = 0.f;
}

void UAudioPawnFlyingComponent::SetLubricationScalar(float& InOutCurrent) const {
	InOutCurrent = 0.f;
}
