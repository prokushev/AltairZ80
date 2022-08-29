;
;Emulated undocumented opcodes
;
;08h, 10h, 18h, 20h, 28h, 30h, 38h - NOP
;0CBh - JMP
;0D9h - RET
;0DDh, 0EDh, 0FDh - CALL


				ORG		OP_00
NOP				JP	(IX)
OP_00_LEN:		EQU		$-OP_00

				ORG		OP_01
LXI_B			
;---------------------------------
;				LD	A,(BC)		;[7]
;				LD	L,A			;[4]
;				INC	BC			;[6]
;				LD	A,(BC)		;[7]
;				LD	H,A			;[4]
;				INC	BC			;[6]
;				LD	(RC),HL		;[16]
;---------------------------------
				LD	A,(BC)		;[7]
				EXX				;[4]
				LD	C,A			;[4]
				EXX				;[4]
				INC	BC			;[6]
				LD	A,(BC)		;[7]
				EXX				;[4]
				LD	B,A			;[4]
				EXX				;[4]
				INC	BC			;[5]
;-------------------------------[same]
				JP	(IX)
OP_01_LEN:		EQU		$-OP_01

				ORG		OP_02
STAX_B
;				EX	AF,AF'
;				LD	HL,(RC)		;[16]
;				SET	7,H
;				LD	(HL),A
;				EX	AF,AF'
;---------------------------------------
				EXX				;[4]
				SET 7, B
				EX	AF,AF'
				LD	(BC), A
				EX	AF,AF'
				RES 7, B		;[8]
				EXX				;[4]
;-------------------------------[same]
				JP	(IX)
OP_02_LEN:		EQU		$-OP_02

				ORG		OP_03
INX_B
;				LD	HL,(RC)		; [16]
;				INC	HL
;				LD	(RC),HL		; [16]
;------------------------------------
				EXX				; [4]
				INC	BC
				EXX				; [4]
;-------------------------------[-24]
				JP	(IX)
OP_03_LEN:		EQU		$-OP_03

				ORG		OP_04
INR_B
;				EX	AF,AF'
;				LD	HL,RB		;[10]
;				INC	(HL)		;[11]
;				CALL	PARINR
;				EX	AF,AF'
				EXX				;[4]
				EX	AF,AF'
				INC		B		;[4]
				CALL	PARINR
				EX	AF,AF'
				EXX				;[4]
				JP	(IX)
;--------------------------------[-9]
OP_04_LEN:		EQU		$-OP_04

				ORG		OP_05
DCR_B
;				EX	AF,AF'
;				LD	HL,RB		;[10]
;				DEC	(HL)		;[11]
;				CALL	PARINR
;				EX	AF,AF'
				EXX				;[4]
				EX	AF,AF'
				DEC	B			;[4]
				CALL	PARINR
				EX	AF,AF'
				EXX				;[4]
;--------------------------------[-9]
				JP	(IX)
OP_05_LEN:		EQU		$-OP_05

				ORG		OP_06
MVI_B
;				LD	A,(BC)
;				LD	(RB),A		; [13]
;				INC	BC
				LD	A, (BC)
				EXX				; [4]
				LD	B, A		; [4]
				EXX				; [4]
				INC	BC
;--------------------------------[-1]
				JP	(IX)
OP_06_LEN:		EQU		$-OP_06

				ORG		OP_07
RLC				EX	AF,AF'
				RLCA
				EX	AF,AF'
;--------------------------------[same]
				JP	(IX)
OP_07_LEN:		EQU		$-OP_07

				ORG		OP_08
;--------------------------------[same]
				JP	(IX)
OP_08_LEN:		EQU		$-OP_08

				ORG		OP_09
DAD_B			EX	AF,AF'
				LD	DE,(RC)
				LD	HL,(RL)
				ADD	HL,DE
				LD	(RL),HL
				EX	AF,AF'
				JP	(IX)
OP_09_LEN:		EQU		$-OP_09

				ORG		OP_0A
LDAX_B			EX	AF,AF'
				LD	HL,(RC)
				SET	7,H
				LD	A,(HL)
				EX	AF,AF'
				JP	(IX)
OP_0A_LEN:		EQU		$-OP_0A

				ORG		OP_0B
DCX_B			LD	HL,(RC)
				DEC	HL
				LD	(RC),HL
				JP	(IX)
OP_0B_LEN:		EQU		$-OP_0B

				ORG		OP_0C
INR_C			EX	AF,AF'
				LD	HL,RC
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_0C_LEN:		EQU		$-OP_0C

				ORG		OP_0D
DCR_C			EX	AF,AF'
				LD	HL,RC
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_0D_LEN:		EQU		$-OP_0D

				ORG		OP_0E
MVI_C			LD	A,(BC)
				LD	(RC),A
				INC	BC
				JP	(IX)
OP_0E_LEN:		EQU		$-OP_0E

				ORG		OP_0F
RRC				EX	AF,AF'
				RRCA
				EX	AF,AF'
				JP	(IX)
OP_0F_LEN:		EQU		$-OP_0F

				ORG		OP_10
				JP	(IX)
OP_10_LEN:		EQU		$-OP_10

				ORG		OP_11
LXI_D			LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				LD	(RE),HL
				JP	(IX)
OP_11_LEN:		EQU		$-OP_11

				ORG		OP_12
STAX_D			EX	AF,AF'
				LD	HL,(RE)
				SET	7,H
				LD	(HL),A
				EX	AF,AF'
				JP	(IX)
OP_12_LEN:		EQU		$-OP_12

				ORG		OP_13
INX_D			LD	HL,(RE)
				INC	HL
				LD	(RE),HL
				JP	(IX)
OP_13_LEN:		EQU		$-OP_13

				ORG		OP_14
INR_D			EX	AF,AF'
				LD	HL,RD
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_14_LEN:		EQU		$-OP_14

				ORG		OP_15
