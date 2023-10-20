#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include "stdint.h"
#include "waveletMethods.h"


void assemblyFWT(float* data, Wavelet* waveletStruct, uint8_t length, float* result);
void assemblyDWT(float* data, Wavelet* waveletStruct, uint8_t length, float* result);
#endif
