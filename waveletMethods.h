#ifndef WAVELET_METHOD_H
#define WAVELET_METHOD_H

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif

#define BIGEST_PROCESSED_DATA 64

typedef struct Wavelet{
    unsigned int length;
    float* aprox;
    float* detail;
}Wavelet;


static uint8_t waveletHaarLength = 2;
static float waveletHaarAprox[BIGEST_PROCESSED_DATA] =  {0.70710678118654752440084436210485,0.707106781186547524400844362104850};   //[2 ... 31] = 0   // 1/sqrt(2)
static float waveletHaarDetail[BIGEST_PROCESSED_DATA] = {0.70710678118654752440084436210485,-0.707106781186547524400844362104850};  

static Wavelet waveletHaar = {.length = 2,.aprox = waveletHaarAprox, .detail = waveletHaarDetail};


static uint8_t waveletdb2Length = 4;
static float waveletdb2Aprox[BIGEST_PROCESSED_DATA] =  {0.4829629131, 0.8365163037, 0.2241438680, -0.1294095226};
static float waveletdb2Detail[BIGEST_PROCESSED_DATA] = {-0.1294095226, -0.2241438680, 0.8365163037, -0.4829629131};

static Wavelet waveletdb2 = {.length = 4,.aprox = waveletdb2Aprox, .detail = waveletdb2Detail};


static uint8_t waveletdb4Length = 8;
static float waveletdb4Aprox[BIGEST_PROCESSED_DATA] =  {0.2303778133, 0.7148465706, 0.6308807679, -0.0279837694, -0.1870348117, 0.0308413818, 0.0328830117, -0.0105974018};
static float waveletdb4Detail[BIGEST_PROCESSED_DATA] = {-0.0105974018, -0.0328830117, 0.0308413818, 0.1870348117, -0.0279837694, -0.6308807679, 0.7148465706, -0.2303778133};

static Wavelet waveletdb4 = {.length = 8,.aprox = waveletdb4Aprox, .detail = waveletdb4Detail};


static uint8_t waveletsym2Length = 4;
static float waveletsym2Aprox[BIGEST_PROCESSED_DATA] =  {0.4829629131, 0.8365163037, 0.2241438680, -0.1294095226};
static float waveletsym2Detail[BIGEST_PROCESSED_DATA] = {-0.1294095226, -0.2241438680, 0.8365163037, -0.4829629131};

static Wavelet waveletsym2 = {.length = 4,.aprox = waveletsym2Aprox, .detail = waveletsym2Detail};


static uint8_t waveletsym4Length = 8;
static float waveletsym4Aprox[BIGEST_PROCESSED_DATA] =  {0.0322231006, -0.0126039673, -0.0992195436, 0.2978577956, 0.8037387518, 0.4976186676, -0.0296355276, -0.0757657148};
static float waveletsym4Detail[BIGEST_PROCESSED_DATA] = {-0.0757657148, 0.0296355276, 0.4976186676, -0.8037387518, 0.2978577956, 0.0992195436, -0.0126039673, -0.0322231006};

static Wavelet waveletsym4 = {.length = 8,.aprox = waveletsym4Aprox, .detail = waveletsym4Detail};


static uint8_t waveletcoif1Length = 6;
static float waveletcoif1Aprox[BIGEST_PROCESSED_DATA] =  {-0.0727326195, 0.3378976625, 0.8525720202, 0.3848648469, -0.0727326195, -0.0156557281};
static float waveletcoif1Detail[BIGEST_PROCESSED_DATA] = {-0.0156557281, 0.0727326195, 0.3848648469, -0.8525720202, 0.3378976625, 0.0727326195};

static Wavelet waveletcoif1 = {.length = 6,.aprox = waveletcoif1Aprox, .detail = waveletcoif1Detail};


void waveletCompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData);
void waveletCompressOptimised(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData);
void waveletLossyCompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData);
void waveletDecompress2(float* aproxMatrix,float* detailMatrix, float* waveletAprox, float* waveletDetail, uint8_t lengthOfData, float* processedData);
void waveletDecompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfData, float* processedData);



#ifdef __cplusplus
} // extern "C"
#endif

#endif
