;
;	EMulator 8080 - to run Altair Basic
;	         Philip Avery July 2012
;	ver 1.3  August 2014 (EMNET3)
;	Changes suggested by George Phillips:
;	mainly - OPTABLE split; msb, lsb
;
; 8080 code must reside at 8000H, but be assembled for
; 0000H - 7FFFH
; Speed: around 10 times slower than Altair
;
;https://github.com/simonowen/apple1emu
;
; Core Intel 8080 Emulator on Z80
;

	CPU		Z80
	ORG		5200H
	include "opdefs.inc"
START	CALL	01C9H		;CLS
	LD	A,0EH
	CALL	33H		;Cursor on
START1 	LD	BC,8000H	;Start of prog, 'PC'
	LD	IX,NXTINS	;Use IX as RET addr

; --Original-------------------------------------------------
;NXTINS	LD	H,.HIGH.OPTABLE	; [7]
;	LD	A,(BC)		; [7] Get opcode from 'PC'
;	LD	L,A		; [4]
;	LD	A,(HL)		; [7] Get MSB of address
;	INC	H		; [4]
;	LD	L,(HL)		; [7] Get LSB of address
;	LD	H,A		; [4]
;	INC	BC		; [6] 'PC' to next byte/instr
;	JP	(HL)		; [4] now Run from start addr
;---------------------------------[50]-----------------------
;	JP	(IX)		  [8] [58]

; --Fast table-----------------------------------------------
;NXTINS	LD	H, OPTABLE>>8 ; [7] look-up table
;	LD	A,(BC)          ; [7] fetch opcode
;	INC	BC              ; [6] PC++
;	LD	L,A             ; [4] LSB is opcode
;	LD	H,(HL)          ; [7] opcode MSB
;	JP	(HL)            ; [4] execute!
; --------------------------------[35]-------------------
;	JP	(IX)		  [8] [43]

; --Fast table and EXX---------------------------------------
	LD	D, OPTABLE>>8	; [7] look-up table
;--------------------------------------------------------
NXTINS	LD	H, D		; [4]
	LD	A,(BC)		; [7] fetch opcode
	INC	BC		; [6] PC++
	LD	L,A		; [4] LSB is opcode
	LD	H,(HL)		; [7] opcode MSB
	JP	(HL)		; [4] execute!
; --------------------------------[32]-------------------
;	JP	(IX)		  [8] [40]
;

HLT1	JP	HLT
UNDOC	DEC	BC
	PUSH	BC
 	LD	HL,UNDOCM	;Print 'UNDOC_._'
UNDOC0	LD	A,(HL)
	OR	A
	JP	Z,UNDOC4
	PUSH	HL
	CALL	33H		;Print char
	POP	HL
	INC	HL
	JP	UNDOC0
UNDOC4	POP	BC		;Hex-Ascii of 'PC'
	LD	A,B
	CALL	UNDOC1
	LD	A,C
	CALL	UNDOC1
	LD	A,'H'
	CALL	33H		;Print char
	JP	402DH		;Exit to DOS
UNDOC1	PUSH	AF		;Get most signif 4 bits
	SRL	A
	SRL	A
	SRL	A
	SRL	A
	CALL 	UNDOC2		;Print in Ascii
	POP	AF		;Get least signif 4 bits
	AND	0FH
	CALL	UNDOC2		;Print in Ascii
	RET
UNDOC2	ADD	A,30H
	CP	3AH
	JP	M,UNDOC3
	ADD	A,7
UNDOC3	PUSH	BC		;Send 0-F to screen
	CALL	33H		;Print char
	POP	BC
	RET
UNDOCM	DB	'UNDOC code at ',0
;			HLT for 8080test (TEST81/CMD)
;			Make active: change HLT1 to HLT

HLT	LD	A,(BC)	; Exit for 8080test
	CP	1	; Next byte: 1 = Error detected
	JP	Z,CPUER
	CP	2	; 2 = CPU ok
	JP	Z,CPUOK
LOOP2	JP	LOOP2

CPUOK	LD	HL,(COUNT)
	XOR	A
	CP	H
	JP	NZ,OK1
	CP	L
	JP	Z,402DH
OK1	DEC	HL
	LD	(COUNT),HL
	LD	HL,0101H
	LD	(84F5H),HL
	LD	(84F7H),HL
	LD	H,02
	LD	(84F9H),HL
	LD	HL,0F385H
	LD	(84FBH),HL
	JP	START1
