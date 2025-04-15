/**
 * @file AudioPawnDefinitions.h
 * @author Markus Schramm
 * @brief concepts, enums, macros and statics for this module
 */

#pragma once

/**
 * @concept PawnAudioInput
 * @brief Concept to only allow variables of types int32, float or bool.
 * 
 * So we can communicate towards Metasound.
 */
template<typename T>
concept PawnAudioInput
	=	std::is_same_v<int32, T>
	||	std::is_same_v<float, T>
	||	std::is_same_v<bool, T>;

/**
 * @enum EAudioPawnScalarType
 * @brief Defines size of parameters getting propagated to Metasound.
 * NumAudioPawnScalars is the default scalar array size of AudioPawnComponents
 *
 * So we can iterate through Objects and are able to create Arrays.
 */
UENUM(BlueprintType)
enum class EAudioPawnScalarType : uint8 {
	SpeedScalar			  = 0  UMETA(DisplayName = "Speed Scalar"),
	MoodScalar			  = 1  UMETA(DisplayName = "Mood Scalar"),
	EnergyScalar		  = 2  UMETA(DisplayName = "Energy Scalar"),
	RainScalar			  = 3  UMETA(DisplayName = "Rain Scalar"),
	WindScalar			  = 4  UMETA(DisplayName = "Wind Scalar"),
	TemperatureScalar	  = 5  UMETA(DisplayName = "Temperature Scalar"),
	WeightScalar		  = 6  UMETA(DisplayName = "Weight Scalar"),
	SurfaceScalar		  = 7  UMETA(DisplayName = "Surface Scalar"),
	ImpactScalar		  = 8  UMETA(DisplayName = "Roll Scalar"),
	LubricationScalar	  = 9 UMETA(DisplayName = "Lubrication Scalar"),
	// last value used as size indicator
	NumAudioPawnScalars   = 10 UMETA(DisplayName = "Num Pawn Scalars"),	
};

/**
 * @static ScalarTypeAsInt
 * @brief utility for iterating and indexing
 * @param InType ScalarType to cast
 * @return EAudioSpawnScalarType as int
 */
static int ScalarTypeAsInt(const EAudioPawnScalarType& InType) {
	return static_cast<int>(InType);
}

/**
 * @static ScalarTypeAsFName
 * @brief utility for naming
 * @param InType ScalarType to transform
 * @return EAudioSpawnScalarType as FName
 */
static FName ScalarTypeAsFName(const EAudioPawnScalarType& InType) noexcept {
	switch (InType) {
	case EAudioPawnScalarType::SpeedScalar:
		return FName("SpeedScalar");
	case EAudioPawnScalarType::MoodScalar:
		return FName("MoodScalar");
	case EAudioPawnScalarType::EnergyScalar:
		return FName("EnergyScalar");
	case EAudioPawnScalarType::RainScalar:
		return FName("RainScalar");
	case EAudioPawnScalarType::WindScalar:
		return FName("WindScalar");
	case EAudioPawnScalarType::TemperatureScalar:
		return FName("TemperatureScalar");
	case EAudioPawnScalarType::WeightScalar:
		return FName("WeightScalar");
	case EAudioPawnScalarType::SurfaceScalar:
		return FName("SurfaceScalar");
	case EAudioPawnScalarType::ImpactScalar:
		return FName("ImpactScalar");
	case EAudioPawnScalarType::LubricationScalar:
		return FName("LubricationScalar");
	case EAudioPawnScalarType::NumAudioPawnScalars:
		return FName("NumScalars");
	default:
		return FName("None");
	}
}

/**
 * @static ScalarTypeAsFName
 * @brief utility for naming
 * @param TypeIndex int value to transform
 * @return EAudioSpawnScalarType from int
 */
static EAudioPawnScalarType IntAsScalarType(const int& TypeIndex) noexcept {
	int i = FMath::Clamp(
		TypeIndex,
		0,
		ScalarTypeAsInt(EAudioPawnScalarType::NumAudioPawnScalars)
		);
	return static_cast<EAudioPawnScalarType>(i);
}

/**
 * @def SCALAR_NUM
 * @brief Macro for accessing size of scalar array of AudioPaenComponents
 */
#ifndef SCALAR_NUM
#define SCALAR_NUM EAudioPawnScalarType::NumAudioPawnScalars
#endif