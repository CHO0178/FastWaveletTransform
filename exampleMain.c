#include <stdint.h>
#include "experiments.h"
#include "waveletMethods.h"
#include "descreteWaveletTransformation.h"

#define SIZE_OF_MESSAGE 	32u
#define USED_WL_APROX  		waveletdb2Aprox
#define USED_WL_DETAIL 		waveletdb2Detail
#define USED_WL_LENGTH 		waveletdb2Length
#define USED_STRUCT 		&waveletdb2

int exampleMain(void) {



	float dataArray[SIZE_OF_MESSAGE];
	uint8_t encriptedMessage[SIZE_OF_MESSAGE*2*sizeof(float)*2+2] = {0};
	//uint8_t decriptedMessage[SIZE_OF_MESSAGE*sizeof(float)];
	float processedData[SIZE_OF_MESSAGE*2] = {0};

	// get data from PC

	//receiveArray(encriptedMessage, SIZE_OF_MESSAGE, sizeof(float));  //looping until receive data from PC
	//uint8_t receivedMsgSize = decodeMessageRFC1662(encriptedMessage, (uint8_t*)dataArray, SIZE_OF_MESSAGE*2*sizeof(float)+2)/4;

	// benchmark 100'000 itenations of experimental function
	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyFWT(dataArray,USED_STRUCT,8,processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break

	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyFWT(dataArray,USED_STRUCT,16,processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break

	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyFWT(dataArray,USED_STRUCT,32,processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break

	startBenchmark();
	for(int i = 0; i<100000;i++){waveletCompressOptimised(dataArray, USED_WL_APROX, USED_WL_DETAIL, USED_WL_LENGTH, 32/*receivedMsgSize*/, processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break

	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyDWT(dataArray,USED_STRUCT,8,processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break
	
	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyDWT(dataArray,USED_STRUCT,16,processedData);}
	stopBenchmark();

	for(unsigned long i = 0; i<10000000;i++){__asm volatile ("nop");} //break

	startBenchmark();
	for(int i = 0; i<100000;i++){assemblyDWT(dataArray,USED_STRUCT,32,processedData);}
	stopBenchmark();
    return 0 ;
}
