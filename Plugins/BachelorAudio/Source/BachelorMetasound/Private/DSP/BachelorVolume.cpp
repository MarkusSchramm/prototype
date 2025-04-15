/**
 * @file BachelorVolume.cpp
 * @brief Volume processor implementation for BachelorDSP.
 * 
 * Defines a simple amplitude-based gain processor that inherits from FProcessorBase.
 */


#include "DSP/BachelorVolume.h"

BachelorDSP::FBachelorVolume::FBachelorVolume()
	: FProcessorBase(EDSPType::Volume), Amplitude(0.f) {}

BachelorDSP::FBachelorVolume::FBachelorVolume(const float DefaultAmplitude)
	: FProcessorBase(EDSPType::Volume), Amplitude(DefaultAmplitude) {}

void BachelorDSP::FBachelorVolume::Init() {
	InitVolume();
}

void BachelorDSP::FBachelorVolume::Process(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) {
	ProcessVolumeBuffer(InBuffer, OutBuffer, InNumSamples);
}

void BachelorDSP::FBachelorVolume::SetAmplitude(const float NewAmplitude) {
	Amplitude = NewAmplitude;
}

void BachelorDSP::FBachelorVolume::InitVolume() {}

void BachelorDSP::FBachelorVolume::ProcessVolumeBuffer(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) {
	// Uncomment to profile the cost of this DSP processing in Unreal Insights
	//TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FVolume::ProcessAudioBuffer"))

	// Naive version (and without parameter smoothing)
	for (int32 Index = 0; Index < InNumSamples; ++Index) {
		OutBuffer[Index] = Amplitude * InBuffer[Index];
	}
}
