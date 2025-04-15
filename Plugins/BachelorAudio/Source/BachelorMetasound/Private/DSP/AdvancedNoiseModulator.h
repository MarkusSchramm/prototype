#pragma once

struct FAdvancedNoiseParameterPack {
	float Frequency						= 2000.f;
	float Gain							= 0.f;
	float Bandwidth						= 0.f;
	float Scale							= 0.f;
	float Offset						= 0.f;
};

class BACHELORMETASOUND_API FAdvancedNoiseModulator {
public:
	FAdvancedNoiseModulator() = delete;
	virtual ~FAdvancedNoiseModulator() = default;
	
	FAdvancedNoiseModulator(
		const float& SampleRate,
		const FAdvancedNoiseParameterPack& ParameterPack,
		const uint8& Type
		);

	bool Init();
	bool Update();
	
	
	void SetType(const uint8& NewType) { Type = NewType; }
	uint8 GetType() const { return Type; }
	
	void SetFrequency(const float InFrequency) {
		ParameterPack.Frequency = InFrequency;
		Frequency = ParameterPack.Frequency;
	}
	float GetFrequency() const { return ParameterPack.Frequency; }

	void SetGain(const float InGain) {
		ParameterPack.Gain = InGain;
		Gain = ParameterPack.Gain;
	}
	
	float GetGain() const { return ParameterPack.Gain; }
	
	float GetBandwidth() const { return ParameterPack.Bandwidth; }
	
	float GetScale() const { return ParameterPack.Scale; }
	
	float GetOffset() const { return ParameterPack.Offset; }

protected:
	virtual float Process() = 0;
	virtual bool SetParameters(FAdvancedNoiseParameterPack& InOutParams) = 0;
	virtual void SetBandwidth(const float InBandwidth) = 0;
	virtual void SetScale(const float InScale) = 0;
	virtual void SetOffset(const float Offset) = 0;
	virtual bool SetCoefficients() = 0;

	const float& SampleRate;
	FAdvancedNoiseParameterPack ParameterPack;
	uint8 Type; // 0-White 1-Pink 2-Brown 3-Green
	
	float Frequency;
	float Gain;
	float Bandwidth;
	float Scale;
	float Offset;
	
	float Coefficients[4];
	float FrequencyBuffer[4];
	float GainBuffer[4];
	float BandwidthBuffer[4];
	float ScaleBuffer[4];
	float OffsetBuffer[4];
	
private:
	bool SwapBuffers();
};

class BACHELORMETASOUND_API FWhiteNoiseModulator final : public FAdvancedNoiseModulator {
public:
	FWhiteNoiseModulator() = delete;
	
	FWhiteNoiseModulator(
		const float& SampleRate,
		const FAdvancedNoiseParameterPack& ParameterPack
		);
	
	virtual ~FWhiteNoiseModulator() override;

	virtual float Process() override;
	virtual bool SetParameters(FAdvancedNoiseParameterPack& InOutParams) override;
	virtual void SetBandwidth(const float InBandwidth) override;
	virtual void SetScale(const float InScale) override;
	virtual void SetOffset(const float InOffset) override;
	
private:
	virtual bool SetCoefficients() override;
	
	float ProcessWhiteNoiseModulator();
	bool SetParametersWhiteNoiseModulator();
};

class BACHELORMETASOUND_API FPinkNoiseModulator final : public FAdvancedNoiseModulator {
public:
	FPinkNoiseModulator() = delete;
	
	FPinkNoiseModulator(
		const float& SampleRate,
		const FAdvancedNoiseParameterPack& ParameterPack
		);
	
	virtual ~FPinkNoiseModulator() override;

	virtual float Process() override;
	virtual bool SetParameters(FAdvancedNoiseParameterPack& InOutParams) override;
	virtual void SetBandwidth(const float InBandwidth) override;
	virtual void SetScale(const float InScale) override;
	virtual void SetOffset(const float InOffset) override;
	
private:
	virtual bool SetCoefficients() override;

	float ProcessPinkNoiseModulator();
	bool SetParametersPinkNoiseModulator();
};

class BACHELORMETASOUND_API FBrownNoiseModulator final : public FAdvancedNoiseModulator {
public:
	FBrownNoiseModulator() = delete;
	
	FBrownNoiseModulator(
		const float& SampleRate,
		const FAdvancedNoiseParameterPack& ParameterPack
		);
	
	virtual ~FBrownNoiseModulator() override;

	virtual float Process() override;
	virtual bool SetParameters(FAdvancedNoiseParameterPack& InOutParams) override;
	virtual void SetBandwidth(const float InBandwidth) override;
	virtual void SetScale(const float InScale) override;
	virtual void SetOffset(const float InOffset) override;
	
private:
	virtual bool SetCoefficients() override;

	float ProcessBrownNoiseModulator();
	bool SetParametersBrownNoiseModulator();
	void SetScaleBrownNoiseModulator(const float InScale);
	void SetOffsetBrownNoiseModulator(const float InOffset);
};

class BACHELORMETASOUND_API FGreenNoiseModulator final : public FAdvancedNoiseModulator {
public:
	FGreenNoiseModulator() = delete;
	
	FGreenNoiseModulator(
		const float& SampleRate,
		const FAdvancedNoiseParameterPack& ParameterPack
		);
	
	virtual ~FGreenNoiseModulator() override;

	virtual float Process() override;
	virtual bool SetParameters(FAdvancedNoiseParameterPack& InOutParams) override;
	virtual void SetBandwidth(const float InBandwidth) override;
	virtual void SetScale(const float InScale) override;
	virtual void SetOffset(const float InOffset) override;
	
private:
	virtual bool SetCoefficients() override;

	float ProcessGreenNoiseModulator();
	bool SetParametersGreenNoiseModulator(FAdvancedNoiseParameterPack& InOutParams);
	void SetBandwidthGreenNoiseModulator(const float InBandwidth);
	void SetScaleGreenNoiseModulator(const float InScale);
	void SetOffsetGreenNoiseModulator(const float InOffset);
};