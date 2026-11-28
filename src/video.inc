; putpixel with parameters color, y(rows), x(cols)

putpixel:
    push bp
    mov bp, sp

    push ax
    push bx
    push cx
    push di

    mov cx, [bp+4]
    mov ax, [bp+6]
    mov bx, ax
    shl ax, 8

    shl bx, 6
    add bx, ax

    mov ax, [bp+8]
    add bx, ax

    mov di, bx
    mov [es:di], cl

    pop di
    pop cx
    pop bx
    pop ax
    pop bp

    ret 6
; Name:      fill_rect
; Purpose:   fill a solid rectangle with one colour in the segment ES points at
; Inputs:    stack: x [bp+12], y [bp+10], width [bp+8], height [bp+6], colour [bp+4]
;            ES = segment to draw into
; Outputs:   none
; Registers: none chnaged

fill_rect:
    push bp
    mov bp, sp

    push ax
    push bx
    push cx
    push dx
    push di

    mov bx, [bp+6]      ; height
    test bx, bx
    jz .done            ; nothing to draw

    mov ax, [bp+10]     ; y
    mov di, ax
    shl ax, 8           ; y*256
    shl di, 6           ; y*64
    add di, ax          ; y*320
    add di, [bp+12]     ; + x

    mov dx, 320
    sub dx, [bp+8]      ; 320 - width

    mov al, [bp+4]
    cld

.row_loop:
    mov cx, [bp+8]
    rep stosb
    add di, dx
    dec bx
    jnz .row_loop

.done:
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop bp
    ret 10


; cols at bp+8, rows at bp+6, color code at bp+4
; This function draws a tile using fill_rect.
; No output returned; registers used are preserved.

drawtile:
    push bp
    mov bp, sp

    push ax
    push bx
    push cx

    ; Calculate pixel X

    mov ax, [bp+8]
    shl ax, 4
    push ax

    ; Calculate pixel Y

    mov ax, [bp+6]
    shl ax, 4
    push ax

    mov cx, 16
    push cx
    push cx

    ; Calculate the color using the provided tile code

    mov bx, [bp+4]
    mov al, [tile_colours+bx]
    xor ah, ah
    push ax

    call fill_rect

    pop cx
    pop bx
    pop ax
    pop bp

    ret 6


; Name: drawLevel
; Purpose: Draw 20 visible columns of the level
; Inputs: first_column at [bp+4]
; Outputs: None
; Registers: Preserves all registers used

drawLevel:
    push bp
    mov bp, sp

    push ax
    push bx
    push cx
    push dx
    push si
    push di

    mov si, 0

row_loop:
    cmp si, LEVEL_HEIGHT
    jge done

    mov di, 0

column_loop:
    cmp di, VISIBLE_COLUMNS
    jge next_row

    ; Map column = first_column + screen column

    mov bx, [bp+4]
    add bx, di

    ; X = map column * 16

    shl bx, 4

    ; Y = row * 16

    mov dx, si
    shl dx, 4

    ; Get tile code

    push bx
    push dx
    call getTile

    ; Draw tile at screen position

    push di
    push si
    push ax
    call drawtile

    inc di
    jmp column_loop

next_row:
    inc si
    jmp row_loop

done:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    pop bp

    ret 2

i dw 0
j dw 0