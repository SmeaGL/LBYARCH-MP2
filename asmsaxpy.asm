section .text
bits 64
default rel
global asmsaxpy

; rcx -> n (length)
; xmm0 -> A (scalar multiplier, single-precision float)
; rdx -> Address of X
; r8  -> Address of Y
; r9  -> Address of Z

asmsaxpy:
.loop:
    test rcx, rcx          ; Check if n == 0
    jz .done               ; Exit if n == 0

    movss xmm1, dword [rdx]    
    mulss xmm1, xmm0           
    movss xmm2, dword [r8]    
    addss xmm1, xmm2          
    movss dword [r9], xmm1     

    add rdx, 4                 
    add r8, 4                  
    add r9, 4                  

    dec rcx
    jmp .loop                 

.done:
    ret