DCR_D			EX	AF,AF'
				LD	HL,RD
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_15_LEN:		EQU		$-OP_15

				ORG		OP_16
MVI_D			LD	A,(BC)
				LD	(RD),A
				INC	BC
				JP	(IX)
OP_16_LEN:		EQU		$-OP_16

				ORG		OP_17
RAL				EX	AF,AF'
				RLA
				EX	AF,AF'
				JP	(IX)
OP_17_LEN:		EQU		$-OP_17

				ORG		OP_18
				JP	(IX)
OP_18_LEN:		EQU		$-OP_18

				ORG		OP_19
DAD_D			EX	AF,AF'
				LD	DE,(RE)
				LD	HL,(RL)
				ADD	HL,DE
				LD	(RL),HL
				EX	AF,AF'
				JP	(IX)
OP_19_LEN:		EQU		$-OP_19

				ORG		OP_1A
LDAX_D			EX	AF,AF'
				LD	HL,(RE)
				SET	7,H
				LD	A,(HL)
				EX	AF,AF'
				JP	(IX)
OP_1A_LEN:		EQU		$-OP_1A

				ORG		OP_1B
DCX_D			LD	HL,(RE)
				DEC	HL
				LD	(RE),HL
				JP	(IX)
OP_1B_LEN:		EQU		$-OP_1B

				ORG		OP_1C
INR_E			EX	AF,AF'
				LD	HL,RE
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_1C_LEN:		EQU		$-OP_1C

				ORG		OP_1D
DCR_E			EX	AF,AF'
				LD	HL,RE
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_1D_LEN:		EQU		$-OP_1D

				ORG		OP_1E
MVI_E			LD	A,(BC)
				LD	(RE),A
				INC	BC
				JP	(IX)
OP_1E_LEN:		EQU		$-OP_1E

				ORG		OP_1F
RAR				EX	AF,AF'
				RRA
				EX	AF,AF'
				JP	(IX)
OP_1F_LEN:		EQU		$-OP_1F

				ORG		OP_20
				JP	(IX)
OP_20_LEN:		EQU		$-OP_20

				ORG		OP_21
LXI_H			LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				LD	(RL),HL
				JP	(IX)
OP_21_LEN:		EQU		$-OP_21

				ORG		OP_22
SHLD			LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				LD	DE,(RL)
				SET	7,H
				LD	(HL),E
				INC	HL
				LD	(HL),D
				JP	(IX)
OP_22_LEN:		EQU		$-OP_22

				ORG		OP_23
INX_H			LD	HL,(RL)
				INC	HL
				LD	(RL),HL
				JP	(IX)
OP_23_LEN:		EQU		$-OP_23

				ORG		OP_24
INR_H			EX	AF,AF'
				LD	HL,RH
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_24_LEN:		EQU		$-OP_24

				ORG		OP_25
DCR_H			EX	AF,AF'
				LD	HL,RH
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_25_LEN:		EQU		$-OP_25

				ORG		OP_26
MVI_H			LD	A,(BC)
				LD	(RH),A
				INC	BC
				JP	(IX)
OP_26_LEN:		EQU		$-OP_26

				ORG		OP_27
DAA				EX	AF,AF'
				DAA
				EX	AF,AF'
				JP	(IX)
OP_27_LEN:		EQU		$-OP_27

				ORG		OP_28
				JP	(IX)
OP_28_LEN:		EQU		$-OP_28

				ORG		OP_29
DAD_H			EX	AF,AF'
				LD	HL,(RL)
				ADD	HL,HL
				LD	(RL),HL
				EX	AF,AF'
				JP	(IX)
OP_29_LEN:		EQU		$-OP_29

				ORG		OP_2A
LHLD			LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				SET	7,H
				LD	E,(HL)
				INC	HL
				LD	D,(HL)
				LD	(RL),DE
				JP	(IX)
OP_2A_LEN:		EQU		$-OP_2A

				ORG		OP_2B
DCX_H			LD	HL,(RL)
				DEC	HL
				LD	(RL),HL
				JP	(IX)
OP_2B_LEN:		EQU		$-OP_2B

				ORG		OP_2C
INR_L			EX	AF,AF'
				LD	HL,RL
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_2C_LEN:		EQU		$-OP_2C

				ORG		OP_2D
DCR_L			EX	AF,AF'
				LD	HL,RL
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_2D_LEN:		EQU		$-OP_2D

				ORG		OP_2E
MVI_L			LD	A,(BC)
				LD	(RL),A
				INC	BC
				JP	(IX)
OP_2E_LEN:		EQU		$-OP_2E

				ORG		OP_2F
CMA				EX	AF,AF'
				CPL
				EX	AF,AF'
				JP	(IX)
OP_2F_LEN:		EQU		$-OP_2F

				ORG		OP_30
				JP	(IX)
OP_30_LEN:		EQU		$-OP_30

				ORG		OP_31
LXI_SP			LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				LD	(RSP),HL
				JP	(IX)
OP_31_LEN:		EQU		$-OP_31

				ORG		OP_32
STA				LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				SET	7,H
				INC	BC
				EX	AF,AF'
				LD	(HL),A
				EX	AF,AF'
				JP	(IX)
OP_32_LEN:		EQU		$-OP_32

				ORG		OP_33
INX_SP			LD	HL,(RSP)
				INC	HL
				LD	(RSP),HL
				JP	(IX)
OP_33_LEN:		EQU		$-OP_33

				ORG		OP_34
INR_M			LD	HL,(RL)
				SET	7,H
				EX	AF,AF'
				INC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_34_LEN:		EQU		$-OP_34

				ORG		OP_35
DCR_M			LD	HL,(RL)
				SET	7,H
				EX	AF,AF'
				DEC	(HL)
				CALL	PARINR
				EX	AF,AF'
				JP	(IX)