CPUER	LD	HL,(RSP)
	SET	7,H
	LD	E,(HL)
	INC	HL
	LD	D,(HL)
	DEC	DE
LOOP3	JP	LOOP3

			; Z80/8080 Parity difference
PARITY	PUSH	AF	; Some Z80 instr use parity flag
	EX	AF,AF'	; as overflow, 8080 is all parity
	POP	HL	; Get copy of AF
	LD	A,H
	OR	A
	JP	PO,PODD
	SET	2,L	; Parity Even, set flag
	JP	EXPAR
PODD	RES	2,L	; Parity Odd, turn flag off
EXPAR	PUSH	HL	; Get modified flag back to AF
	EX	AF,AF'
	POP	AF
	RET
			; PARINR Parity INR & DCR
			; Gets A from (HL)
PARINR	PUSH	AF	; Save A'
	PUSH	AF	; Save flags'
	PUSH	HL	; Save HL'
	EX	AF,AF'
	POP	HL
	LD	A,(HL)	; Got (HL)'
	POP	HL	; Get flags'
	OR	A
	JP	PO,PARI1
	SET	2,L
	JP	PARIEX
PARI1 	RES	2,L
PARIEX	POP	DE	; Get A'
	LD	H,D
	PUSH	HL	; Save with new flags
	EX	AF,AF'
	POP	AF
	RET

JNZ1	EX	AF,AF'
	LD	A,(BC)
	LD	L,A
	INC	BC
	LD	A,(BC)
	LD	H,A
	SET	7,H
	LD	B,H
	LD	C,L
	JP	(IX)

RZ1	EX	AF,AF'		;Not zero, so do RETURN
	LD	HL,(RSP)
	SET	7,H
	LD	E,(HL)		;Get contents of em_ SP
	INC	HL		;from emulated stack
	LD	D,(HL)		;DE now has RET addr
	INC	HL
	RES	7,H
	LD	(RSP),HL
	SET	7,D
	LD	B,D
	LD	C,E
	JP	(IX)

CNZ1	EX	AF,AF'
	LD	A,(BC)
	LD	E,A		;DE gets Call address
	INC	BC
	LD	A,(BC)
	LD	D,A
	SET	7,D
	INC	BC
	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B		;Push CALL's ret addr
	DEC	HL		;onto emulated stack
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	B,D
	LD	C,E
	JP	(IX)

;Registers
RC	DB	0
RB	DB	0
RE	DB	0
RD	DB	0
RL	DB	0
RH	DB	0
RSP	DW	07FFFH
COUNT	DW	0064H	; Count for 8080test repeats
KEY	DB	0	; Key buffer
SAVLOD	DB	0	; Set FF Save, 00 nothing 01 Load
SLADD	DW	0C000H	; Save/Load start address
SLFIN	DW	1111H	; Save/Load finish address
;

	ORG	5400H	;Optable must start at 256 bound.
