#include "experiments.h"
#include "stdint.h"

__attribute__((naked))void assemblyFWT(float* data, Wavelet* waveletStruct, uint8_t length, float* result) { //test FPU load and save
__asm(R"(
	PUSH {r4,r5,r6,r7,r8,r9,r10,r11,r12}
breakStructure:
	LDR r5,[r1,#8]
	LDR r4,[r1,#4]
	LDR r1,[r1]
init:
	MOV r6,#0
	MOV r9,#0
	MOV r8,#0
	MOV r7,#0
	MOV r12,#0
	LSL r1,r1,#2
	LSL r2,r2,#2
	LSR r10,r2,#1
	ADD r11,r10,r0
loadValueToFPU:
	ADD r10,r4,r8
	VLDR s0,[r10]
	ADD r10,r0,r7
	VLDR s1,[r10]
	ADD r10,r5,r8
	VLDR s4,[r10]
	ADD r10,r0,r7
	VLDR s5,[r10]
MACInstruction:
	VMLA.F32 s2,s1,s0
	VMLA.F32 s6,s5,s4
	ADD r8,#4
checkEndOfWL:
	CMP r8,r1
	BHS saveValue
checkDataEnd:
	CMP r7,r2
	ITE EQ
	MOVEQ r7,#0
	ADDNE r7,#4
	CMP r12,r2
	ITE EQ
	MOVEQ r12,#0
	ADDNE r12,#4
	B loadValueToFPU
saveValue:
	ADD r10,r3,r9
	VSTR s2,[r10]
	LSR r10,r2,#1
	ADD r10,r10,r9
	ADD r10,r3
	VSTR s6,[r10]
	MOV r10,#0
	VMOV s2,r10
	VMOV s6,r10
	ADD r6,#8
checkEndOfProgram:
	LSR r10,r2,#1
	ADD r9,r9,#4
	CMP r9,r10
	BHS finish
incrementAndContinue:
	MOV r8,#0
	LSL r7,r9,#1
	LSL r12,r9,#1
	CMP r12,r2
	IT HS
	SUBHS r12,r12,r2
	B loadValueToFPU
finish:
	POP {r4,r5,r6,r7,r8,r9,r10,r11,r12}
	BX lr
)");
}