OP_35_LEN:		EQU		$-OP_35

				ORG		OP_36
MVI_M			LD	A,(BC)
				INC	BC
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_36_LEN:		EQU		$-OP_36

				ORG		OP_37
STC				EX	AF,AF'
				SCF
				EX	AF,AF'
				JP	(IX)
OP_37_LEN:		EQU		$-OP_37

				ORG		OP_38
				JP	(IX)
OP_38_LEN:		EQU		$-OP_38

				ORG		OP_39
DAD_SP			EX	AF,AF'
				LD	DE,(RSP)
				LD	HL,(RL)
				ADD	HL,DE
				LD	(RL),HL
				EX	AF,AF'
				JP	(IX)
OP_39_LEN:		EQU		$-OP_39

				ORG		OP_3A
LDA				LD	A,(BC)
				LD	L,A
				INC	BC
				LD	A,(BC)
				LD	H,A
				INC	BC
				SET	7,H
				EX	AF,AF'
				LD	A,(HL)
				EX	AF,AF'
				JP	(IX)
OP_3A_LEN:		EQU		$-OP_3A

				ORG		OP_3B
DCX_SP			LD	HL,(RSP)
				DEC	HL
				LD	(RSP),HL
				JP	(IX)
OP_3B_LEN:		EQU		$-OP_3B

				ORG		OP_3C
INR_A			EX	AF,AF'
				INC	A
				CALL	PARITY
				EX	AF,AF'
				JP	(IX)
OP_3C_LEN:		EQU		$-OP_3C

				ORG		OP_3D
DCR_A			EX	AF,AF'
				DEC	A
				CALL	PARITY
				EX	AF,AF'
				JP	(IX)
OP_3D_LEN:		EQU		$-OP_3D

				ORG		OP_3E
MVI_A			EX	AF,AF'
				LD	A,(BC)
				EX	AF,AF'
				INC	BC
				JP	(IX)
OP_3E_LEN:		EQU		$-OP_3E

				ORG		OP_3F
CMC				EX	AF,AF'
				CCF
				EX	AF,AF'
				JP	(IX)
OP_3F_LEN:		EQU		$-OP_3F

				ORG		OP_40
MOVB_B			LD	A,(RB)
				LD	(RB),A
				JP	(IX)
OP_40_LEN:		EQU		$-OP_40

				ORG		OP_41
MOVB_C			LD	A,(RC)
				LD	(RB),A
				JP	(IX)
OP_41_LEN:		EQU		$-OP_41

				ORG		OP_42
MOVB_D			LD	A,(RD)
				LD	(RB),A
				JP	(IX)
OP_42_LEN:		EQU		$-OP_42

				ORG		OP_43
MOVB_E			LD	A,(RE)
				LD	(RB),A
				JP	(IX)
OP_43_LEN:		EQU		$-OP_43

				ORG		OP_44
MOVB_H			LD	A,(RH)
				LD	(RB),A
				JP	(IX)
OP_44_LEN:		EQU		$-OP_44

				ORG		OP_45
MOVB_L			LD	A,(RL)
				LD	(RB),A
				JP	(IX)
OP_45_LEN:		EQU		$-OP_45

				ORG		OP_46
MOVB_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RB),A
				JP	(IX)
OP_46_LEN:		EQU		$-OP_46

				ORG		OP_47
MOVB_A			EX	AF,AF'
				LD	(RB),A
				EX	AF,AF'
				JP	(IX)
OP_47_LEN:		EQU		$-OP_47

				ORG		OP_48
MOVC_B			LD	A,(RB)
				LD	(RC),A
				JP	(IX)
OP_48_LEN:		EQU		$-OP_48

				ORG		OP_49
MOVC_C			LD	A,(RC)
				LD	(RC),A
				JP	(IX)
OP_49_LEN:		EQU		$-OP_49

				ORG		OP_4A
MOVC_D			LD	A,(RD)
				LD	(RC),A
				JP	(IX)
OP_4A_LEN:		EQU		$-OP_4A

				ORG		OP_4B
MOVC_E			LD	A,(RE)
				LD	(RC),A
				JP	(IX)
OP_4B_LEN:		EQU		$-OP_4B

				ORG		OP_4C
MOVC_H			LD	A,(RH)
				LD	(RC),A
				JP	(IX)
OP_4C_LEN:		EQU		$-OP_4C

				ORG		OP_4D
MOVC_L			LD	A,(RL)
				LD	(RC),A
				JP	(IX)
OP_4D_LEN:		EQU		$-OP_4D

				ORG		OP_4E
MOVC_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RC),A
				JP	(IX)
OP_4E_LEN:		EQU		$-OP_4E

				ORG		OP_4F
MOVC_A			EX	AF,AF'
				LD	(RC),A
				EX	AF,AF'
				JP	(IX)
OP_4F_LEN:		EQU		$-OP_4F

				ORG		OP_50
MOVD_B			LD	A,(RB)
				LD	(RD),A
				JP	(IX)
OP_50_LEN:		EQU		$-OP_50

				ORG		OP_51
MOVD_C			LD	A,(RC)
				LD	(RD),A
				JP	(IX)
OP_51_LEN:		EQU		$-OP_51

				ORG		OP_52
MOVD_D			LD	A,(RD)
				LD	(RD),A
				JP	(IX)
OP_52_LEN:		EQU		$-OP_52

				ORG		OP_53
MOVD_E			LD	A,(RE)
				LD	(RD),A
				JP	(IX)
OP_53_LEN:		EQU		$-OP_53

				ORG		OP_54
MOVD_H			LD	A,(RH)
				LD	(RD),A
				JP	(IX)
OP_54_LEN:		EQU		$-OP_54

				ORG		OP_55
MOVD_L			LD	A,(RL)
				LD	(RD),A
				JP	(IX)
