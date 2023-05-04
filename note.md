

```
asm volatile(
                "pushq %rbx\n\t"
                "pushq %rsi\n\t"
                "pushq %rdi\n\t"
                "movq  %rsp, (%rdi)\n\t"
                "movq  %rsi, %rsp\n\t"
                "popq %rdi\n\t"
                "popq %rsi\n\t"
                "popq %rbx\n\t"
                );

```
generate to
```
uco::swtch(uco::Context**, uco::Context*):
	push   %rbp
	mov    %rsp,%rbp
	mov    %rdi,-0x8(%rbp)
	mov    %rsi,-0x10(%rbp)
	push   %rbx
	push   %rsi
	push   %rdi
	mov    %rsp,(%rdi)
	mov    %rsi,%rsp
	pop    %rdi
	pop    %rsi
	pop    %rbx
	nop
	pop    %rbp
	ret

```




```
__asm__ __volatile__(
                "pushl %%ebx\n\t"
                "pushl %%esi\n\t"
                "pushl %%edi\n\t"
                "movl %%esp, (%0)\n\t"
                "movl %1, %%esp\n\t"
                "popl %%edi\n\t"
                "popl %%esi\n\t"
                "popl %%ebx\n\t"
                :
                : "r" (old_context), "r" (new_context)
                :
                );

```


call instruction before:
```

(gdb) x/8xb $rsi
0x55555556ee90:	0x00	0x00	0x00	0x00	0x00	0x00	0x00	0x00

(gdb) x/8xb $rdi
0x55555555a0f8 <scheduler+24>:	0x00	0x00	0x00	0x00	0x00	0x00	0x00	0x00

```
```
version 2 asm
uco::swtch(uco::Context**, uco::Context*):
	push   %rbp
	mov    %rsp,%rbp
	mov    %rdi,-0x8(%rbp)
	mov    %rsi,-0x10(%rbp)
	mov    -0x8(%rbp),%rax
	mov    -0x10(%rbp),%rdx
	push   %rbx
	push   %rsi
	push   %rdi
	mov    %rsp,(%rax)
	mov    %rdx,%rsp
	pop    %rdi
	pop    %rsi
	pop    %rbx
	nop
	pop    %rbp
	ret
```
```
	mov    -0x8(%rbp),%rax
	mov    -0x10(%rbp),%rdx
later:

print %rax and %rdx

(gdb) x/8xb $rax
0x55555555a0f8 <scheduler+24>:	0x00	0x00	0x00	0x00	0x00	0x00	0x00	0x00

(gdb) x/8xb $rdx
0x55555556ee90:	0x00	0x00	0x00	0x00	0x00	0x00	0x00	0x00

```
