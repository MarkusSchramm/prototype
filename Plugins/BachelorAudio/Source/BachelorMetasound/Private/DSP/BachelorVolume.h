/**
 * @file BachelorVolume.h
 * @brief Volume processor implementation for BachelorDSP.
 * 
 * Defines a simple amplitude-based gain processor that inherits from FProcessorBase.
 * Provides basic linear gain control for real-time audio buffers.
 */

#pragma once

#include "CoreMinimal.h"
#include "ProcessorBase.h"

namespace BachelorDSP {

	/**
	 * @class FBachelorVolume
	 * @brief Simple volume/gain processor for real-time audio processing.
	 * 
	 * This class scales incoming audio data by a linear gain factor (amplitude).
	 * It is designed to be used within a modular DSP framework and implements the FProcessorBase interface.
	 */
	class FBachelorVolume : public FProcessorBase {
	public:
		/**
		 * @brief Default constructor.
		 * 
		 * Initializes the processor with default amplitude = 1.0 (unity gain).
		 */
		FBachelorVolume();

		/**
		 * @brief Constructor with initial gain value.
		 * 
		 * @param DefaultAmplitude The linear amplitude (gain) value to apply during processing.
		 */
		explicit FBachelorVolume(const float DefaultAmplitude);

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~FBachelorVolume() override = default;

		/**
		 * @brief Initializes the processor state.
		 * 
		 * Should be called before the first call to Process().
		 */
		virtual void Init() override;

		/**
		 * @brief Processes an audio buffer and applies volume scaling.
		 * 
		 * @param InBuffer Input audio buffer (read-only).
		 * @param OutBuffer Output audio buffer (write).
		 * @param InNumSamples Number of audio samples to process.
		 */
		virtual void Process(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) override;

		/**
		 * @brief Sets a new amplitude (gain) value.
		 * 
		 * @param NewAmplitude The gain multiplier (e.g., 0.5 = -6dB, 2.0 = +6dB).
		 */
		void SetAmplitude(const float NewAmplitude);

	private:
		/**
		 * @brief Internal initialization logic for volume settings.
		 * 
		 * Called during Init(), can be extended for runtime parameter smoothing or safety checks.
		 */
		void InitVolume();

		/**
		 * @brief Applies gain to the input buffer and writes result to output.
		 * 
		 * @param InBuffer Input buffer of float samples.
		 * @param OutBuffer Output buffer to receive the scaled samples.
		 * @param InNumSamples Number of samples to process.
		 */
		void ProcessVolumeBuffer(const float* InBuffer, float* OutBuffer, const int32 InNumSamples);

		/** Linear gain multiplier applied during audio processing. */
		float Amplitude;
	};

}