OP_55_LEN:		EQU		$-OP_55

				ORG		OP_56
MOVD_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RD),A
				JP	(IX)
OP_56_LEN:		EQU		$-OP_56

				ORG		OP_57
MOVD_A			EX	AF,AF'
				LD	(RD),A
				EX	AF,AF'
				JP	(IX)
OP_57_LEN:		EQU		$-OP_57

				ORG		OP_58
MOVE_B			LD	A,(RB)
				LD	(RE),A
				JP	(IX)
OP_58_LEN:		EQU		$-OP_58

				ORG		OP_59
MOVE_C			LD	A,(RC)
				LD	(RE),A
				JP	(IX)
OP_59_LEN:		EQU		$-OP_59

				ORG		OP_5A
MOVE_D			LD	A,(RD)
				LD	(RE),A
				JP	(IX)
OP_5A_LEN:		EQU		$-OP_5A

				ORG		OP_5B
MOVE_E			LD	A,(RE)
				LD	(RE),A
				JP	(IX)
OP_5B_LEN:		EQU		$-OP_5B

				ORG		OP_5C
MOVE_H			LD	A,(RH)
				LD	(RE),A
				JP	(IX)
OP_5C_LEN:		EQU		$-OP_5C

				ORG		OP_5D
MOVE_L			LD	A,(RL)
				LD	(RE),A
				JP	(IX)
OP_5D_LEN:		EQU		$-OP_5D

				ORG		OP_5E
MOVE_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RE),A
				JP	(IX)
OP_5E_LEN:		EQU		$-OP_5E

				ORG		OP_5F
MOVE_A			EX	AF,AF'
				LD	(RE),A
				EX	AF,AF'
				JP	(IX)
OP_5F_LEN:		EQU		$-OP_5F

				ORG		OP_60
MOVH_B			LD	A,(RB)
				LD	(RH),A
				JP	(IX)
OP_60_LEN:		EQU		$-OP_60

				ORG		OP_61
MOVH_C			LD	A,(RC)
				LD	(RH),A
				JP	(IX)
OP_61_LEN:		EQU		$-OP_61

				ORG		OP_62
MOVH_D			LD	A,(RD)
				LD	(RH),A
				JP	(IX)
OP_62_LEN:		EQU		$-OP_62

				ORG		OP_63
MOVH_E			LD	A,(RE)
				LD	(RH),A
				JP	(IX)
OP_63_LEN:		EQU		$-OP_63

				ORG		OP_64
MOVH_H			LD	A,(RH)
				LD	(RH),A
				JP	(IX)
OP_64_LEN:		EQU		$-OP_64

				ORG		OP_65
MOVH_L			LD	A,(RL)
				LD	(RH),A
				JP	(IX)
OP_65_LEN:		EQU		$-OP_65

				ORG		OP_66
MOVH_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RH),A
				JP	(IX)
OP_66_LEN:		EQU		$-OP_66

				ORG		OP_67
MOVH_A			EX	AF,AF'
				LD	(RH),A
				EX	AF,AF'
				JP	(IX)
OP_67_LEN:		EQU		$-OP_67

				ORG		OP_68
MOVL_B			LD	A,(RB)
				LD	(RL),A
				JP	(IX)
OP_68_LEN:		EQU		$-OP_68

				ORG		OP_69
MOVL_C			LD	A,(RC)
				LD	(RL),A
				JP	(IX)
OP_69_LEN:		EQU		$-OP_69

				ORG		OP_6A
MOVL_D			LD	A,(RD)
				LD	(RL),A
				JP	(IX)
OP_6A_LEN:		EQU		$-OP_6A

				ORG		OP_6B
MOVL_E			LD	A,(RE)
				LD	(RL),A
				JP	(IX)
OP_6B_LEN:		EQU		$-OP_6B

				ORG		OP_6C
MOVL_H			LD	A,(RH)
				LD	(RL),A
				JP	(IX)
OP_6C_LEN:		EQU		$-OP_6C

				ORG		OP_6D
MOVL_L			LD	A,(RL)
				LD	(RL),A
				JP	(IX)
OP_6D_LEN:		EQU		$-OP_6D

				ORG		OP_6E
MOVL_M			LD	HL,(RL)
				SET	7,H
				LD	A,(HL)
				LD	(RL),A
				JP	(IX)
OP_6E_LEN:		EQU		$-OP_6E

				ORG		OP_6F
MOVL_A			EX	AF,AF'
				LD	(RL),A
				EX	AF,AF'
				JP	(IX)
OP_6F_LEN:		EQU		$-OP_6F

				ORG		OP_70
MOVM_B			LD	A,(RB)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_70_LEN:		EQU		$-OP_70

				ORG		OP_71
MOVM_C			LD	A,(RC)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_71_LEN:		EQU		$-OP_71

				ORG		OP_72
MOVM_D			LD	A,(RD)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_72_LEN:		EQU		$-OP_72

				ORG		OP_73
MOVM_E			LD	A,(RE)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_73_LEN:		EQU		$-OP_73

				ORG		OP_74
MOVM_H			LD	A,(RH)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_74_LEN:		EQU		$-OP_74

				ORG		OP_75
MOVM_L			LD	A,(RL)
				LD	HL,(RL)
				SET	7,H
				LD	(HL),A
				JP	(IX)
OP_75_LEN:		EQU		$-OP_75

				ORG		OP_76
				JP	(IX)
OP_76_LEN:		EQU		$-OP_76

				ORG		OP_77
MOVM_A			LD	HL,(RL)
				SET	7,H
				EX	AF,AF'
				LD	(HL),A
				EX	AF,AF'
				JP	(IX)
OP_77_LEN:		EQU		$-OP_77

				ORG		OP_78
MOVA_B			LD	A,(RB)
				LD	H,A
				EX	AF,AF'
				LD	A,H
				EX	AF,AF'
				JP	(IX)
