/*
* Copyright (c) 2002 By Richard Kiss
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify,
* merge, publish, distribute, sublicense, and or sell copies of
* the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*
*/

#ifndef __audiopipeout_h__
#define __audiopipeout_h__

#include "threadedqueue.h"
#include "resampler.h"

typedef struct {
  threadedqueue tq;
  Resampler *resampler;
  unsigned channelCount;
  float sampleRateInHZ;
  unsigned byteCountAfterWhichToStart;
  unsigned bufferSizeInBytes;
  float startAfterTime;
  unsigned bytesPerSample;
  unsigned readByteCount;
  unsigned sampleRepeatCount;
} audiopipeout;

/* Larger buffers reduces dropout probability. */
void init_audiopipeout(audiopipeout *ap, float rate, int isMono, int frameBufferSize);

void write_s8_samples(audiopipeout *ap, char samples[], unsigned frameCount);
void write_u8_samples(audiopipeout *ap, unsigned char samples[], unsigned frameCount);
void write_s16_samples(audiopipeout *ap, short samples[], unsigned frameCount);
void write_u16_samples(audiopipeout *ap, unsigned short samples[], unsigned frameCount);
void write_s32_samples(audiopipeout *ap, long samples[], unsigned frameCount);
void write_u32_samples(audiopipeout *ap, unsigned long samples[], unsigned frameCount);
void write_float_samples(audiopipeout *ap, float samples[], unsigned frameCount);

/* utilities */
void swap_16_samples(short samples[], unsigned frameCount);
void swap_32_samples(long samples[], unsigned frameCount);

void wait_until_done(audiopipeout *ap);

void destroy_audiopipeout(audiopipeout *ap);

#endif /* __audiopipeout_h__ */