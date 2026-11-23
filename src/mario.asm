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

    call Validate_map
    mov ax, 0x0013              ; VGA mode 13h
    int 0x10
    mov ax, 0xA000
    mov es, ax
    xor si, si                  ; SI = colour number 0..15
    mov bx, 64                  ; BX = x of the first stripe
colour_test_loop:
    push bx                     ; x
    push word 80                ; y
    push word 12                ; width
    push word 40                ; height
    push si                     ; colour = stripe number
    call fill_rect
    add bx, 12                  ; next stripe to the right
    inc si
    cmp si, 16
    jb colour_test_loop

    mov ah, 0
    int 0x16                    ; wait for a key

    mov ax, 0x0013
    int 0x10
    mov ax, 0xA000
    mov es, ax

    call reset_map
    mov byte [working_map+ 6*60 +45],5 ; changed the working map for testing 
    
    push word 40
    call drawLevel
    ; Wait for a key
    mov ah, 0
    int 0x16

    call reset_map
    push word 40
    call drawLevel


    ; Wait for a key
    mov ah, 0
    int 0x16


    jmp ExitToDos

ExitToDos:
    mov ax, 0x0003
    int 0x10

    mov ax, 0x4c00
    int 0x21