OP_78_LEN:		EQU		$-OP_78

				ORG		OP_79
MOVA_C			LD	A,(RC)
				LD	H,A
				EX	AF,AF'
				LD	A,H
				EX	AF,AF'
				JP	(IX)
OP_79_LEN:		EQU		$-OP_79

				ORG		OP_7A
MOVA_D			LD	A,(RD)		; [13]
				LD	H,A			; [4]
				EX	AF,AF'		; [4]
				LD	A,H			; [4]
				EX	AF,AF'		; [4]
;---------------[fetch]-----------[43]
;---------------[total]-----------[]
				
;-----------------------------------------
;				EXX				; [4]
;				EX	AF,AF'		; [4]
;				LD	A,D			; [4]
;				EX	AF,AF'		; [4]
;				EXX				; [4]
;---------------[fetch]-----------[40]
;---------------[total]-----------[-12]--------
				JP	(IX)
OP_7A_LEN:		EQU		$-OP_7A

				ORG		OP_7B
MOVA_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	LD	A,H
	EX	AF,AF'
	JP	(IX)
OP_7B_LEN:		EQU		$-OP_7B

				ORG		OP_7C
MOVA_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	LD	A,H
	EX	AF,AF'
	JP	(IX)
OP_7C_LEN:		EQU		$-OP_7C

				ORG		OP_7D
MOVA_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	LD	A,H
	EX	AF,AF'
	JP	(IX)
OP_7D_LEN:		EQU		$-OP_7D

				ORG		OP_7E
MOVA_M	LD	HL,(RL)
	SET	7,H
	EX	AF,AF'
	LD	A,(HL)
	EX	AF,AF'
	JP	(IX)
OP_7E_LEN:		EQU		$-OP_7E

				ORG		OP_7F
MOVA_A	EX	AF,AF'
	LD	A,A
	EX	AF,AF'
	JP	(IX)
OP_7F_LEN:		EQU		$-OP_7F

				ORG		OP_80
ADD_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_80_LEN:		EQU		$-OP_80

				ORG		OP_81
ADD_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_81_LEN:		EQU		$-OP_81

				ORG		OP_82
ADD_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_82_LEN:		EQU		$-OP_82

				ORG		OP_83
ADD_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_83_LEN:		EQU		$-OP_83

				ORG		OP_84
ADD_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_84_LEN:		EQU		$-OP_84

				ORG		OP_85
ADD_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_85_LEN:		EQU		$-OP_85

				ORG		OP_86
ADD_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_86_LEN:		EQU		$-OP_86

				ORG		OP_87
ADD_A	EX	AF,AF'
	ADD	A,A
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_87_LEN:		EQU		$-OP_87

				ORG		OP_88
ADC_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_88_LEN:		EQU		$-OP_88

				ORG		OP_89
ADC_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_89_LEN:		EQU		$-OP_89

				ORG		OP_8A
ADC_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8A_LEN:		EQU		$-OP_8A

				ORG		OP_8B
ADC_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8B_LEN:		EQU		$-OP_8B

				ORG		OP_8C
ADC_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8C_LEN:		EQU		$-OP_8C

				ORG		OP_8D
ADC_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8D_LEN:		EQU		$-OP_8D

				ORG		OP_8E
ADC_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8E_LEN:		EQU		$-OP_8E

				ORG		OP_8F
ADC_A	EX	AF,AF'
	ADC	A,A
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_8F_LEN:		EQU		$-OP_8F

				ORG		OP_90
SUB_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_90_LEN:		EQU		$-OP_90

				ORG		OP_91
SUB_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_91_LEN:		EQU		$-OP_91

				ORG		OP_92
SUB_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_92_LEN:		EQU		$-OP_92

				ORG		OP_93
SUB_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_93_LEN:		EQU		$-OP_93

				ORG		OP_94
SUB_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_94_LEN:		EQU		$-OP_94

				ORG		OP_95
SUB_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_95_LEN:		EQU		$-OP_95

				ORG		OP_96
SUB_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_96_LEN:		EQU		$-OP_96

				ORG		OP_97
SUB_A	EX	AF,AF'
	SUB	A
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_97_LEN:		EQU		$-OP_97

				ORG		OP_98
SBB_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_98_LEN:		EQU		$-OP_98

				ORG		OP_99
SBB_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_99_LEN:		EQU		$-OP_99

				ORG		OP_9A
SBB_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9A_LEN:		EQU		$-OP_9A

				ORG		OP_9B
SBB_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9B_LEN:		EQU		$-OP_9B

				ORG		OP_9C
SBB_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9C_LEN:		EQU		$-OP_9C

				ORG		OP_9D
SBB_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9D_LEN:		EQU		$-OP_9D

				ORG		OP_9E
SBB_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9E_LEN:		EQU		$-OP_9E

				ORG		OP_9F
SBB_A	EX	AF,AF'
	SBC	A,A
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_9F_LEN:		EQU		$-OP_9F

				ORG		OP_A0
ANA_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A0_LEN:		EQU		$-OP_A0

				ORG		OP_A1
ANA_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A1_LEN:		EQU		$-OP_A1

				ORG		OP_A2
ANA_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A2_LEN:		EQU		$-OP_A2

				ORG		OP_A3
ANA_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A3_LEN:		EQU		$-OP_A3

				ORG		OP_A4
ANA_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A4_LEN:		EQU		$-OP_A4

				ORG		OP_A5
ANA_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A5_LEN:		EQU		$-OP_A5

				ORG		OP_A6
ANA_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_A6_LEN:		EQU		$-OP_A6

				ORG		OP_A7
ANA_A	EX	AF,AF'
	AND	A
	EX	AF,AF'
	JP	(IX)
OP_A7_LEN:		EQU		$-OP_A7

				ORG		OP_A8
