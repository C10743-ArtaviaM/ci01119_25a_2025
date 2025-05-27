section .data
msg db 'Factorial 5 is: ', 0
num db "     ", 10, 0    ; espacio para número + salto de línea

section .text
global _start

_start:
    ; Inicializar eax = 1, ebx = 1 (a=1, f=1)
    mov eax, 1     ; acumulador (resultado factorial)
    mov ecx, 1     ; contador

.loop:
    mul ecx        ; eax = eax * ecx
    inc ecx
    cmp ecx, 5     ; repetir mientras ecx <= 5
    jle .loop

    ; EAX ahora contiene 120 (5!)
    ; Convertir EAX a ASCII y guardar en buffer

    mov edi, num + 4    ; apunta al último dígito
    mov ebx, 10

.convert:
    xor edx, edx
    div ebx             ; divide eax entre 10, resultado en eax, resto en edx
    add dl, '0'         ; convierte dígito a carácter
    dec edi
    mov [edi], dl
    test eax, eax
    jnz .convert

    ; Escribir mensaje "Factorial 5 is: "
    mov eax, 4          ; syscall: write
    mov ebx, 1          ; fd: stdout
    mov ecx, msg
    mov edx, 17         ; longitud del mensaje
    int 0x80

    ; Escribir número convertido
    mov eax, 4
    mov ebx, 1
    mov ecx, edi
    mov edx, num + 5
    sub edx, ecx        ; longitud del número + \n
    int 0x80

    ; Salida limpia
    mov eax, 1          ; syscall: exit
    xor ebx, ebx
    int 0x80
