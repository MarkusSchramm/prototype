/**
* @file ProcessorBase.h
 * @brief Defines the base class for DSP processors in the BachelorDSP namespace.
 * 
 * This abstract base class provides a common interface for all DSP processors,
 * including initialization and audio buffer processing methods.
 */

#pragma once

#include "CoreMinimal.h"

namespace BachelorDSP {
	/**
	 * @enum EDSPType
	 * @brief Enum describing the type of DSP processor.
	 * 
	 * Used to identify the DSP unit in runtime logic or diagnostics.
	 */
	enum class EDSPType : uint8 {
		Volume,
		NotchFilter,
	};
	
	/**
	 * @class FProcessorBase
	 * @brief Abstract base class for all DSP processors in the BachelorDSP module.
	 * 
	 * All DSP processors should inherit from this class and implement the Init() and Process() methods.
	 * It also exposes a runtime type identifier via EDSPType.
	 */
	class FProcessorBase {
	public:
		/**
		 * @brief Deleted default constructor.
		 * 
		 * Processors must be initialized with a DSP type.
		 */
		FProcessorBase() = delete;

		/**
		 * @brief Constructs the processor with a specific type.
		 * 
		 * @param Type The DSP type identifier.
		 */
		explicit FProcessorBase(const EDSPType Type);

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~FProcessorBase() = default;
		
		/**
		 * @brief Initializes the processor.
		 * 
		 * Called before audio processing begins. Must be implemented by subclasses.
		 */
		virtual void Init() = 0;

		/**
		 * @brief Processes a block of audio data.
		 * 
		 * @param InBuffer Input audio buffer (read-only).
		 * @param OutBuffer Output audio buffer (write).
		 * @param InNumSamples Number of samples to process.
		 */
		virtual void Process(const float* InBuffer, float* OutBuffer, const int32 InNumSamples) = 0;

		/**
		 * @brief Returns the type of this DSP processor.
		 * 
		 * @return The processor type as EDSPType.
		 */
		EDSPType GetType() const;

	private:
		/** Type identifier for the DSP processor instance. */
		EDSPType Type;
	};
}