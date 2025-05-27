section .data
buffer db "Resultado: ", 0
numstr db "     ", 10, 0  ; espacio para número + salto de línea

section .text
global _start

_start:
    push 5
    call fibonacci
    add esp, 4

    ; EAX ahora tiene el resultado (ej: 8)
    ; Convertir a string decimal
    mov edi, numstr + 4     ; apuntar al final del buffer (antes del \n)
    mov ecx, 0              ; contador de dígitos

.to_ascii:
    xor edx, edx
    mov ebx, 10
    div ebx                 ; divide EAX entre 10, resultado en EAX, resto en EDX
    add dl, '0'             ; convierte dígito a ASCII
    dec edi
    mov [edi], dl
    inc ecx
    test eax, eax
    jnz .to_ascii

    ; Escribir el texto "Resultado: "
    mov eax, 4              ; syscall: sys_write
    mov ebx, 1              ; fd: stdout
    mov ecx, buffer         ; mensaje
    mov edx, 10             ; longitud
    int 0x80

    ; Escribir el número
    mov eax, 4              ; syscall: sys_write
    mov ebx, 1              ; fd: stdout
    mov ecx, edi            ; apunta al número convertido
    mov edx, ecx
    mov esi, numstr + 5
    sub edx, edi            ; longitud = numstr+5 - edi
    add edx, 1              ; incluye el salto de línea
    int 0x80

    ; Salir
    mov eax, 1              ; syscall: sys_exit
    xor ebx, ebx
    int 0x80

; -------------------------
; Fibonacci recursivo
; -------------------------
fibonacci:
    push ebp
    mov ebp, esp

    mov ecx, [ebp + 8]      ; ecx = n
    cmp ecx, 1
    jle .base_case

    mov eax, ecx
    dec eax
    push eax
    call fibonacci
    add esp, 4
    mov esi, eax            ; fib(n-1)

    mov eax, ecx
    sub eax, 2
    push eax
    call fibonacci
    add esp, 4

    add eax, esi            ; fib(n-1) + fib(n-2)
    jmp .end

.base_case:
    mov eax, 1

.end:
    pop ebp
    ret

