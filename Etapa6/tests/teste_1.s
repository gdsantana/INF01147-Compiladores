	.data
__TMP_VAR_11: .string	"input1 - input2 = "
__TMP_VAR_4: .long	0
_0: .long	0
__TMP_VAR_15: .string	"\n"
__TMP_VAR_3: .string	"\n"
__TMP_VAR_19: .string	"\n"
_input__dash__one: .long	0
__TMP_VAR_2: .string	"Enter the first value: "
__TMP_VAR_1: .string	"Atribuições e operações aritmeticas com impressão:  [read, +, -, *, /] \n"
__TMP_VAR_12: .string	"\n"
__TMP_VAR_0: .string	"Teste 1:"
__TMP_VAR_16: .long	0
__TMP_VAR_13: .long	0
__TMP_VAR_17: .string	"\n"
__TMP_VAR_9: .string	"\n"
_input__dash__two: .long	0
__TMP_VAR_8: .string	"input1 + input2 = "
_result: .long	0
__TMP_VAR_10: .long	0
__TMP_VAR_7: .long	0
__TMP_VAR_14: .string	"input1 * input2 = "
__TMP_VAR_6: .long	0
__TMP_VAR_18: .string	"input1 / input2 = "
__TMP_VAR_5: .string	"Enter the second value: "

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



# TAC_BEGINFUN
	.text
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp


# TAC_PRINT_STRING 
    leaq	__TMP_VAR_0(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_1(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_3(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_2(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_READ
	leaq	__TMP_VAR_4(%rip), %rsi
	leaq	read(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT

# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_4(%rip), %eax
    movl	%eax, _input__dash__one(%rip)
    movl	$0, %eax




# TAC_PRINT_STRING 
    leaq	__TMP_VAR_5(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_READ
	leaq	__TMP_VAR_6(%rip), %rsi
	leaq	read(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT

# TAC_MOVE //ASSIGN 
    movl	__TMP_VAR_6(%rip), %eax
    movl	%eax, _input__dash__two(%rip)
    movl	$0, %eax




# TAC_PRINT_STRING 
    leaq	__TMP_VAR_9(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_8(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_ADD 
    movl	_input__dash__one(%rip), %edx
    movl	_input__dash__two(%rip), %eax
    addl	%edx, %eax
    movl	%eax, __TMP_VAR_7(%rip)
    movl	$0, %eax



# TAC_PRINT_INT 
    movl	__TMP_VAR_7(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_12(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_11(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_SUB 
    movl	_input__dash__one(%rip), %edx
    movl	_input__dash__two(%rip), %eax
    subl	%eax, %edx
    movl	%edx, %eax
    movl	%eax, __TMP_VAR_10(%rip)
    movl	$0, %eax



# TAC_PRINT_INT 
    movl	__TMP_VAR_10(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_15(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_14(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_MULT 
    movl	_input__dash__one(%rip), %edx
    movl	_input__dash__two(%rip), %eax
    imull	%edx, %eax
    movl	%eax, __TMP_VAR_13(%rip)
    movl	$0, %eax



# TAC_PRINT_INT 
    movl	__TMP_VAR_13(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_19(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_18(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



# TAC_DIV
    movl	_input__dash__one(%rip), %eax
    movl	_input__dash__two(%rip), %ecx
            cltd
    idivl	%ecx
    movl	%eax, __TMP_VAR_16(%rip)
    movl	$0, %eax




# TAC_PRINT_INT 
    movl	__TMP_VAR_16(%rip), %esi   # mov a to reg
    #movl	%eax, %esi
    leaq	print_string_int(%rip), %rdi
	call	printf@PLT



# TAC_PRINT_STRING 
    leaq	__TMP_VAR_17(%rip), %rdi
    movl	$0, %eax
    call	printf@PLT
    movl	$0, %eax



## TAC_ENDFUN
	popq	%rbp
	ret

