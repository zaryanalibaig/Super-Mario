bits 16
org 0x0100

jmp start

    %include "consta~1.inc"
    %include "data.inc"
    %include "video.inc"
    %include "level.inc"
    %include "macros.inc"

start:
    ; Initialize segment registers.
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0FFFEh

    cld

    mov ax, 0013h
    int 10h
    mov ax,0A000h
    mov es,ax
    push word 10
    push word 10
    push word 30h
    push word 40h
    push word 0015h
    call fill_rect
    xor ah,ah
    int 16h


    mov ax, 0003h
    int 10h



    jmp ExitToDos

ExitToDos:
    mov ax, 0x0003
    int 0x10

    mov ax, 0x4c00
    int 0x21