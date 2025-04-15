/**
 * @file ProcessorBase.cpp
 * @brief processor implementation for BachelorDSP.
 */

#include "DSP/ProcessorBase.h"

BachelorDSP::FProcessorBase::FProcessorBase(const EDSPType Type)
	: Type(Type) {}

BachelorDSP::EDSPType BachelorDSP::FProcessorBase::GetType() const {
	return this->Type;
}
