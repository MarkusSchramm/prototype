/**
 * @file NotchFilter.h
 * @brief Defines a digital notch filter class for real-time audio processing.
 * 
 * Implements a second-order IIR notch filter using the bilinear transform method.
 * Part of the BachelorDSP module and inherits from FProcessorBase.
 */

#pragma once

#include "CoreMinimal.h"
#include "ProcessorBase.h"

namespace BachelorDSP {

	/**
	 * @class FNotchFilter
	 * @brief A simple second-order digital notch filter processor.
	 * 
	 * This class processes input audio samples and attenuates frequencies around a given cutoff frequency.
	 * The filter can be configured via sampling frequency, cutoff frequency, and a bandwidth coefficient.
	 */
	class FNotchFilter : public FProcessorBase
	{
	public:
		/**
		 * @brief Default constructor.
		 * 
		 * Initializes the notch filter with default parameters.
		 */
		FNotchFilter();

		/**
		 * @brief Constructor with filter parameters.
		 * 
		 * @param SamplingFrequency Sampling rate in Hz.
		 * @param CutoffFrequency Frequency to be notched (center frequency).
		 * @param BandwidthCoefficient Width of the notch band.
		 */
		FNotchFilter(const float& SamplingFrequency, const float& CutoffFrequency, const float& BandwidthCoefficient);

		/**
		 * @brief Destructor.
		 */
		virtual ~FNotchFilter() override = default;

		/**
		 * @brief Initializes the internal filter state.
		 */
		virtual void Init() override;

		/**
		 * @brief Processes audio input using the notch filter.
		 * 
		 * @param InBuffer Input audio buffer (read-only).
		 * @param OutBuffer Output buffer with filtered data.
		 * @param InNumSamples Number of samples to process.
		 */
		virtual void Process(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) override;

		/**
		 * @brief Sets the sampling frequency.
		 * 
		 * @param NewSamplingFrequency New sampling rate in Hz.
		 */
		void SetSamplingFrequency(const float& NewSamplingFrequency);

		/**
		 * @brief Sets the cutoff frequency (center frequency to attenuate).
		 * 
		 * @param NewCutoffFrequency Center frequency in Hz.
		 */
		void SetCutoffFrequency(const float& NewCutoffFrequency);

		/**
		 * @brief Sets the bandwidth coefficient (controls notch width).
		 * 
		 * @param NewBandwidthCoefficient Bandwidth value.
		 */
		void SetBandwidthCoefficient(const float& NewBandwidthCoefficient);

		/**
		 * @brief Sets all filter parameters at once.
		 * 
		 * @param NewSamplingFrequency Sampling frequency in Hz.
		 * @param NewCutoffFrequency Cutoff (center) frequency in Hz.
		 * @param NewBandwidthCoefficient Bandwidth coefficient.
		 */
		void SetValues(
			const float& NewSamplingFrequency,
			const float& NewCutoffFrequency,
			const float& NewBandwidthCoefficient
		);

	private:
		/**
		 * @brief Initializes internal filter state and coefficients.
		 */
		void InitNotchFilter();

		/**
		 * @brief Processes audio samples using the configured filter.
		 * 
		 * @param InBuffer Input audio buffer.
		 * @param OutBuffer Output audio buffer.
		 * @param InNumSamples Number of samples.
		 */
		void ProcessNotchFilter(const float* InBuffer, float* OutBuffer, const int32 InNumSamples);

		/**
		 * @brief Calculates filter coefficients based on current parameter values.
		 */
		void SetCoefficients();

		/** Current sampling rate in Hz. */
		float SamplingFrequency;

		/** Center frequency of the notch in Hz. */
		float CutoffFrequency;

		/** Bandwidth coefficient (controls attenuation range around center). */
		float BandwidthCoefficient;

		// Internal filter state variables for recursive calculation
		float Y, Y1, Y2; ///< Current and previous output samples.
		float X, X1, X2; ///< Current and previous input samples.
		float Z;         ///< Intermediate coefficient for normalization.
		float A, A1;     ///< Coefficients for input scaling.
		float B, B1, B2; ///< Coefficients for feedback path.
	};
}