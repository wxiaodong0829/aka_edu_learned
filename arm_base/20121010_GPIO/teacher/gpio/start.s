	AREA init_led,CODE,READONLY
	CODE32
	ENTRY
	IMPORT c_entry
START
	B c_entry
	END