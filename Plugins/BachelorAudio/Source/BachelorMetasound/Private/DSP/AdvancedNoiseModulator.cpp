#include "AdvancedNoiseModulator.h"

FAdvancedNoiseModulator::FAdvancedNoiseModulator(
	const float& SampleRate,
	const FAdvancedNoiseParameterPack& ParameterPack,
	const uint8& Type
	) : SampleRate(SampleRate),
		ParameterPack(ParameterPack),
		Type(Type),
		Frequency(2000.f),
		Gain(0.f),
		Bandwidth(0.f),
		Scale(0.f),
		Offset(0.f),
		Coefficients{0.f, 0.f, 0.f, 0.f},
		FrequencyBuffer{2000.f, 2000.f, 2000.f, 2000.f},
		GainBuffer{0.f, 0.f, 0.f, 0.f},
		BandwidthBuffer{0.f, 0.f, 0.f, 0.f},
		ScaleBuffer{0.f, 0.f, 0.f, 0.f},
		OffsetBuffer{0.f, 0.f, 0.f, 0.f} {
	if(Type > 3) this->Type = 0;
	Init();
}

bool FAdvancedNoiseModulator::Init() {
	for(int i = 0; i < 4; ++i) {
		FrequencyBuffer[i] = 2000.f;
		GainBuffer[i] = 0.f;
		BandwidthBuffer[i] = 0.f;
		ScaleBuffer[i] = 0.f;
		OffsetBuffer[i] = 0.f;
	}
	return SetCoefficients();
}

bool FAdvancedNoiseModulator::Update() {
	if(!SetCoefficients()) return false;
	if(!SwapBuffers()) return false;
	return true;
}