OPTABLE	DB	OP_00>>8, OP_01>>8, OP_02>>8, OP_03>>8, OP_04>>8, OP_05>>8, OP_06>>8, OP_07>>8
	DB	OP_08>>8, OP_09>>8, OP_0A>>8, OP_0B>>8, OP_0C>>8, OP_0D>>8, OP_0E>>8, OP_0F>>8
	DB	OP_10>>8, OP_11>>8, OP_12>>8, OP_13>>8, OP_14>>8, OP_15>>8, OP_16>>8, OP_17>>8
	DB	OP_18>>8, OP_19>>8, OP_1A>>8, OP_1B>>8, OP_1C>>8, OP_1D>>8, OP_1E>>8, OP_1F>>8
	DB	OP_20>>8, OP_21>>8, OP_22>>8, OP_23>>8, OP_24>>8, OP_25>>8, OP_26>>8, OP_27>>8
	DB	OP_28>>8, OP_29>>8, OP_2A>>8, OP_2B>>8, OP_2C>>8, OP_2D>>8, OP_2E>>8, OP_2F>>8
	DB	OP_30>>8, OP_31>>8, OP_32>>8, OP_33>>8, OP_34>>8, OP_35>>8, OP_36>>8, OP_37>>8
	DB	OP_38>>8, OP_39>>8, OP_3A>>8, OP_3B>>8, OP_3C>>8, OP_3D>>8, OP_3E>>8, OP_3F>>8
	DB	OP_40>>8, OP_41>>8, OP_42>>8, OP_43>>8, OP_44>>8, OP_45>>8, OP_46>>8, OP_47>>8
	DB	OP_48>>8, OP_49>>8, OP_4A>>8, OP_4B>>8, OP_4C>>8, OP_4D>>8, OP_4E>>8, OP_4F>>8
	DB	OP_50>>8, OP_51>>8, OP_52>>8, OP_53>>8, OP_54>>8, OP_55>>8, OP_56>>8, OP_57>>8
	DB	OP_58>>8, OP_59>>8, OP_5A>>8, OP_5B>>8, OP_5C>>8, OP_5D>>8, OP_5E>>8, OP_5F>>8
	DB	OP_60>>8, OP_61>>8, OP_62>>8, OP_63>>8, OP_64>>8, OP_65>>8, OP_66>>8, OP_67>>8
	DB	OP_68>>8, OP_69>>8, OP_6A>>8, OP_6B>>8, OP_6C>>8, OP_6D>>8, OP_6E>>8, OP_6F>>8
	DB	OP_70>>8, OP_71>>8, OP_72>>8, OP_73>>8, OP_74>>8, OP_75>>8, OP_76>>8, OP_77>>8
	DB	OP_78>>8, OP_79>>8, OP_7A>>8, OP_7B>>8, OP_7C>>8, OP_7D>>8, OP_7E>>8, OP_7F>>8
	DB	OP_80>>8, OP_81>>8, OP_82>>8, OP_83>>8, OP_84>>8, OP_85>>8, OP_86>>8, OP_87>>8
	DB	OP_88>>8, OP_89>>8, OP_8A>>8, OP_8B>>8, OP_8C>>8, OP_8D>>8, OP_8E>>8, OP_8F>>8
	DB	OP_90>>8, OP_91>>8, OP_92>>8, OP_93>>8, OP_94>>8, OP_95>>8, OP_96>>8, OP_97>>8
	DB	OP_98>>8, OP_99>>8, OP_9A>>8, OP_9B>>8, OP_9C>>8, OP_9D>>8, OP_9E>>8, OP_9F>>8
	DB	OP_A0>>8, OP_A1>>8, OP_A2>>8, OP_A3>>8, OP_A4>>8, OP_A5>>8, OP_A6>>8, OP_A7>>8
	DB	OP_A8>>8, OP_A9>>8, OP_AA>>8, OP_AB>>8, OP_AC>>8, OP_AD>>8, OP_AE>>8, OP_AF>>8
	DB	OP_B0>>8, OP_B1>>8, OP_B2>>8, OP_B3>>8, OP_B4>>8, OP_B5>>8, OP_B6>>8, OP_B7>>8
	DB	OP_B8>>8, OP_B9>>8, OP_BA>>8, OP_BB>>8, OP_BC>>8, OP_BD>>8, OP_BE>>8, OP_BF>>8
	DB	OP_C0>>8, OP_C1>>8, OP_C2>>8, OP_C3>>8, OP_C4>>8, OP_C5>>8, OP_C6>>8, OP_C7>>8
	DB	OP_C8>>8, OP_C9>>8, OP_CA>>8, OP_CB>>8, OP_CC>>8, OP_CD>>8, OP_CE>>8, OP_CF>>8
	DB	OP_D0>>8, OP_D1>>8, OP_D2>>8, OP_D3>>8, OP_D4>>8, OP_D5>>8, OP_D6>>8, OP_D7>>8
	DB	OP_D8>>8, OP_D9>>8, OP_DA>>8, OP_DB>>8, OP_DC>>8, OP_DD>>8, OP_DE>>8, OP_DF>>8
	DB	OP_E0>>8, OP_E1>>8, OP_E2>>8, OP_E3>>8, OP_E4>>8, OP_E5>>8, OP_E6>>8, OP_E7>>8
	DB	OP_E8>>8, OP_E9>>8, OP_EA>>8, OP_EB>>8, OP_EC>>8, OP_ED>>8, OP_EE>>8, OP_EF>>8
	DB	OP_F0>>8, OP_F1>>8, OP_F2>>8, OP_F3>>8, OP_F4>>8, OP_F5>>8, OP_F6>>8, OP_F7>>8
	DB	OP_F8>>8, OP_F9>>8, OP_FA>>8, OP_FB>>8, OP_FC>>8, OP_FD>>8, OP_FE>>8, OP_FF>>8


		INCLUDE	"opimpl.inc"