XRA_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_A8_LEN:		EQU		$-OP_A8

				ORG		OP_A9
XRA_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_A9_LEN:		EQU		$-OP_A9

				ORG		OP_AA
XRA_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_AA_LEN:		EQU		$-OP_AA

				ORG		OP_AB
XRA_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_AB_LEN:		EQU		$-OP_AB

				ORG		OP_AC
XRA_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_AC_LEN:		EQU		$-OP_AC

				ORG		OP_AD
XRA_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_AD_LEN:		EQU		$-OP_AD

				ORG		OP_AE
XRA_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_AE_LEN:		EQU		$-OP_AE

				ORG		OP_AF
XRA_A	EX	AF,AF'
	XOR	A
	EX	AF,AF'
	JP	(IX)
OP_AF_LEN:		EQU		$-OP_AF

				ORG		OP_B0
ORA_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	OR	H
	EX	AF,AF'
	JP	(IX)
OP_B0_LEN:		EQU		$-OP_B0

				ORG		OP_B1
ORA_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B1_LEN:		EQU		$-OP_B1

				ORG		OP_B2
ORA_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B2_LEN:		EQU		$-OP_B2

				ORG		OP_B3
ORA_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B3_LEN:		EQU		$-OP_B3

				ORG		OP_B4
ORA_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B4_LEN:		EQU		$-OP_B4

				ORG		OP_B5
ORA_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B5_LEN:		EQU		$-OP_B5

				ORG		OP_B6
ORA_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	OR 	H
	EX	AF,AF'
	JP	(IX)
OP_B6_LEN:		EQU		$-OP_B6

				ORG		OP_B7
ORA_A	EX	AF,AF'
	OR 	A
	EX	AF,AF'
	JP	(IX)
OP_B7_LEN:		EQU		$-OP_B7

				ORG		OP_B8
CMP_B	LD	A,(RB)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_B8_LEN:		EQU		$-OP_B8

				ORG		OP_B9
CMP_C	LD	A,(RC)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_B9_LEN:		EQU		$-OP_B9

				ORG		OP_BA
CMP_D	LD	A,(RD)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BA_LEN:		EQU		$-OP_BA

				ORG		OP_BB
CMP_E	LD	A,(RE)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BB_LEN:		EQU		$-OP_BB

				ORG		OP_BC
CMP_H	LD	A,(RH)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BC_LEN:		EQU		$-OP_BC

				ORG		OP_BD
CMP_L	LD	A,(RL)
	LD	H,A
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BD_LEN:		EQU		$-OP_BD

				ORG		OP_BE
CMP_M	LD	HL,(RL)
	SET	7,H
	LD	H,(HL)
	EX	AF,AF'
	CP 	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BE_LEN:		EQU		$-OP_BE

				ORG		OP_BF
CMP_A	EX	AF,AF'
	CP 	A
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_BF_LEN:		EQU		$-OP_BF

				ORG		OP_C0
RNZ	EX	AF,AF'
	JP	NZ,RZ1
	EX	AF,AF'
	JP	(IX)
OP_C0_LEN:		EQU		$-OP_C0

				ORG		OP_C1
POP_B	LD	HL,(RSP)
	SET	7,H
	LD	E,(HL)		;Get contents of em_ SP
	INC	HL		;from emulated stack
	LD	D,(HL)		;DE has contents for BC
	INC	HL
	RES	7,H
	LD	(RSP),HL
	LD	(RC),DE
	JP	(IX)
OP_C1_LEN:		EQU		$-OP_C1

				ORG		OP_C2
JNZ	EX	AF,AF'
	JP	NZ,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_C2_LEN:		EQU		$-OP_C2

				ORG		OP_C3
JMP	LD	A,(BC)
	LD	L,A
	INC	BC
	LD	A,(BC)
	LD	H,A
	SET	7,H
	LD	B,H
	LD	C,L
	JP	(IX)
OP_C3_LEN:		EQU		$-OP_C3

				ORG		OP_C4
CNZ	EX	AF,AF'
	JP	NZ,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_C4_LEN:		EQU		$-OP_C4

				ORG		OP_C5
PUSH_B	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	LD	DE,(RC)
	LD	(HL),D
	DEC	HL
	LD	(HL),E
	RES	7,H
	LD	(RSP),HL
	JP	(IX)
OP_C5_LEN:		EQU		$-OP_C5

				ORG		OP_C6
ADI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	ADD	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_C6_LEN:		EQU		$-OP_C6

				ORG		OP_C7
RST_0	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8000H
	JP	(IX)
OP_C7_LEN:		EQU		$-OP_C7

				ORG		OP_C8
RZ	EX	AF,AF'
	JP	Z,RZ1
	EX	AF,AF'
	JP	(IX)
OP_C8_LEN:		EQU		$-OP_C8

				ORG		OP_C9
RET	LD	HL,(RSP)
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
OP_C9_LEN:		EQU		$-OP_C9

				ORG		OP_CA
JZ	EX	AF,AF'
	JP	Z,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_CA_LEN:		EQU		$-OP_CA

				ORG		OP_CB
	LD	A,(BC)
	LD	L,A
	INC	BC
	LD	A,(BC)
	LD	H,A
	SET	7,H
	LD	B,H
	LD	C,L
	JP	(IX)
OP_CB_LEN:		EQU		$-OP_CB

				ORG		OP_CC
CZ	EX	AF,AF'
	JP	Z,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_CC_LEN:		EQU		$-OP_CC

				ORG		OP_CD
CALL	LD	A,(BC)
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
OP_CD_LEN:		EQU		$-OP_CD

				ORG		OP_CE
ACI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	ADC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_CE_LEN:		EQU		$-OP_CE

				ORG		OP_CF
RST_1	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8008H
	JP	(IX)
OP_CF_LEN:		EQU		$-OP_CF

				ORG		OP_D0
