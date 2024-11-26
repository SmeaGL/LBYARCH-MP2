section .text
bits 64
default rel
	global asmsaxpy
	
    ; rcx -> n(length)
    ; xmm0 ->  A ( multiplier, single-precision, float)
    ; rdx = X
    ; r8  = Y
    ; r9  = Z

asmsaxpy:
    movss xmm6, xmm0
    xor rax, rax
    test rcx, rcx 
    jz .done

.loop:
    ; load original value of A
    movss xmm0, xmm6
    
    ; load X[i] to xmm1
    movss xmm1, dword [rdx + rax*4]
    
    ;  A * X[i], store result is in xmm1
    mulss xmm0, xmm1
    
    ; Load Y[i] into xmm2
    movss xmm2, dword [r8 + rax*4]
    
    ; Y[i] + (A * X[i]),store it in xmm1
    addss xmm0, xmm2
    
    ; Store result in Z[i]
    movss dword [r9 + rax*4], xmm0

    inc rax
    cmp rax, rcx
    jl .loop
    ret

.done:
    ret
