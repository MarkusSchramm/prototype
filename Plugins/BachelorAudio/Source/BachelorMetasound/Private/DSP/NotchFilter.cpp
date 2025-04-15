/**
 * @file NotchFilter.cpp
 * @brief Defines a digital notch filter class for real-time audio processing.
 * 
 * Implements a second-order IIR notch filter using the bilinear transform method.
 * Part of the BachelorDSP module and inherits from FProcessorBase.
 */


#include "DSP/NotchFilter.h"

BachelorDSP::FNotchFilter::FNotchFilter()
  :	FProcessorBase(EDSPType::NotchFilter),
	SamplingFrequency(),
	CutoffFrequency(),
	BandwidthCoefficient(),
	X(0.f), X1(0.f), X2(0.f),
	Y(0.f), Y1(0.f), Y2(0.f),
	Z(0.f), A(0.f), A1(0.f),
	B(0.f), B1(0.f), B2(0.f) {}

BachelorDSP::FNotchFilter::FNotchFilter(
	const float& SamplingFrequency, 
	const float& CutoffFrequency,
	const float& BandwidthCoefficient
) :	FProcessorBase(EDSPType::NotchFilter),
	SamplingFrequency(SamplingFrequency),
	CutoffFrequency(CutoffFrequency),
	BandwidthCoefficient(BandwidthCoefficient),
	X(0.f), X1(0.f), X2(0.f),
	Y(0.f), Y1(0.f), Y2(0.f),
	Z(0.f), A(0.f), A1(0.f),
	B(0.f), B1(0.f), B2(0.f) {}

void BachelorDSP::FNotchFilter::Init() {
	InitNotchFilter();
}

void BachelorDSP::FNotchFilter::Process(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) {
	ProcessNotchFilter(InBuffer, OutBuffer, InNumSamples);
}

void BachelorDSP::FNotchFilter::SetSamplingFrequency(const float& NewSamplingFrequency) {
	SamplingFrequency = NewSamplingFrequency;
	SetCoefficients();
}

void BachelorDSP::FNotchFilter::SetCutoffFrequency(const float& NewCutoffFrequency) {
	CutoffFrequency = NewCutoffFrequency;
	SetCoefficients();
}

void BachelorDSP::FNotchFilter::SetBandwidthCoefficient(const float& NewBandwidthCoefficient) {
	BandwidthCoefficient = NewBandwidthCoefficient;
	SetCoefficients();
}

void BachelorDSP::FNotchFilter::SetValues(
	const float& NewSamplingFrequency, 
	const float& NewCutoffFrequency, 
	const float& NewBandwidthCoefficient
) {
	SamplingFrequency = NewSamplingFrequency;
	CutoffFrequency = NewCutoffFrequency;
	BandwidthCoefficient = NewBandwidthCoefficient;
	SetCoefficients();
}

void BachelorDSP::FNotchFilter::InitNotchFilter() {
	SetCoefficients();
}

void BachelorDSP::FNotchFilter::ProcessNotchFilter(const float* InBuffer, float* OutBuffer, const int32 InNumSamples)
{
	for (int32 Index = 0; Index < InNumSamples; ++Index) {
		Y = B * X + B1 * X1 + B2 * X2 - A * Y1 - A1 * Y2;
		Y2 = Y1;
		Y1 = Y;
		X2 = X1;
		X1 = X;
		X = InBuffer[Index];

		if (Y > 32767) Y = 32767;
		else if (Y < -32768) Y = -32768;

		OutBuffer[Index] = Y;
	}
}

void BachelorDSP::FNotchFilter::SetCoefficients() {
	if ((SamplingFrequency < 0.0) || (CutoffFrequency < 0.0)) return;
	if (CutoffFrequency > (SamplingFrequency / 2)) return;
	if ((BandwidthCoefficient <= 0.0) || (BandwidthCoefficient >= 1.0)) return;

	Z = cos(2 * PI * CutoffFrequency / SamplingFrequency);
	B = (1 - BandwidthCoefficient) * (1 - BandwidthCoefficient) / (2 * (fabs(Z) + 1)) + BandwidthCoefficient;
	B2 = B;
	B1 = -2 * Z * B;
	A = -2 * Z * BandwidthCoefficient;
	A1 = BandwidthCoefficient * BandwidthCoefficient;

	Y = 0, Y1 = 0, Y2 = 0;
	X = 0, X1 = 0, X2 = 0;
}
