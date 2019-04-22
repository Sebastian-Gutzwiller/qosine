/*
 * QosineWaveformLister.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: testadmin
 */

#include "QosineWaveformLister.h"

QosineWaveformLister::QosineWaveformLister() {
	// TODO Auto-generated constructor stub
}

QosineWaveformLister::~QosineWaveformLister() {
	// TODO Auto-generated destructor stub
}

uint32_t QosineWaveformLister::GetNumberOfDifferentWaveforms( uint8_t numberOfBitsPerSample, uint16_t numberOfSamples )
{
	if ( ( minimumNumberOfBitsPerSample <= numberOfBitsPerSample ) && ( numberOfBitsPerSample <= maximumNumberOfBitsPerSample )
	  && ( minimumNumberOfSamples <= numberOfSamples ) && ( numberOfSamples <= maximumNumberOfSamples ) )
	{
		// do something
		return 1;
	}
	else
	{
		return 0;
	}
}
