	.data
__TMP_VAR_11: .string	"\n"
__TMP_VAR_4: .long	0
_0: .long	0
_1: .long	1
_2: .long	2
_3: .long	3
_5: .long	5
__TMP_VAR_15: .string	"A era=15\n"
_a: .long	0
__TMP_VAR_20: .long	0
_c: .byte	120
_d: .byte	48
_f: 	.long	2
	.long	3
_i: .long	1
_n: .long	0
__TMP_VAR_3: .long	0
_x: .long	0
__TMP_VAR_19: .long	0
__TMP_VAR_2: .string	"Digite um numero: \n"
__TMP_VAR_1: .long	0
__TMP_VAR_12: .string	"Incrementado algumas vezes a fica "
__TMP_VAR_0: .long	0
__TMP_VAR_16: .long	0
_10: .long	10
__TMP_VAR_13: .long	0
_100: .long	100
__TMP_VAR_17: .string	"Nao tem como isso....\n"
__TMP_VAR_9: .long	0
_15: .long	15
__TMP_VAR_8: .long	0
__TMP_VAR_10: .long	0
__TMP_VAR_7: .long	0
__TMP_VAR_14: .long	0
_55: .long	55
__TMP_VAR_6: .long	0
__TMP_VAR_18: .string	"OK!\n"
__TMP_VAR_5: .long	0

 # PRINT
print_string_int:
	.string	"%d"

print_string_float:
	.string	"%d/%d"

print_string_char:
	.string	"%c"
print_string:
	.string	"%s"


 #READ
read:
	.string	"%d"



# TAC_ARRAY
_v:
	 .long 'a' 	# v[0]
	 .long 0 	# v[1]
	 .long 0 	# v[2]
	 .long 0 	# v[3]
	 .long 0 	# v[4]
	 .long 0 	# v[5]
	 .long 0 	# v[6]
	 .long 0 	# v[7]
	 .long 0 	# v[8]
	 .long 0 	# v[9]

# TAC_BEGINFUN
	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp


