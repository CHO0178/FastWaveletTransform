#include "experiments.h"
#include "stdint.h"

__attribute__((naked))void assemblyDWT(float* data, Wavelet* waveletStruct, uint8_t length, float* result) { //test FPU load and save
__asm(R"(
	PUSH {r4,r5,r6,r7,r8,r9,r10,r11,r12}
breakStructure:
	LDR r5,[r1,#8]
	LDR r4,[r1,#4]
	LDR r1,[r1]
init:
	MOV r9,#0
	MOV r8,#0
	LSL r11,r2,#1
	LSL r1,r1,#2
	SUB r10,r1,#8
	LSL r2,r2,#2
	ADD r2,r2,r10
	CMP r1,#8
	ITE EQ
	MOVEQ r7,#0
	SUBNE r7,r1,#12
	MOV r6,r7
loadValueToFPU:
	ADD r10,r4,r8
	VLDR s0,[r10]
	ADD r10,r5,r8
	VLDR s4,[r10]
	ADD r10,r0,r7
	VLDR s1,[r10]
	VLDR s5,[r10]
MACInstruction:
	VMLA.F32 s2,s1,s0
	VMLA.F32 s6,s5,s4
	ADD r8,#4
checkEndOfWL:
	CMP r8,r1
	BHS saveValue
checkDataEnd:
	AND r10,r6,#4
	CMP r10,#4
	BEQ beforeData
	SUB r10,r11,#4
	CMP r9,r10
	BHI afterData
	ADD r7,r7,#4
	B loadValueToFPU
  beforeData:
	ADD r10,r9,#4
	LSL r10,r10,#1
	SUB r10,r1,r10
	CMP r10,r8
	BEQ loadValueToFPU
	ITE HS
	SUBHS r7,r7,#4
	ADDLO r7,r7,#4
	B loadValueToFPU
  afterData:
	ADD r10,r9,#4
	SUB r10,r10,r11
	LSL r10,r10,#1
	SUB r10,r1,r10
	CMP r10,r8
	BEQ loadValueToFPU
	ITE HS
	ADDHS r7,r7,#4
	SUBLO r7,r7,#4
	B loadValueToFPU
saveValue:
	ADD r10,r3,r9
	VSTR s2,[r10]
	LSR r10,r2,#1
	ADD r10,r10,r3
	ADD r10,r10,r9
	VSTR s6,[r10]
	MOV r10,#0
	VMOV s2,r10
	VMOV s6,r10
checkEndOfProgram:
	LSR r10,r2,#1
	ADD r9,r9,#4
	CMP r9,r10
	BHS finish
incrementAndContinue:
	MOV r8,#0
	CMP r6,#4
	ITT	EQ
	MOVEQ r6,#0
	MOVEQ r7,r6
	BEQ loadValueToFPU
	AND r10,r6,#4
	CMP r10,#4
	ITE EQ
	SUBEQ r6,r6,#8
	ADDNE r6,r6,#8
	MOV r7,r6
	B loadValueToFPU
finish:
	POP {r4,r5,r6,r7,r8,r9,r10,r11,r12}
	BX lr
)");
}
