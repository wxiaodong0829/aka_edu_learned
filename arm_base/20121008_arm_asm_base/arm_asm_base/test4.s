	AREA Example,CODE,READONLY ;���������Example
	ENTRY ;��ʶ�������
	CODE32 ;����32λARMָ��
START
	mov r0, #0xffffffff
	ldr r0, =0x12345678;[0xe59f005c]   ldr      r0,0x00008068 ; = #0x12345678
						; e59 ldr
						; f(pc)   rd Ŀ��Ĵ���
						; 0(r0)	  rs Դ�Ĵ���
						; 05c     pc��ƫ��     ldr rd,[rs, #n] n �� rs ��ƫ��,�˴�rs �� pc �Ĵ���
								  ����pc �Ĵ����� Ԥȡ �����룬ִ�� ������ˮ��

	mov r0, #0x12
	ldr r1, =0x00008068
	ldr r0, [r1]
	ldr r0, =0xffff0000
	
	
	MOV R1,#0x10000
	MOV R4,#0x20000
	MOV R2,#0xf0000004
	MOV R3,#0x1200
	MOV R0,#0x1
	STR R0,[R1] ;[R1]<-R0���Ĵ������Ѱַ
	LDR R5,[R1] ;R0<-[R1]���Ĵ������Ѱַ
	ADD R5,R1,#4
	MOV R5,#0x7
	LDR R0,[R1,#4] ;R0<-[R1+4]
	LDR R0, [R1, #-4] ;R0<-[R1-4]�������Դӻ�ַ�ϼ�ȥƫ������Ѱַ
	LDR R0,[R1,#4]! ;R0<-[R1+4], R1<-R1+4��R1�е�ֵ��
	LDR R0,[R1],#4 ;R0<-[R1], R1<-R1+4���۲�R0�е�ֵ��R1��
	LDR R0,[R1,R2] ;R0<-[R1+R2]�������ڷ����ź󸽼ӡ���������д��R1=R1+R2
	STR R2,[R4]
	SWP R0,R1,[R4]
	SWP R0,R0,[R1]
	SWPB R0,R1,[R2] ;��һ��ִ���������Ĳ�����r2�е�8λ��r0�ĵ�8λ��r0�ĸ�24λ��0��r1�ĵ�8λ��r2ָ��ĵ�ַ�ĵ�8λ����r2ָ��ĵ�ַ�ĸ�24λ������0
	SWPB R0,R0,[R1] ;��R1��ָ��Ĵ洢���е��ֽ�������R0�еĵ�8λ���ݽ���
	B START
	END