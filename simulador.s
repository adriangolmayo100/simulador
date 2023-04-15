	.file	"simulador.c"
	.text
	.comm	p_rob_cabeza,4,4
	.globl	p_rob_cola
	.bss
	.align 4
	.type	p_rob_cola, @object
	.size	p_rob_cola, 4
p_rob_cola:
	.zero	4
	.globl	PC
	.align 4
	.type	PC, @object
	.size	PC, 4
PC:
	.zero	4
	.globl	p_er_cola
	.align 8
	.type	p_er_cola, @object
	.size	p_er_cola, 12
p_er_cola:
	.zero	12
	.globl	ciclo
	.data
	.align 4
	.type	ciclo, @object
	.size	ciclo, 4
ciclo:
	.long	1
	.comm	banco_registros,256,32
	.comm	memoria_datos,128,32
	.comm	memoria_instrucciones,640,32
	.comm	UF,108,32
	.comm	ER,3840,32
	.comm	ROB,1024,32
	.comm	inst_restantes,4,4
	.globl	inst_rob
	.bss
	.align 4
	.type	inst_rob, @object
	.size	inst_rob, 4
inst_rob:
	.zero	4
	.text
	.globl	Inicializar_ER
	.type	Inicializar_ER, @function
Inicializar_ER:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L5:
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$4, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$8, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$12, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$16, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$20, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$24, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$28, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$32, %rax
	movl	$0, (%rax)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	addq	$36, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L3:
	cmpl	$31, -4(%rbp)
	jle	.L4
	addl	$1, -8(%rbp)
.L2:
	cmpl	$2, -8(%rbp)
	jle	.L5
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	Inicializar_ER, .-Inicializar_ER
	.globl	Inicializar_ROB
	.type	Inicializar_ROB, @function
