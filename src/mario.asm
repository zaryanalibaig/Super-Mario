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

    mov ax, 0x0013
    int 0x10

    ; Set video memory segment
    mov ax, 0xA000
    mov es, ax

    ; Draw first screen (columns 0-19)
    push word 0
    call drawLevel

    ; Wait for a key
    mov ah, 0
    int 0x16

    ; Return to text mode
    mov ax, 0x0003
    int 0x10

    jmp ExitToDos

ExitToDos:
    mov ax, 0x0003
    int 0x10

    mov ax, 0x4c00
    int 0x21