#include "waveletMethods.h"


void waveletCompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData)
{
    for (uint8_t dataIteration = 0; dataIteration < lengthOfData/2; dataIteration++)
    {
        processedData[dataIteration] = 0;
        processedData[dataIteration + (lengthOfData/2)] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfWavelet; waveletIteration++)
        {
            processedData[dataIteration] += data[(2*dataIteration + waveletIteration)%lengthOfData]*waveletAprox[waveletIteration];
            processedData[dataIteration + (lengthOfData/2)] += data[(2*dataIteration + waveletIteration)%lengthOfData]*waveletDetail[waveletIteration];
        }
    }
}

void __attribute__((optimize("O2"))) waveletCompressOptimised(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData)
{
    for (uint8_t dataIteration = 0; dataIteration < lengthOfData/2; dataIteration++)
    {
        processedData[dataIteration] = 0;
        processedData[dataIteration + (lengthOfData/2)] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfWavelet; waveletIteration++)
        {
            processedData[dataIteration] += data[(2*dataIteration + waveletIteration)%lengthOfData]*waveletAprox[waveletIteration];
            processedData[dataIteration + (lengthOfData/2)] += data[(2*dataIteration + waveletIteration)%lengthOfData]*waveletDetail[waveletIteration];
        }
    }
}


void waveletLossyCompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData)
{
    for (uint8_t dataIteration = 0; dataIteration < lengthOfData/2; dataIteration++)
    {
        processedData[dataIteration] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfWavelet; waveletIteration++)
        {
            processedData[dataIteration] += data[(2*dataIteration + waveletIteration)%lengthOfData]*waveletAprox[waveletIteration];
        }
    }
}

void waveletDecompress2(float* aproxMatrix,float* detailMatrix, float* waveletAprox, float* waveletDetail, uint8_t lengthOfData, float* processedData)
{
    for (uint8_t dataIteration = 0; dataIteration < lengthOfData; dataIteration++)
    {
        processedData[dataIteration] = 0;
        processedData[dataIteration + (lengthOfData)] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfData; waveletIteration++)
        {
            uint8_t index1 = (2*(lengthOfData - waveletIteration) + dataIteration) % (lengthOfData*2);
            uint8_t index2 = ((3*lengthOfData - 2*waveletIteration + dataIteration) % (lengthOfData*2));
            processedData[dataIteration] += aproxMatrix[waveletIteration]*waveletAprox[(2*(lengthOfData - waveletIteration) + dataIteration) % (lengthOfData*2)];
            processedData[dataIteration] += aproxMatrix[waveletIteration]*waveletAprox[(2*(lengthOfData - waveletIteration) + dataIteration) % (lengthOfData*2)];
            processedData[dataIteration + lengthOfData] += detailMatrix[waveletIteration]*waveletDetail[((3*lengthOfData - 2*waveletIteration + dataIteration) % (lengthOfData*2))];
            processedData[dataIteration + lengthOfData] += detailMatrix[waveletIteration]*waveletDetail[((3*lengthOfData - 2*waveletIteration + dataIteration) % (lengthOfData*2))];
        }
    }
}

void waveletDecompress(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfData, float* processedData)
{
    for (uint8_t dataIteration = 0; dataIteration < lengthOfData; dataIteration++)
    {
        processedData[dataIteration] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfData>>1; waveletIteration++)
        {
            processedData[dataIteration] += data[waveletIteration]*waveletAprox[((lengthOfData - 2*waveletIteration + dataIteration) % lengthOfData)] + 
                                            data[waveletIteration + (lengthOfData >> 1)] * waveletDetail[((lengthOfData - 2*waveletIteration + dataIteration) % lengthOfData)];
        }
    }
}