Inicializar_ROB:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 4(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 8(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 12(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 16(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 20(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 24(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 28(%rax)
	addl	$1, -4(%rbp)
.L7:
	cmpl	$31, -4(%rbp)
	jle	.L8
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	Inicializar_ROB, .-Inicializar_ROB
	.globl	Inicializar_Banco_registros
	.type	Inicializar_Banco_registros, @function
Inicializar_Banco_registros:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 12(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$1, 4(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 8(%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L10:
	cmpl	$15, -4(%rbp)
	jle	.L11
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	Inicializar_Banco_registros, .-Inicializar_Banco_registros
	.globl	Inicializar_memoria_datos
	.type	Inicializar_memoria_datos, @function
Inicializar_memoria_datos:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L13
.L14:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	addl	%edx, %edx
	movl	%edx, (%rax)
	addl	$1, -4(%rbp)
.L13:
	cmpl	$31, -4(%rbp)
	jle	.L14
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	Inicializar_memoria_datos, .-Inicializar_memoria_datos
	.globl	Etapa_commit
	.type	Etapa_commit, @function
Etapa_commit:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	p_rob_cabeza(%rip), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rsi
	leaq	ROB(%rip), %rcx
	movq	(%rsi,%rcx), %rax
	movq	8(%rsi,%rcx), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	16(%rsi,%rcx), %rax
	movq	24(%rsi,%rcx), %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movl	-24(%rbp), %eax
	cmpl	$1, %eax
	jne	.L19
	movl	-4(%rbp), %eax
	cmpl	$3, %eax
	jne	.L19
	movl	-12(%rbp), %eax
	cmpl	$1, %eax
	jne	.L19
	movl	-8(%rbp), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L19
	movl	-28(%rbp), %eax
	cmpl	$4, %eax
	jne	.L17
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	memoria_datos(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	jmp	.L18
.L17:
	movl	-32(%rbp), %edx
	movl	-20(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	12+banco_registros(%rip), %rax
	movl	(%rcx,%rax), %eax
	cmpl	%eax, %edx
	jne	.L18
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	movslq	%edx, %rdx
	movq	%rdx, %rcx
	salq	$4, %rcx
	leaq	banco_registros(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
.L18:
	movl	p_rob_cabeza(%rip), %eax
	addl	$1, %eax
	movl	%eax, p_rob_cabeza(%rip)
	movl	inst_rob(%rip), %eax
	subl	$1, %eax
	movl	%eax, inst_rob(%rip)
	movl	$0, -32(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
.L19:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	Etapa_commit, .-Etapa_commit
	.globl	Etapa_WB
	.type	Etapa_WB, @function
Etapa_WB:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L21
.L30:
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$1, %eax
	jne	.L22
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	28+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$1, %eax
	jne	.L22
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	32+UF(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L22
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%ecx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	16+ROB(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	20+ROB(%rip), %rax
	movl	$1, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	ciclo(%rip), %eax
	movslq	%edx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	24+ROB(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	4+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$4, %eax
	jne	.L23
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%ecx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	12+ROB(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
.L23:
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	16+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	20+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	28+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	$1, -8(%rbp)
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	p_er_cola(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -4(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L24
.L28:
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L25
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	12+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L26
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	%eax, %ecx
	jne	.L26
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	movl	-12(%rbp), %eax
	movslq	%eax, %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$3, %rax
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	jmp	.L27
.L26:
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	24+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L25
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	20+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	%eax, %ecx
	jne	.L25
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-12(%rbp), %eax
	cltq
	movl	-16(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	20+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	movl	-12(%rbp), %eax
	movslq	%eax, %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$3, %rax
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$8, %rax
	jmp	.L27
.L25:
	addl	$1, -12(%rbp)
.L24:
	movl	-12(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jl	.L28
.L27:
	jmp	.L21
.L22:
	addl	$1, -16(%rbp)
.L21:
	cmpl	$0, -8(%rbp)
	jne	.L31
	cmpl	$2, -16(%rbp)
	jle	.L30
.L31:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	Etapa_WB, .-Etapa_WB
	.globl	Etapa_EX
	.type	Etapa_EX, @function
Etapa_EX:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movl	$0, -100(%rbp)
	jmp	.L33
.L40:
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movq	8(%rdx,%rax), %rbx
	movq	%rcx, -56(%rbp)
	movq	%rbx, -48(%rbp)
	movq	16(%rdx,%rax), %rcx
	movq	24(%rdx,%rax), %rbx
	movq	%rcx, -40(%rbp)
	movq	%rbx, -32(%rbp)
	movl	32(%rdx,%rax), %eax
	movl	%eax, -24(%rbp)
	cmpl	$0, -100(%rbp)
	jne	.L34
	movl	$2, -92(%rbp)
	jmp	.L35
.L34:
	cmpl	$1, -100(%rbp)
	jne	.L36
	movl	$3, -92(%rbp)
	jmp	.L35
.L36:
	cmpl	$2, -100(%rbp)
	jne	.L35
	movl	$5, -92(%rbp)
.L35:
	movl	-56(%rbp), %eax
	testl	%eax, %eax
	je	.L37
	movl	-52(%rbp), %eax
	cmpl	%eax, -92(%rbp)
	jle	.L38
	movl	-52(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -52(%rbp)
	jmp	.L37
.L38:
	movl	$1, -28(%rbp)
	movl	ciclo(%rip), %eax
	movl	%eax, -24(%rbp)
	cmpl	$2, -100(%rbp)
	jne	.L39
	movl	-44(%rbp), %edx
	movl	-40(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, -32(%rbp)
	jmp	.L37
.L39:
	movl	-44(%rbp), %edx
	movl	-40(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -32(%rbp)
.L37:
	addl	$1, -100(%rbp)
.L33:
	cmpl	$2, -100(%rbp)
	jle	.L40
	movl	$0, -96(%rbp)
	leaq	ER(%rip), %rax
	movq	%rax, -64(%rbp)
	movl	p_er_cola(%rip), %eax
	movl	%eax, -76(%rbp)
	movl	$0, -88(%rbp)
	jmp	.L41
.L44:
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L42
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L41
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	16(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L41
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L41
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	28(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L41
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	20(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	16+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	28+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	$-1, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	36(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	36(%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	$2, (%rdx,%rax)
	movl	$1, -96(%rbp)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	jmp	.L41
.L42:
	addl	$1, -88(%rbp)
.L41:
	cmpl	$0, -96(%rbp)
	jne	.L43
	movl	-88(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jl	.L44
.L43:
	leaq	2560+ER(%rip), %rax
	movq	%rax, -64(%rbp)
	movl	8+p_er_cola(%rip), %eax
	movl	%eax, -76(%rbp)
	movl	$0, -88(%rbp)
	jmp	.L45
.L48:
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L46
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L45
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	16(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L45
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L45
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	28(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L45
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	20(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	16+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	28+UF(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	$-1, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	36(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	36(%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	$2, (%rdx,%rax)
	movl	$1, -96(%rbp)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	jmp	.L45
.L46:
	addl	$1, -88(%rbp)
.L45:
	cmpl	$0, -96(%rbp)
	jne	.L47
	movl	-88(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jl	.L48
.L47:
	cmpl	$0, -96(%rbp)
	jne	.L49
	cmpl	$1, -100(%rbp)
	jne	.L49
	leaq	1280+ER(%rip), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movl	4(%rax), %eax
	cmpl	$4, %eax
	jne	.L49
	movq	-64(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L49
	movq	-64(%rbp), %rax
	movl	16(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L49
	movq	-64(%rbp), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L49
	movq	-64(%rbp), %rax
	movl	28(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L49
	movq	-64(%rbp), %rax
	movl	8(%rax), %edx
	movq	-64(%rbp), %rax
	movl	32(%rax), %eax
	addl	%edx, %eax
	movl	%eax, -72(%rbp)
	movq	-64(%rbp), %rax
	movl	20(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rcx
	leaq	4+UF(%rip), %rdx
	movl	-92(%rbp), %eax
	movl	%eax, (%rcx,%rdx)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movq	-64(%rbp), %rax
	movl	36(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movq	-64(%rbp), %rax
	movl	36(%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	$2, (%rdx,%rax)
	movl	$1, -96(%rbp)
	movq	-64(%rbp), %rax
	movl	$0, (%rax)
.L49:
	cmpl	$0, -96(%rbp)
	jne	.L56
	cmpl	$1, -100(%rbp)
	jne	.L56
	leaq	1280+ER(%rip), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movl	4(%rax), %eax
	cmpl	$3, %eax
	jne	.L56
	movq	-64(%rbp), %rax
	movl	12(%rax), %eax
	testl	%eax, %eax
	je	.L56
	movq	-64(%rbp), %rax
	movl	16(%rax), %edx
	movl	ciclo(%rip), %eax
	cmpl	%eax, %edx
	jge	.L56
	movq	-64(%rbp), %rax
	movl	8(%rax), %edx
	movq	-64(%rbp), %rax
	movl	32(%rax), %eax
	addl	%edx, %eax
	movl	%eax, -68(%rbp)
	movl	$0, -84(%rbp)
	movl	$0, -80(%rbp)
	jmp	.L51
.L53:
	movl	-80(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	4+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$4, %eax
	jne	.L52
	addl	$1, -84(%rbp)
.L52:
	addl	$1, -80(%rbp)
.L51:
	cmpl	$31, -80(%rbp)
	jle	.L53
	cmpl	$0, -84(%rbp)
	je	.L54
	movl	-80(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rcx
	leaq	4+UF(%rip), %rdx
	movl	-92(%rbp), %eax
	movl	%eax, (%rcx,%rdx)
	jmp	.L55
.L54:
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+UF(%rip), %rax
	movl	$1, (%rdx,%rax)
.L55:
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	$1, (%rdx,%rax)
	movq	-64(%rbp), %rax
	movl	36(%rax), %ecx
	movl	-100(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movq	-64(%rbp), %rax
	movl	36(%rax), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	$2, (%rdx,%rax)
	movl	$1, -96(%rbp)
	movq	-64(%rbp), %rax
	movl	$0, (%rax)
.L56:
	nop
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	Etapa_EX, .-Etapa_EX
	.globl	Etapa_ID_ISS
	.type	Etapa_ID_ISS, @function
Etapa_ID_ISS:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	inst_restantes(%rip), %eax
	testl	%eax, %eax
	jle	.L73
	movl	PC(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, PC(%rip)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rsi
	leaq	memoria_instrucciones(%rip), %rcx
	movq	(%rsi,%rcx), %rax
	movq	8(%rsi,%rcx), %rdx
	movq	%rax, -120(%rbp)
	movq	%rdx, -112(%rbp)
	movl	16(%rsi,%rcx), %eax
	movl	%eax, -104(%rbp)
	movl	p_rob_cola(%rip), %eax
	movl	%eax, -88(%rbp)
	movl	-120(%rbp), %eax
	movl	%eax, -84(%rbp)
	movl	$1, -80(%rbp)
	movl	-116(%rbp), %eax
	movl	%eax, -76(%rbp)
	movl	$0, -72(%rbp)
	movl	$0, -68(%rbp)
	movl	$0, -64(%rbp)
	movl	$0, -60(%rbp)
	movl	p_rob_cola(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, p_rob_cola(%rip)
	cltq
	salq	$5, %rax
	movq	%rax, %rsi
	leaq	ROB(%rip), %rcx
	movq	-88(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rax, (%rsi,%rcx)
	movq	%rdx, 8(%rsi,%rcx)
	movq	-72(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rax, 16(%rsi,%rcx)
	movq	%rdx, 24(%rsi,%rcx)
	movl	inst_rob(%rip), %eax
	addl	$1, %eax
	movl	%eax, inst_rob(%rip)
	movl	-120(%rbp), %eax
	cmpl	$1, %eax
	je	.L59
	movl	-120(%rbp), %eax
	cmpl	$2, %eax
	jne	.L60
.L59:
	movl	$0, -140(%rbp)
	jmp	.L61
.L60:
	movl	-120(%rbp), %eax
	cmpl	$5, %eax
	jne	.L62
	movl	$2, -140(%rbp)
	jmp	.L61
.L62:
	movl	$1, -140(%rbp)
.L61:
	movl	-140(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	p_er_cola(%rip), %rax
	movl	(%rdx,%rax), %eax
	leal	1(%rax), %edx
	movl	-140(%rbp), %ecx
	movslq	%ecx, %rcx
	leaq	0(,%rcx,4), %rsi
	leaq	p_er_cola(%rip), %rcx
	movl	%edx, (%rsi,%rcx)
	movl	%eax, -136(%rbp)
	movl	$1, -56(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -28(%rbp)
	movl	-104(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-88(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	ER(%rip), %rax
	addq	%rdx, %rax
	movq	-56(%rbp), %rcx
	movq	-48(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-24(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movl	-120(%rbp), %eax
	cmpl	$3, %eax
	jne	.L63
	movl	-108(%rbp), %eax
	movl	%eax, -76(%rbp)
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	4+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L64
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	banco_registros(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L65
.L64:
	movl	-108(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	12+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -124(%rbp)
	movl	-124(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	20+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L66
	movl	-124(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L65
.L66:
	movl	-124(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	12+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	movl	-124(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	16+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L65
.L63:
	movl	-120(%rbp), %eax
	cmpl	$4, %eax
	je	.L67
	movl	-116(%rbp), %eax
	movl	%eax, -76(%rbp)
.L67:
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	4+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L68
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	banco_registros(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L69
.L68:
	movl	-108(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	12+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -132(%rbp)
	movl	-132(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	20+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L70
	movl	-132(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L69
.L70:
	movl	-132(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	12+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	movl	-132(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	16+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
.L69:
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	4+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L71
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	banco_registros(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L65
.L71:
	movl	-112(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	12+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, -128(%rbp)
	movl	-128(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	20+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L72
	movl	-128(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	20+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	jmp	.L65
.L72:
	movl	-128(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	24+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
	movl	-128(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	24+ROB(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-136(%rbp), %eax
	cltq
	movl	-140(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	28+ER(%rip), %rax
	addq	%rdx, %rax
	movl	%esi, (%rax)
.L65:
	movl	inst_restantes(%rip), %eax
	subl	$1, %eax
	movl	%eax, inst_restantes(%rip)
.L73:
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	Etapa_ID_ISS, .-Etapa_ID_ISS
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"file.txt"
.LC2:
	.string	"\n"
.LC3:
	.string	" "
.LC4:
	.string	"ld"
.LC5:
	.string	"sd"
.LC6:
	.string	","
.LC7:
	.string	"("
.LC8:
	.string	"fadd"
.LC9:
	.string	"fsub"
.LC10:
	.string	"fmult"
	.text
	.globl	Carga_programa
	.type	Carga_programa, @function
Carga_programa:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -168(%rbp)
	movl	$0, -204(%rbp)
	jmp	.L75
.L86:
	leaq	-48(%rbp), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -152(%rbp)
	leaq	.LC3(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -144(%rbp)
	movl	$-1, -200(%rbp)
	movq	-152(%rbp), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	movl	%eax, -196(%rbp)
	cmpl	$0, -196(%rbp)
	je	.L76
	movq	-152(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L77
.L76:
	cmpl	$0, -196(%rbp)
	jne	.L78
	movl	$3, -200(%rbp)
	jmp	.L79
.L78:
	movl	$4, -200(%rbp)
.L79:
	movq	-144(%rbp), %rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -112(%rbp)
	leaq	.LC6(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	leaq	.LC7(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -96(%rbp)
	leaq	.LC7(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -88(%rbp)
	movq	-112(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -180(%rbp)
	movq	-88(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -176(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -172(%rbp)
	movl	$-1, -76(%rbp)
	movl	-176(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	-180(%rbp), %eax
	movl	%eax, -68(%rbp)
	movl	-172(%rbp), %eax
	movl	%eax, -64(%rbp)
	jmp	.L80
.L77:
	movq	-152(%rbp), %rax
	leaq	.LC8(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L81
	movl	$1, -200(%rbp)
	jmp	.L82
.L81:
	movq	-152(%rbp), %rax
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L83
	movl	$2, -200(%rbp)
	jmp	.L82
.L83:
	movq	-152(%rbp), %rax
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L82
	movl	$5, -200(%rbp)
.L82:
	movq	-144(%rbp), %rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	strtok@PLT
	movq	%rax, -136(%rbp)
	leaq	.LC6(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -128(%rbp)
	leaq	.LC6(%rip), %rsi
	movl	$0, %edi
	call	strtok@PLT
	movq	%rax, -120(%rbp)
	movq	-136(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -192(%rbp)
	movq	-128(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -188(%rbp)
	movq	-120(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -184(%rbp)
	movl	-192(%rbp), %eax
	movl	%eax, -76(%rbp)
	movl	-188(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	-184(%rbp), %eax
	movl	%eax, -68(%rbp)
	movl	$0, -64(%rbp)
.L80:
	movl	-200(%rbp), %eax
	movl	%eax, -80(%rbp)
	movl	-204(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -204(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rsi
	leaq	memoria_instrucciones(%rip), %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rsi,%rcx)
	movq	%rdx, 8(%rsi,%rcx)
	movl	-64(%rbp), %eax
	movl	%eax, 16(%rsi,%rcx)
	cmpl	$32, -204(%rbp)
	je	.L89
.L75:
	movq	-168(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	testq	%rax, %rax
	jne	.L86
	jmp	.L85
.L89:
	nop
.L85:
	movl	-204(%rbp), %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L88
	call	__stack_chk_fail@PLT
.L88:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	Carga_programa, .-Carga_programa
	.section	.rodata
	.align 8
.LC11:
	.string	"+------+-----+----+----+----+-----+"
	.align 8
.LC12:
	.string	"| INST | COD | RT | RS | RD | INM |"
	.align 8
.LC13:
	.string	"| %4d | %3d | %2d | %2d | %2d | %3d |\n"
	.text
	.globl	imprime_memoria_inst
	.type	imprime_memoria_inst, @function
imprime_memoria_inst:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L91
.L92:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	16+memoria_instrucciones(%rip), %rax
	movl	(%rdx,%rax), %edi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+memoria_instrucciones(%rip), %rax
	movl	(%rdx,%rax), %r9d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+memoria_instrucciones(%rip), %rax
	movl	(%rdx,%rax), %r8d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+memoria_instrucciones(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	memoria_instrucciones(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	-4(%rbp), %edx
	leal	1(%rdx), %esi
	subq	$8, %rsp
	pushq	%rdi
	movl	%eax, %edx
	leaq	.LC13(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	addl	$1, -4(%rbp)
.L91:
	cmpl	$5, -4(%rbp)
	jle	.L92
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	imprime_memoria_inst, .-imprime_memoria_inst
	.section	.rodata
.LC14:
	.string	"+---------------------+"
.LC15:
	.string	"| MEMORIA DE DATOS     |"
.LC16:
	.string	"| [%2d]  |  %8d |\n"
	.text
	.globl	imprime_memoria_datos
	.type	imprime_memoria_datos, @function
imprime_memoria_datos:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	leaq	.LC15(%rip), %rdi
	call	puts@PLT
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L94
.L95:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	memoria_datos(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L94:
	cmpl	$31, -4(%rbp)
	jle	.L95
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	imprime_memoria_datos, .-imprime_memoria_datos
	.section	.rodata
	.align 8
.LC17:
	.string	"+-----+------+-------------+---------+-------+-------------+-------+----------+"
	.align 8
.LC18:
	.string	"| TAG | BUSY | CLK_TICK_OK | DESTINO | ETAPA | INSTRUCCION | VALOR | VALOR_OK |"
.LC19:
	.string	"W"
.LC20:
	.string	"-1"
.LC21:
	.string	"E"
.LC22:
	.string	"I"
	.align 8
.LC23:
	.string	"| %3d | %4d | %11d | %7d | %5s | %11d | %5d | %8d |\n"
	.text
	.globl	imprime_rob
	.type	imprime_rob, @function
imprime_rob:
.LFB17:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC17(%rip), %rdi
	call	puts@PLT
	leaq	.LC18(%rip), %rdi
	call	puts@PLT
	leaq	.LC17(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L97
.L104:
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	20+ROB(%rip), %rax
	movl	(%rdx,%rax), %r9d
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	16+ROB(%rip), %rax
	movl	(%rdx,%rax), %r8d
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	4+ROB(%rip), %rax
	movl	(%rdx,%rax), %edi
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$1, %eax
	je	.L98
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$2, %eax
	je	.L99
	movl	-4(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	28+ROB(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$3, %eax
	jne	.L100
	leaq	.LC19(%rip), %rax
	jmp	.L103
.L100:
	leaq	.LC20(%rip), %rax
	jmp	.L103
.L99:
	leaq	.LC21(%rip), %rax
	jmp	.L103
.L98:
	leaq	.LC22(%rip), %rax
.L103:
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	12+ROB(%rip), %rdx
	movl	(%rcx,%rdx), %r11d
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rdx, %rcx
	salq	$5, %rcx
	leaq	24+ROB(%rip), %rdx
	movl	(%rcx,%rdx), %ecx
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rdx, %rsi
	salq	$5, %rsi
	leaq	8+ROB(%rip), %rdx
	movl	(%rsi,%rdx), %edx
	movl	-4(%rbp), %esi
	movslq	%esi, %rsi
	salq	$5, %rsi
	movq	%rsi, %r10
	leaq	ROB(%rip), %rsi
	movl	(%r10,%rsi), %esi
	subq	$8, %rsp
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movq	%rax, %r9
	movl	%r11d, %r8d
	leaq	.LC23(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$32, %rsp
	addl	$1, -4(%rbp)
.L97:
	movl	inst_restantes(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L104
	leaq	.LC17(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	imprime_rob, .-imprime_rob
	.section	.rodata
	.align 8
.LC24:
	.string	"+------------------------------------------------------------------------------"
	.align 8
.LC25:
	.string	"|Estacion %d                                                                   |\n"
	.align 8
.LC26:
	.string	"+---------+----+------+-----+---------+-----+---------+--------+--------+-----+"
	.align 8
.LC27:
	.string	"| TAG_ROB | OP | BUSY | OpA | CLK_OpA | OpB | CLK_OpB | opb_Q | opb_Q | INM |"
	.align 8
.LC28:
	.string	"| %7d | %2d | %4d | %3d | %7d | %3d | %7d | %6d | %6d | %3d |\n"
	.text
	.globl	imprime_ER
	.type	imprime_ER, @function
imprime_ER:
.LFB18:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movl	$0, -40(%rbp)
	jmp	.L106
.L109:
	leaq	.LC24(%rip), %rdi
	call	puts@PLT
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC25(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC26(%rip), %rdi
	call	puts@PLT
	leaq	.LC27(%rip), %rdi
	call	puts@PLT
	leaq	.LC26(%rip), %rdi
	call	puts@PLT
	movl	$0, -36(%rbp)
	jmp	.L107
.L108:
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	32+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %ebx
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	24+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r11d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	12+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r10d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	28+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r9d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	20+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r8d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	16+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r13d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	8+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %r12d
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %edi
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	4+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %esi
	movl	-36(%rbp), %eax
	cltq
	movl	-40(%rbp), %edx
	movslq	%edx, %rcx
	movq	%rax, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	leaq	0(,%rdx,8), %rax
	movq	%rax, %rdx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$8, %rax
	addq	%rax, %rdx
	leaq	36+ER(%rip), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	subq	$8, %rsp
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	movl	%r13d, %r9d
	movl	%r12d, %r8d
	movl	%edi, %ecx
	movl	%esi, %edx
	movl	%eax, %esi
	leaq	.LC28(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$48, %rsp
	addl	$1, -36(%rbp)
.L107:
	movl	inst_restantes(%rip), %eax
	cmpl	%eax, -36(%rbp)
	jl	.L108
	leaq	.LC26(%rip), %rdi
	call	puts@PLT
	addl	$1, -40(%rbp)
.L106:
	cmpl	$2, -40(%rbp)
	jle	.L109
	nop
	nop
	leaq	-24(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	imprime_ER, .-imprime_ER
	.section	.rodata
	.align 8
.LC29:
	.string	"+---------+-----+----------+-------------+-----+-----+-----+--------+"
	.align 8
.LC30:
	.string	"| TAG_ROB | USO | OPERACION | CONT_CICLOS  | OpA | OpB | RES | RES_OK |"
	.align 8
.LC31:
	.string	"| %7d | %3d | %8d | %11d | %3d | %3d | %3d | %6d |\n"
	.text
	.globl	imprime_UF
	.type	imprime_UF, @function
imprime_UF:
.LFB19:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC29(%rip), %rdi
	call	puts@PLT
	leaq	.LC30(%rip), %rdi
	call	puts@PLT
	leaq	.LC29(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L111
.L112:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	28+UF(%rip), %rax
	movl	(%rdx,%rax), %r9d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	24+UF(%rip), %rax
	movl	(%rdx,%rax), %r8d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	16+UF(%rip), %rax
	movl	(%rdx,%rax), %edi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	12+UF(%rip), %rax
	movl	(%rdx,%rax), %r11d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	4+UF(%rip), %rax
	movl	(%rdx,%rax), %r10d
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	20+UF(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	UF(%rip), %rax
	movl	(%rdx,%rax), %esi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	8+UF(%rip), %rax
	movl	(%rdx,%rax), %eax
	subq	$8, %rsp
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movl	%r11d, %r9d
	movl	%r10d, %r8d
	movl	%esi, %edx
	movl	%eax, %esi
	leaq	.LC31(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$32, %rsp
	addl	$1, -4(%rbp)
.L111:
	cmpl	$2, -4(%rbp)
	jle	.L112
	leaq	.LC29(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	imprime_UF, .-imprime_UF
	.section	.rodata
	.align 8
.LC32:
	.string	"+---------+-----+--------+-----------+"
	.align 8
.LC33:
	.string	"| TAG_ROB | OK  | CLK_OK | CONTENIDO |"
.LC34:
	.string	"| %7d | %3d | %6d | %9d |\n"
	.text
	.globl	imprime_Banco_registros
	.type	imprime_Banco_registros, @function
imprime_Banco_registros:
.LFB20:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC32(%rip), %rdi
	call	puts@PLT
	leaq	.LC33(%rip), %rdi
	call	puts@PLT
	leaq	.LC32(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L114
.L115:
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	banco_registros(%rip), %rax
	movl	(%rdx,%rax), %edi
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	8+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %ecx
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	4+banco_registros(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rsi
	leaq	12+banco_registros(%rip), %rax
	movl	(%rsi,%rax), %eax
	movl	%edi, %r8d
	movl	%eax, %esi
	leaq	.LC34(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L114:
	cmpl	$15, -4(%rbp)
	jle	.L115
	leaq	.LC32(%rip), %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	imprime_Banco_registros, .-imprime_Banco_registros
	.section	.rodata
.LC35:
	.string	"Ciclo%d>\n"
.LC36:
	.string	"Memoria Instrucciones"
.LC37:
	.string	"Memoria Datos"
.LC38:
	.string	"ROB"
.LC39:
	.string	"ER"
.LC40:
	.string	"UF"
.LC41:
	.string	"Banco de registros"
.LC42:
	.string	"\n\n"
	.text
	.globl	imprimeCPU
	.type	imprimeCPU, @function
imprimeCPU:
.LFB21:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	ciclo(%rip), %eax
	movl	%eax, %esi
	leaq	.LC35(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC36(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_memoria_inst
	leaq	.LC37(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_memoria_datos
	leaq	.LC38(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_rob
	leaq	.LC39(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_ER
	leaq	.LC40(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_UF
	leaq	.LC41(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	call	imprime_Banco_registros
	leaq	.LC42(%rip), %rdi
	call	puts@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	imprimeCPU, .-imprimeCPU
	.section	.rodata
.LC43:
	.string	"Inst ROB: %d, Inst prog: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	call	Carga_programa
	movl	%eax, inst_restantes(%rip)
	leaq	ER(%rip), %rdi
	call	Inicializar_ER
	leaq	ROB(%rip), %rdi
	call	Inicializar_ROB
	leaq	banco_registros(%rip), %rdi
	call	Inicializar_Banco_registros
	leaq	memoria_datos(%rip), %rdi
	call	Inicializar_memoria_datos
	jmp	.L118
.L119:
	movl	$0, %eax
	call	Etapa_commit
	movl	$0, %eax
	call	Etapa_WB
	movl	$0, %eax
	call	Etapa_EX
	movl	$0, %eax
	call	Etapa_ID_ISS
	movl	$0, %eax
	call	imprimeCPU
	movl	ciclo(%rip), %eax
	addl	$1, %eax
	movl	%eax, ciclo(%rip)
	movl	inst_restantes(%rip), %edx
	movl	inst_rob(%rip), %eax
	movl	%eax, %esi
	leaq	.LC43(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L118:
	movl	inst_rob(%rip), %eax
	testl	%eax, %eax
	jg	.L119
	movl	inst_restantes(%rip), %eax
	testl	%eax, %eax
	jg	.L119
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
