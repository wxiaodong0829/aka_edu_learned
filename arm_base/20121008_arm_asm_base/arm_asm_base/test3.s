	; �� �� λ��0 ���
	
	
	
	AREA Example,CODE,READONLY ;���������Example
	ENTRY ;��ʶ�������
	CODE32 ;����32λARMָ��
START

	mov r1, #0xffffffff

	MOV R0,#0x02
	AND R0,R0,#0x01 ;R0=R0&0x01 ȡ�����λ����
	MOV R1,#0x0f7
	MOV R3,#0x05
	AND R2,R1,R3 ;R2=R1&R3
	MOV R0,#0x0c1
	ORR R0,R0,#0x0F ;��R0�ĵ�4λ��1
	EOR R1,R1,#0x0F ;��R1�ĵ�4λȡ��
	EOR R2,R1,R0 ;R2 = R1 ^ R0
	BIC R1,R1,#0x0F ;��R1�ĵ�4λ��0������λ���ֲ���
	BIC R1,R2,R3 ;�����ʲô�����أ���r2�� r3��Ӧ�ı���1��λ��0֮�󸳸�r1
	B START
	
	END