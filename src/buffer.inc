; Name:      alloc_buffer
; Purpose:   shrink our own memory block to 64 KB, then ask DOS for a second
;            block of 64,000 bytes to use as the off-screen frame buffer.
; Inputs:    none (DS = CS)
; Outputs:   [frame_seg] = segment of the buffer when CF = 0
;            CF = 1 if either DOS call failed
; Registers: AX and BX changed; ES is saved and restored
alloc_buffer:
    push es

    mov ax, cs
    mov es, ax                      ; function 4Ah needs ES = our own block
    mov bx, PROGRAM_PARAGRAPHS
    mov ah, 4Ah
    int 21h
    jc .done

    mov bx, BUFFER_PARAGRAPHS
    mov ah, 48h
    int 21h
    jc .done
    mov [frame_seg], ax

.done:
    pop es
    ret


; Name:      clear_buffer
; Purpose:   fill the whole frame buffer with one colour using a block store rep stosw
; Inputs:    AL = colour index
; Outputs:   none 
; Registers: none changed but the direction flag is cleared
clear_buffer:
    push ax
    push cx
    push di
    push es

    mov ah, al
    mov es, [frame_seg]
    xor di, di
    mov cx, BUFFER_WORDS
    cld
    rep stosw

    pop es
    pop di
    pop cx
    pop ax
    ret


; Name:      present_buffer
; Purpose:   copy the finished frame from the buffer to video memory with movsw
; Inputs:    none
; Outputs:   none
; Registers: none changed but the direction flag is cleared
present_buffer:
    push ax
    push cx
    push si
    push di
    push ds
    push es

    mov ax, [frame_seg]
    mov ds, ax
    mov ax, VIDEO_SEGMENT
    mov es, ax
    xor si, si
    xor di, di
    mov cx, BUFFER_WORDS
    cld
    rep movsw

    pop es
    pop ds
    pop di
    pop si
    pop cx
    pop ax
    ret


; Name:      wait_retrace
; Purpose:   wait for the start of the next vertical retrace so each frame is
;            drawn once per screen refresh.
; Inputs:    none
; Outputs:   none
; Registers: none changed
wait_retrace:
    push ax
    push dx

    mov dx, 3DAh                    ; VGA input status register 1
.wait_for_end:
    in al, dx
    test al, 8
    jnz .wait_for_end
.wait_for_start:
    in al, dx
    test al, 8
    jz .wait_for_start

    pop dx
    pop ax
    ret