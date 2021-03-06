/***************************************************************************
 *   Copyright (C) 1998-2009 by David Bucciarelli (davibu@interfree.it)    *
 *                                                                         *
 *   This file is part of SmallLuxGPU.                                     *
 *                                                                         *
 *   SmallLuxGPU is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *  SmallLuxGPU is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *   This project is based on PBRT ; see http://www.pbrt.org               *
 *   and Lux Renderer website : http://www.luxrender.net                   *
 ***************************************************************************/

#ifndef _SAMPLEBUFFER_H
#define	_SAMPLEBUFFER_H

#include "core/spectrum.h"
#include "sampler.h"

#define SAMPLE_BUFFER_SIZE (4096)

typedef struct {
	float screenX, screenY;
	unsigned int pass;
	Spectrum radiance;
} SampleBufferElem;

class SampleBuffer {
public:
	SampleBuffer(size_t bufferSize) : size(bufferSize) {
		samples = new SampleBufferElem[size];
		Reset();
	}
	~SampleBuffer() {
		delete samples;
	}

	void Reset() { currentFreeSample = 0; };
	bool IsFull() const { return (currentFreeSample >= size); }

	void SplatSample(const Sample *sample, const Spectrum &radiance) {
		SampleBufferElem *s = &samples[currentFreeSample++];

		s->screenX = sample->screenX;
		s->screenY = sample->screenY;
		s->pass = sample->pass;
		s->radiance = radiance;
	}

	SampleBufferElem *GetSampleBuffer() const { return samples; }

	size_t GetSampleCount() const { return currentFreeSample; }

private:
	size_t size;
	size_t currentFreeSample;

	SampleBufferElem *samples;
};

#endif	/* _SAMPLEBUFFER_H */
