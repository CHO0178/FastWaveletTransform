#include "descreteWaveletTransformation.h"
#include "math.h"
#include "stdlib.h"


static inline int getAddressPosition(const int pos,const unsigned int datal);
int getSizeOfAnswer(const int lengthOfData, const int lengthOfWavelet);


void __attribute__((optimize("O0")))decompositionDWT(float* data, float* waveletAprox, float* waveletDetail, uint8_t lengthOfWavelet, uint8_t lengthOfData, float* processedData)
{
    int a = getSizeOfAnswer(lengthOfData, lengthOfWavelet);
    for (int dataIteration = 0; dataIteration < getSizeOfAnswer(lengthOfData, lengthOfWavelet); dataIteration++)
    {
        processedData[dataIteration] = 0;
        processedData[dataIteration + getSizeOfAnswer(lengthOfData, lengthOfWavelet)] = 0;
        for (uint8_t waveletIteration = 0; waveletIteration < lengthOfWavelet; waveletIteration++)
        {

            processedData[dataIteration] += data[getAddressPosition(2-lengthOfWavelet+2*dataIteration+waveletIteration,lengthOfData)]*waveletAprox[waveletIteration];
            processedData[dataIteration + (lengthOfData/2) + (lengthOfWavelet/2)-1] += data[getAddressPosition(2-lengthOfWavelet+2*dataIteration+waveletIteration,lengthOfData)]*waveletDetail[waveletIteration];
        
        }
    }
}

static inline int getAddressPosition(const int pos,const unsigned int datal)
{
    return abs(((pos/datal) % 2)*(datal-1) - pos%datal);
}

int getSizeOfAnswer(const int lengthOfData, const int lengthOfWavelet)
{
    return (lengthOfData/2)+ (lengthOfWavelet/2)-1;
}