RNC	EX	AF,AF'
	JP	NC,RZ1
	EX	AF,AF'
	JP	(IX)
OP_D0_LEN:		EQU		$-OP_D0

				ORG		OP_D1
POP_D	LD	HL,(RSP)
	SET	7,H
	LD	E,(HL)
	INC	HL
	LD	D,(HL)
	INC	HL
	RES	7,H
	LD	(RSP),HL
	LD	(RE),DE
	JP	(IX)
OP_D1_LEN:		EQU		$-OP_D1

				ORG		OP_D2
JNC	EX	AF,AF'
	JP	NC,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_D2_LEN:		EQU		$-OP_D2

				ORG		OP_D3
OUT	LD	A,(BC)
	INC	BC
	OR	A
	JP	NZ,OUT00
	JP	(IX)
OUT00	CP	1
	JP	Z,OUT01
LOOP4	JP	LOOP4
OUT01	LD	A,(SAVLOD)
	OR	A
	JP	P,OUT04
	LD	HL,(SLADD)	; FFH=Save
	EX	AF,AF'
	PUSH	AF
	EX	AF,AF'
	POP	AF
	AND	7FH
	LD	(HL),A
	INC	HL
	LD	(SLADD),HL
OUT04	EX	AF,AF'
	AND	7FH
	PUSH	AF
	JP	Z,OUT02
	CP	0DH
	JP	Z,OUT02
	CP	5FH	;Correction for DEL (08)
	JP	NZ,OUT03
	LD	A,8
OUT03	PUSH	BC
	CALL	33H		;Display char
	POP	BC
OUT02	POP	AF
	EX	AF,AF'
	JP	(IX)
OP_D3_LEN:		EQU		$-OP_D3

				ORG		OP_D4
CNC	EX	AF,AF'
	JP	NC,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_D4_LEN:		EQU		$-OP_D4

				ORG		OP_D5
PUSH_D	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	LD	DE,(RE)
	LD	(HL),D
	DEC	HL
	LD	(HL),E
	RES	7,H
	LD	(RSP),HL
	JP	(IX)
OP_D5_LEN:		EQU		$-OP_D5

				ORG		OP_D6
SUI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	SUB	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_D6_LEN:		EQU		$-OP_D6

				ORG		OP_D7
RST_2	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8010H
	JP	(IX)
OP_D7_LEN:		EQU		$-OP_D7

				ORG		OP_D8
RC1	EX	AF,AF'
	JP	C,RZ1
	EX	AF,AF'
	JP	(IX)
OP_D8_LEN:		EQU		$-OP_D8

				ORG		OP_D9
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
OP_D9_LEN:		EQU		$-OP_D9

				ORG		OP_DA
JC	EX	AF,AF'
	JP	C,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_DA_LEN:		EQU		$-OP_DA

				ORG		OP_DB
IN	LD	A,(BC)
	INC	BC
	OR	A
	JP	Z,IOSTAT
	CP	1
	JP	Z,IOPORT
IOSTAT	LD	A,(SAVLOD)
	DEC	A
	JP	Z,IOST4
	LD	A,(KEY)
	OR	A
	JP	NZ,IOST4
	CALL	2BH		;Scan keys
	DEC	A
	JP	M,IOST5    ; A was 0 - no key pressed
	JP	NZ,IOST2	; Key pressed
	INC	A	;BREAK, make a=3
	INC	A
