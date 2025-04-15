/**
 * @file AudioCharDefinitions.h
 * @author Markus Schramm
 * @brief concepts, enums, macros and statics for this module
 */

#pragma once

/**
 * @enum EAudioCharCompType
 * @brief Defines size of parameters getting propagated as audio components.
 * NumAudioCharComps is the default scalar array size of AudioPawnComponents
 *
 * So we can iterate through Objects and are able to create Arrays.
 */
UENUM(BlueprintType)
enum class EAudioCharCompType : uint8 {
	FootL	= 0  UMETA(DisplayName = "Foot Left"),
	FootR	= 1  UMETA(DisplayName = "Foot Right"),
	Jump	= 2  UMETA(DisplayName = "Jump"),
	Land	= 3  UMETA(DisplayName = "Land"),
	Foliage	= 4  UMETA(DisplayName = "Foliage"),
	// last value used as size indicator
	NumAudioCharComps   = 5 UMETA(DisplayName = "Num Charcter AudioComponents"),	
};

/**
 * @static AudioCharTypeAsInt
 * @brief utility for iterating and indexing
 * @param InType ScalarType to cast
 * @return EAudioCharCompType as int
 */
static int AudioCharTypeAsInt(const EAudioCharCompType& InType) {
	return static_cast<int>(InType);
}

/**
 * @static AudioCharTypeAsFName
 * @brief utility for naming
 * @param InType ScalarType to transform
 * @return EAudioCharCompType as FName
 */
static FName AudioCharTypeAsFName(const EAudioCharCompType& InType) noexcept {
	switch (InType) {
	case EAudioCharCompType::FootL:
		return FName("FootLeft");
	case EAudioCharCompType::FootR:
		return FName("FootRight");
	case EAudioCharCompType::Jump:
		return FName("Jump");
	case EAudioCharCompType::Land:
		return FName("Landing");
	case EAudioCharCompType::Foliage:
		return FName("Foliage");
	case EAudioCharCompType::NumAudioCharComps:
		return FName("NumAudioComponents");
	default:
		return FName("None");
	}
}

/**
 * @static IntAsAudioCharType
 * @brief utility for naming
 * @param TypeIndex int value to transform
 * @return EAudioCharCompType from int
 */
static EAudioCharCompType IntAsAudioCharType(const int& TypeIndex) noexcept {
	int i = FMath::Clamp(
		TypeIndex,
		0,
		AudioCharTypeAsInt(EAudioCharCompType::NumAudioCharComps) - 1
		);
	return static_cast<EAudioCharCompType>(i);
}

/**
 * @def AUDIOCHAR_NUM
 * @brief Macro for accessing size of scalar array of AudioCharComponents
 */
#ifndef AUDIOCHAR_NUM
#define AUDIOCHAR_NUM EAudioCharCompType::NumAudioCharComps
#endif