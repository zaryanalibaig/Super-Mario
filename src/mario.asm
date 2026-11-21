bits 16
org 0x0100

jmp start

    %include "constants.inc"
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

    mov ax, TEXT_MODE_03H
    int 10h



    jmp ExitToDOS

ExitToDos:
    mov ax, 0x0003
    int 0x10

    mov ax, 0x4c00
    int 0x21