	AREA Example,CODE,READONLY ;���������Example

	CODE32 ;����32λARMָ��
	ENTRY ;��ʶ�������
	
START
	
	MOV R1, #3
	MOV R2, #5
	
	ADD R0, R1, R2 ; R0 = R1 + R2
	ADD R0, R1, #2 ; R0 = R1 + 2
	ADD R0, R2, R1,LSL#1 ; R0 = R2 + (R1 << 1)
	
	MOV R1, #0xf1000000
	MOV R2, #0x80000000
	
	ADD R0, R1, R2 ; R0 = R1 + R2 �鿴CPSR�Ĵ����е�Cλ�Ƿ�仯
	ADDS R3, R1, R2 ; �鿴CPSR�Ĵ����е�Cλ�Ƿ�仯
	ADD R5, R1, R2 ; ָ����û��S����ӽ�����ı�CPSR����ر�־λ
	
	ADC R6, R1, R2 ; ����λ�ӷ���R6=R1+R2+��CPSR��C��־λ��ֵ��
	ADDS R5, R1, R2 ; ָ���м�S����ӽ���ı�CPSR����ر�־λ
	ADC R6, R1, R2 ; ����λ�ӷ���R6=R1+R2+��CPSR��C��־λ��ֵ��
	MOV R4, #0x5fffffff
	MOV R5, #0x6e
	MOV R6, #0x6fffffff
	MOV R7, #0x9
	MOV R8, #0xcfffffff
	MOV R9, #0x1
	MOV R10, #0xbfffffff
	MOV R11, #0x9
	ADDS R0, R4, R8 ; �ӵͶ˵���
	ADCS R1, R5, R9 ; ����һ���֣�����λ
	ADCS R2, R6, R10 ; �ӵ������֣�����λ
	ADCS R3, R7, R11 ; �Ӹ߶˵��֣�����λ
	SUB R0, R2, R1 ; R0 = R2 �C R1
	SUB R0, R1, #2 ; R0 = R1 - 2
	SUB R0, R2, R3,LSL#1 ; R0 = R2 - (R3 << 1)
	RSB R0, R1, R2 ; R0 = R2 - R1
	RSB R0, R1, #256 ; R0 = 256 - R1
	RSB R0, R1, R3,LSL#1 ; R0 = (R3 << 1) �C R1
	MOV R1, #3
	MOV R2, #5
	MUL R3, R1, R2
	B START
	
	
	
	END