IOST2	INC	A
IOST3	LD	(KEY),A
IOST4 	EX	AF,AF'
	XOR	A	; Bit 7=0, bit 0=0 (ready for
	EX	AF,AF'	; output, has input char)
	JP	(IX)
IOST5	EX	AF,AF'
	LD	A,1	;Bit 7=0, bit 0=1 (ready for
	EX	AF,AF'	; output, no input char)
	JP	(IX)
IOPORT	LD	A,(SAVLOD)
	DEC	A
	JP	NZ,IOP2	; Save or nothing
	LD	HL,(SLADD)	; Loading
	LD	DE,(SLFIN)
	RST	18H	; HL > DE?
	JP	NC,IOP1	; Yes, past last char
	LD	A,(HL)
	LD	(KEY),A
	INC	HL
	LD	(SLADD),HL
	JP	IOP2
IOP1	XOR	A
	LD	(SAVLOD),A
	LD	BC,81F9H	; Print OK
	JP	(IX)
IOP2	EX	AF,AF'
	LD	A,(KEY)
	CP	8	;DEL?
	JP	NZ,IOP3
	LD	A,5FH	;Change from 08 to 5fH
IOP3	EX	AF,AF'
	XOR	A
	LD	(KEY),A
	JP	(IX)
OP_DB_LEN:		EQU		$-OP_DB


				ORG		OP_DC
CC	EX	AF,AF'
	JP	C,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_DC_LEN:		EQU		$-OP_DC

				ORG		OP_DD
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
OP_DD_LEN:		EQU		$-OP_DD

				ORG		OP_DE
SBI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	SBC	A,H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_DE_LEN:		EQU		$-OP_DE

				ORG		OP_DF
RST_3	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8018H
	JP	(IX)
OP_DF_LEN:		EQU		$-OP_DF

				ORG		OP_E0
RPO	EX	AF,AF'
	JP	PO,RZ1
	EX	AF,AF'
	JP	(IX)
OP_E0_LEN:		EQU		$-OP_E0

				ORG		OP_E1
POP_H	LD	HL,(RSP)
	SET	7,H
	LD	E,(HL)		;Get contents of em_ SP
	INC	HL		;from emulated stack
	LD	D,(HL)		;DE has contents for BC
	INC	HL
	RES	7,H
	LD	(RSP),HL
	LD	(RL),DE
	JP	(IX)
OP_E1_LEN:		EQU		$-OP_E1

				ORG		OP_E2
JPO	EX	AF,AF'
	JP	PO,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_E2_LEN:		EQU		$-OP_E2

				ORG		OP_E3
XTHL	LD	HL,(RSP)
	SET	7,H
	LD	IY,0
	DI
	ADD	IY,SP
	LD	SP,HL
	LD	HL,(RL)
	EX	(SP),HL
	LD	(RL),HL
	LD	SP,IY
	EI
	JP	(IX)
OP_E3_LEN:		EQU		$-OP_E3

				ORG		OP_E4
CPO	EX	AF,AF'
	JP	PO,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_E4_LEN:		EQU		$-OP_E4

				ORG		OP_E5
PUSH_H	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	LD	DE,(RL)
	LD	(HL),D
	DEC	HL
	LD	(HL),E
	RES	7,H
	LD	(RSP),HL
	JP	(IX)
OP_E5_LEN:		EQU		$-OP_E5

				ORG		OP_E6
ANI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	AND	H
	EX	AF,AF'
	JP	(IX)
OP_E6_LEN:		EQU		$-OP_E6

				ORG		OP_E7
RST_4	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8020H
	JP	(IX)
OP_E7_LEN:		EQU		$-OP_E7

				ORG		OP_E8
RPE	EX	AF,AF'
	JP	PE,RZ1
	EX	AF,AF'
	JP	(IX)
OP_E8_LEN:		EQU		$-OP_E8

				ORG		OP_E9
PCHL	LD	BC,(RL)
	SET	7,B
	JP	(IX)
OP_E9_LEN:		EQU		$-OP_E9

				ORG		OP_EA
JPE	EX	AF,AF'
	JP	PE,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_EA_LEN:		EQU		$-OP_EA

				ORG		OP_EB
XCHG	LD	DE,(RE)
	LD	HL,(RL)
	LD	(RE),HL
	LD	(RL),DE
	JP	(IX)
OP_EB_LEN:		EQU		$-OP_EB

				ORG		OP_EC
CPE	EX	AF,AF'
	JP	PE,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_EC_LEN:		EQU		$-OP_EC

				ORG		OP_ED
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
OP_ED_LEN:		EQU		$-OP_ED

				ORG		OP_EE
XRI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	XOR	H
	EX	AF,AF'
	JP	(IX)
OP_EE_LEN:		EQU		$-OP_EE

				ORG		OP_EF
RST_5	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8028H
	JP	(IX)
OP_EF_LEN:		EQU		$-OP_EF

				ORG		OP_F0
RP	EX	AF,AF'
	JP	P,RZ1
	EX	AF,AF'
	JP	(IX)
OP_F0_LEN:		EQU		$-OP_F0

				ORG		OP_F1
POP_PSW	LD	HL,(RSP)
	SET	7,H
	LD	IY,0
	DI
	ADD	IY,SP
	LD	SP,HL
	EX	AF,AF'
	POP	AF
	EX	AF,AF'
	INC	HL
	INC	HL
	RES	7,H
	LD	(RSP),HL
	LD	SP,IY
	EI
	JP	(IX)
OP_F1_LEN:		EQU		$-OP_F1

				ORG		OP_F2
JP	EX	AF,AF'
	JP	P,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_F2_LEN:		EQU		$-OP_F2

				ORG		OP_F3
DI	JP	(IX)
OP_F3_LEN:		EQU		$-OP_F3

				ORG		OP_F4
CP	EX	AF,AF'
	JP	P,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_F4_LEN:		EQU		$-OP_F4

				ORG		OP_F5
PUSH_P	LD	HL,(RSP)
	SET	7,H
	LD	IY,0
	DI
	ADD	IY,SP
	LD	SP,HL
	EX	AF,AF'
	PUSH	AF
	EX	AF,AF'
	DEC	HL
	DEC	HL
	RES	7,H
	LD	(RSP),HL
	LD	SP,IY
	EI
	JP	(IX)
OP_F5_LEN:		EQU		$-OP_F5

				ORG		OP_F6
ORI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	OR	H
	EX	AF,AF'
	JP	(IX)
OP_F6_LEN:		EQU		$-OP_F6

				ORG		OP_F7
RST_6	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8030H
	JP	(IX)
OP_F7_LEN:		EQU		$-OP_F7

				ORG		OP_F8
RM	EX	AF,AF'
	JP	M,RZ1
	EX	AF,AF'
	JP	(IX)
OP_F8_LEN:		EQU		$-OP_F8

				ORG		OP_F9
SPHL	LD	HL,(RSP)
	LD	DE,(RL)
	LD	(RSP),DE
	JP	(IX)
OP_F9_LEN:		EQU		$-OP_F9

				ORG		OP_FA
JM	EX	AF,AF'
	JP	M,JNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_FA_LEN:		EQU		$-OP_FA

				ORG		OP_FB
EI	JP	(IX)
OP_FB_LEN:		EQU		$-OP_FB

				ORG		OP_FC
CM	EX	AF,AF'
	JP	M,CNZ1
	EX	AF,AF'
	INC	BC
	INC	BC
	JP	(IX)
OP_FC_LEN:		EQU		$-OP_FC

				ORG		OP_FD
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
OP_FD_LEN:		EQU		$-OP_FD

				ORG		OP_FE
CPI	LD	A,(BC)
	INC	BC
	LD	H,A
	EX	AF,AF'
	CP	H
	CALL	PARITY
	EX	AF,AF'
	JP	(IX)
OP_FE_LEN:		EQU		$-OP_FE

				ORG		OP_FF
RST_7	LD	HL,(RSP)
	SET	7,H
	DEC	HL
	RES	7,B
	LD	(HL),B
	DEC	HL
	LD	(HL),C
	RES	7,H
	LD	(RSP),HL
	LD	BC,8038H
	JP	(IX)
OP_FF_LEN:		EQU		$-OP_FF





