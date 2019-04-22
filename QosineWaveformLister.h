/*
 * QosineWaveformLister.h
 *
 *  Created on: Apr 22, 2019
 *      Author: testadmin
 */

#ifndef QOSINEWAVEFORMLISTER_H_
#define QOSINEWAVEFORMLISTER_H_

#include <cstdint>

class QosineWaveformLister {
public:
	QosineWaveformLister();
	virtual ~QosineWaveformLister();
	uint32_t GetNumberOfDifferentWaveforms( uint8_t numberOfBitsPerSample, uint16_t numberOfSamples );
private:
	const uint8_t minimumNumberOfBitsPerSample = 2;
	const uint8_t maximumNumberOfBitsPerSample = 24;
	const uint16_t minimumNumberOfSamples = 4;
	const uint16_t maximumNumberOfSamples = 255;
};
#endif /* QOSINEWAVEFORMLISTER_H_ */

