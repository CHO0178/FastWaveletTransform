#ifndef DESCRETE_WAVELET_TRANSFORMATION_H
#define DESCRETE_WAVELET_TRANSFORMATION_H   

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif

void decompositionDWT(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