# TAC_MOVE //ASSIGN 
    movl	_0(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_SUB 
    movl	_a(%rip), %edx
    movl	_i(%rip), %eax
    subl	%eax, %edx
    movl	%edx, %eax
    movl	%eax, __TMP_VAR_0(%rip)
    movl	$0, %eax




# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_0(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_MOVE //ASSIGN 
    movl	_5(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_ARRAY SET_ELEMENT EXP
	movl	_a(%rip), %edx   #endereço
	movl	_55(%rip), %eax   #valor
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	_v(%rip), %rdx   #array
	movl	%eax, (%rcx,%rdx)

# TAC_ARRAY GET_ELEMENT
    movl	20+_v(%rip), %eax
    movl	%eax, __TMP_VAR_1(%rip)
    movl	$0, %eax


# TAC_PRINT_INT 
    movl	__TMP_VAR_1(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT


# TAC_PRINT_INT 
    movl	_a(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_MOVE //ASSIGN 
    movl	_2(%rip), %eax
    movl	%eax, _i(%rip)
    movl	$0, %eax




# TAC_PRINT_STRING 
    leaq	__TMP_VAR_2(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_READ
	leaq	__TMP_VAR_3(%rip), %rsi
	leaq	read(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT

# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_3(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_LABEL
    __TMP_LABEL_0:	# AUTO



# TAC_LT 
	movl	_i(%rip), %edx
	movl	_10(%rip), %eax
	cmpl	%eax, %edx 
	jl	CMP_LBL_TEMP_0 		# se condição verdadeira pula para setar 1
 	movl	$0, __TMP_VAR_4(%rip) 		# Se falsa seta 0 
	jmp	CMP_LBL_TEMP_1 		# e pula para o final do bloco

CMP_LBL_TEMP_0: 		 #se condição verdadeira seta 1
	movl	$1, __TMP_VAR_4(%rip)

CMP_LBL_TEMP_1:	#final do bloco



# TAC_JMPZ
	movl	__TMP_VAR_4(%rip), %edx
	movl	$0, %eax
	cmpl	%eax, %edx 	# Se condicional anterior for 0 pula o trecho a baixo
    jz __TMP_LABEL_1


# TAC_TAC_FUN_CALL_ARGS

	movl	_1(%rip), %r10d
	pushq	%r10

	movl	_i(%rip), %r10d
	pushq	%r10

	# TAC_TAC_FUN_CALL
	call	incn
	addq	$16, %rsp
	movl	%eax, __TMP_VAR_7(%rip) #move return to tempvar


# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_7(%rip), %eax
    movl	%eax, _i(%rip)
    movl	$0, %eax




# TAC_TAC_FUN_CALL_ARGS

	movl	_1(%rip), %r10d
	pushq	%r10

	movl	_a(%rip), %r10d
	pushq	%r10

	# TAC_TAC_FUN_CALL
	call	incn
	addq	$16, %rsp
	movl	%eax, __TMP_VAR_10(%rip) #move return to tempvar


# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_10(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_JMP
	jmp	__TMP_LABEL_0



# TAC_LABEL
    __TMP_LABEL_1:	# AUTO



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_12(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax


# TAC_PRINT_INT 
    movl	_a(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_11(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_EQ 
	movl	_a(%rip), %edx
	movl	_15(%rip), %eax
	cmpl	%eax, %edx 
	je	CMP_LBL_TEMP_2 		# se condição verdadeira pula para setar 1
 	movl	$0, __TMP_VAR_13(%rip) 		# Se falsa seta 0 
	jmp	CMP_LBL_TEMP_3 		# e pula para o final do bloco

CMP_LBL_TEMP_2: 		 #se condição verdadeira seta 1
	movl	$1, __TMP_VAR_13(%rip)

CMP_LBL_TEMP_3:	#final do bloco



# TAC_JMPZ
	movl	__TMP_VAR_13(%rip), %edx
	movl	$0, %eax
	cmpl	%eax, %edx 	# Se condicional anterior for 0 pula o trecho a baixo
    jz __TMP_LABEL_3


# TAC_LABEL
    __TMP_LABEL_2:	# label__dash__x



# TAC_SUB 
    movl	_a(%rip), %edx
    movl	_1(%rip), %eax
    subl	%eax, %edx
    movl	%edx, %eax
    movl	%eax, __TMP_VAR_14(%rip)
    movl	$0, %eax




# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_14(%rip), %eax
    movl	%eax, _a(%rip)
    movl	$0, %eax




# TAC_PRINT_STRING 
    leaq	__TMP_VAR_15(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_LABEL
    __TMP_LABEL_3:	# AUTO



# TAC_EQ 
	movl	_i(%rip), %edx
	movl	_100(%rip), %eax
	cmpl	%eax, %edx 
	je	CMP_LBL_TEMP_4 		# se condição verdadeira pula para setar 1
 	movl	$0, __TMP_VAR_16(%rip) 		# Se falsa seta 0 
	jmp	CMP_LBL_TEMP_5 		# e pula para o final do bloco

CMP_LBL_TEMP_4: 		 #se condição verdadeira seta 1
	movl	$1, __TMP_VAR_16(%rip)

CMP_LBL_TEMP_5:	#final do bloco



# TAC_JMPZ
	movl	__TMP_VAR_16(%rip), %edx
	movl	$0, %eax
	cmpl	%eax, %edx 	# Se condicional anterior for 0 pula o trecho a baixo
    jz __TMP_LABEL_4


# TAC_PRINT_STRING 
    leaq	__TMP_VAR_17(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_JMP
	jmp	__TMP_LABEL_5



# TAC_LABEL
    __TMP_LABEL_4:	# AUTO



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_18(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_LABEL
    __TMP_LABEL_5:	# AUTO



# TAC_GT 
	movl	_a(%rip), %edx
	movl	_0(%rip), %eax
	cmpl	%eax, %edx 
	jg	CMP_LBL_TEMP_6 		# se condição verdadeira pula para setar 1
 	movl	$0, __TMP_VAR_19(%rip) 		# Se falsa seta 0 
	jmp	CMP_LBL_TEMP_7 		# e pula para o final do bloco

CMP_LBL_TEMP_6: 		 #se condição verdadeira seta 1
	movl	$1, __TMP_VAR_19(%rip)

CMP_LBL_TEMP_7:	#final do bloco



# TAC_JMPZ
	movl	__TMP_VAR_19(%rip), %edx
	movl	$0, %eax
	cmpl	%eax, %edx 	# Se condicional anterior for 0 pula o trecho a baixo
    jz __TMP_LABEL_6


# TAC_LABEL
    __TMP_LABEL_6:	# AUTO



## TAC_ENDFUN
	popq	%rbp
	ret



# TAC_BEGINFUN
	.text
	.globl	incn
incn:
	pushq	%rbp
	movq	%rsp, %rbp

	# TAC_DEC_FUNC_ARGS
    movl	$0, %edx

	movl	16(%rbp), %eax
	movl	%eax, _x(%rip)
	movl	24(%rbp), %eax
	movl	%eax, _n(%rip)

# TAC_ADD 
    movl	_x(%rip), %edx
    movl	_n(%rip), %eax
    addl	%edx, %eax
    movl	%eax, __TMP_VAR_20(%rip)
    movl	$0, %eax



## TAC_ENDFUN
	movl	__TMP_VAR_20(%rip), %eax #return
	popq	%rbp
	ret