bool FAdvancedNoiseModulator::SwapBuffers() {
	for (int i = 3; i > 0; i--) {
		switch(Type) {
		case 0:
			FrequencyBuffer[i] = FrequencyBuffer[i - 1];
			GainBuffer[i] = GainBuffer[i - 1];
			break;
		case 1:
			FrequencyBuffer[i] = FrequencyBuffer[i - 1];
			GainBuffer[i] = GainBuffer[i - 1];
			break;
		case 2:
			FrequencyBuffer[i] = FrequencyBuffer[i - 1];
			GainBuffer[i] = GainBuffer[i - 1];
			ScaleBuffer[i] = ScaleBuffer[i - 1];
			OffsetBuffer[i] = OffsetBuffer[i - 1];
			break;
		case 3:
			FrequencyBuffer[i] = FrequencyBuffer[i - 1];
			GainBuffer[i] = GainBuffer[i - 1];
			BandwidthBuffer[i] = BandwidthBuffer[i - 1];
			ScaleBuffer[i] = ScaleBuffer[i - 1];
			OffsetBuffer[i] = OffsetBuffer[i - 1];
			break;
		default:
			return false;
		}
	}
	FrequencyBuffer[0] = Frequency;
	GainBuffer[0] = Gain;
	if(Type < 2) return true;
	ScaleBuffer[0] = Scale;
	OffsetBuffer[0] = Offset;
	if(Type < 3) return true;
	BandwidthBuffer[0] = Bandwidth;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FWhiteNoiseModulator::FWhiteNoiseModulator(
	const float& SampleRate,
	const FAdvancedNoiseParameterPack& ParameterPack
	) : FAdvancedNoiseModulator(SampleRate, ParameterPack, 0) {}

FWhiteNoiseModulator::~FWhiteNoiseModulator() {
	for(int i = 0; i < 4; ++i) {
		FrequencyBuffer[i] = 2000.f;
		GainBuffer[i] = 0.f;
		BandwidthBuffer[i] = 0.f;
		ScaleBuffer[i] = 0.f;
		OffsetBuffer[i] = 0.f;
	}
}

float FWhiteNoiseModulator::Process() {
	return ProcessWhiteNoiseModulator();
}

bool FWhiteNoiseModulator::SetParameters(FAdvancedNoiseParameterPack& InOutParams) {
	ParameterPack = InOutParams;
	return SetParametersWhiteNoiseModulator();
}

void FWhiteNoiseModulator::SetBandwidth(const float InBandwidth) {
	ParameterPack.Bandwidth = InBandwidth;
}

void FWhiteNoiseModulator::SetScale(const float InScale) {
	ParameterPack.Scale = InScale;
}

void FWhiteNoiseModulator::SetOffset(const float InOffset) {
	ParameterPack.Offset = InOffset;
}

bool FWhiteNoiseModulator::SetCoefficients() { return true; }

float FWhiteNoiseModulator::ProcessWhiteNoiseModulator() { return 0; }

bool FWhiteNoiseModulator::SetParametersWhiteNoiseModulator() {
	Frequency = ParameterPack.Frequency;
	Gain = ParameterPack.Gain;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FPinkNoiseModulator::FPinkNoiseModulator(
	const float& SampleRate,
	const FAdvancedNoiseParameterPack& ParameterPack
) : FAdvancedNoiseModulator(SampleRate, ParameterPack, 1)
{}

FPinkNoiseModulator::~FPinkNoiseModulator() {
	for(int i = 0; i < 4; ++i) {
		FrequencyBuffer[i] = 2000.f;
		GainBuffer[i] = 0.f;
		BandwidthBuffer[i] = 0.f;
		ScaleBuffer[i] = 0.f;
		OffsetBuffer[i] = 0.f;
	}
}
float FPinkNoiseModulator::Process() { return ProcessPinkNoiseModulator(); }
bool FPinkNoiseModulator::SetParameters(FAdvancedNoiseParameterPack& InOutParams) { return false; }
void FPinkNoiseModulator::SetBandwidth(const float InBandwidth) {}
void FPinkNoiseModulator::SetScale(const float InScale) {}
void FPinkNoiseModulator::SetOffset(const float InOffset) {}
bool FPinkNoiseModulator::SetCoefficients() { return false; }
float FPinkNoiseModulator::ProcessPinkNoiseModulator() { return 0; }
bool FPinkNoiseModulator::SetParametersPinkNoiseModulator() { return false; }

FBrownNoiseModulator::FBrownNoiseModulator(
	const float& SampleRate,
	const FAdvancedNoiseParameterPack& ParameterPack
) : FAdvancedNoiseModulator(SampleRate, ParameterPack, 2)
{}
FBrownNoiseModulator::~FBrownNoiseModulator() {}
float FBrownNoiseModulator::Process() { return 0; }
bool FBrownNoiseModulator::SetParameters(FAdvancedNoiseParameterPack& InOutParams) { return false; }
void FBrownNoiseModulator::SetBandwidth(const float InBandwidth) {}
void FBrownNoiseModulator::SetScale(const float InScale) {}
void FBrownNoiseModulator::SetOffset(const float InOffset) {}
bool FBrownNoiseModulator::SetCoefficients() { return false; }
float FBrownNoiseModulator::ProcessBrownNoiseModulator() { return 0; }
bool FBrownNoiseModulator::SetParametersBrownNoiseModulator() { return false; }
void FBrownNoiseModulator::SetScaleBrownNoiseModulator(const float InScale) {
	ParameterPack.Scale = InScale;
	Scale = ParameterPack.Scale;
}

void FBrownNoiseModulator::SetOffsetBrownNoiseModulator(const float InOffset) {
	ParameterPack.Offset = InOffset;
	Offset = ParameterPack.Offset;
}

FGreenNoiseModulator::FGreenNoiseModulator(
	const float& SampleRate,
	const FAdvancedNoiseParameterPack& ParameterPack
) : FAdvancedNoiseModulator(SampleRate, ParameterPack, 3)
{}
FGreenNoiseModulator::~FGreenNoiseModulator() {}
float FGreenNoiseModulator::Process() { return 0; }
bool FGreenNoiseModulator::SetParameters(FAdvancedNoiseParameterPack& InOutParams) { return false; }
void FGreenNoiseModulator::SetBandwidth(const float InBandwidth) {}
void FGreenNoiseModulator::SetScale(const float InScale) {}
void FGreenNoiseModulator::SetOffset(const float InOffset) {}
bool FGreenNoiseModulator::SetCoefficients() { return false; }
float FGreenNoiseModulator::ProcessGreenNoiseModulator() { return 0; }

bool FGreenNoiseModulator::SetParametersGreenNoiseModulator(FAdvancedNoiseParameterPack& InOutParams) { return false; }

void FGreenNoiseModulator::SetBandwidthGreenNoiseModulator(const float InBandwidth) {
	ParameterPack.Bandwidth = InBandwidth;
	Bandwidth = ParameterPack.Bandwidth;
}

void FGreenNoiseModulator::SetScaleGreenNoiseModulator(const float InScale) {
	ParameterPack.Scale = InScale;
	Scale = ParameterPack.Scale;
}

void FGreenNoiseModulator::SetOffsetGreenNoiseModulator(const float InOffset) {
	ParameterPack.Offset = InOffset;
	Offset = ParameterPack.Offset;
}
