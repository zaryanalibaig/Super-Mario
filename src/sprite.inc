; Name:      drawsprite
; Purpose:   draw a 16-wide sprite (16 or 32 rows) with clipping on all
;            four screen edges; colour 0 is transparent
; Inputs:    [bp+10] x (signed), [bp+8] y (signed), [bp+6] sprite address,
;            [bp+4] flags: bit 0 = mirrored, bit 1 = 32 rows tall
;            ES = segment to draw into
; locals: [bp-2] = row index, [bp-4] = height 
;No ouput and register changed
; used  local functions with . so that it doesnot cause collision
drawsprite:
    push bp
    mov bp, sp
    sub sp, 4
    push ax
    push bx
    push cx
    push dx
    push si
    push di

    mov si, [bp+6]              ; SI = start of the sprite data
    mov dx, [bp+8]              ; DX = screen y of the current row
    mov word [bp-2], 0          ; row index = 0
    mov word [bp-4], 16         ; default height
    test word [bp+4], 2
    jz .row_loop
    mov word [bp-4], 32         ; tall sprite (Super Mario)

.row_loop:
    cmp dx, VIEW_HEIGHT         ; row below the visible area?
    jge .skip_row
    cmp dx, VIEW_HEIGHT         ; row below the visible area?
    jge .skip_row
    mov bx, dx                  ; BX = y * 320 = y*256 + y*64
    shl bx, 8
    mov ax, dx
    shl ax, 6
    add bx, ax

    xor cx, cx  ; columns

.pixel_loop:
    mov di, cx                  ; DI = source column
    test word [bp+4], 1
    jz .read
    mov di, 15                  ; mirrored
    sub di, cx
.read:
    add di, si                  ; DI = address of this pixel in the sprite data
    mov al, [di]                ; AL = colour
    cmp al, 0
    je .next_pixel              ; transparent

    mov di, [bp+10]             ; DI = screen x of this pixel
    add di, cx
    cmp di, 0
    jl .next_pixel              ; left of the screen
    cmp di, SCREEN_WIDTH
    jge .next_pixel             ; right of the screen
    add di, bx
    mov [es:di], al             ; plot the pixel

.next_pixel:
    inc cx
    cmp cx, 16
    jb .pixel_loop

.skip_row:
    add si, 16                  ; next row of sprite data
    inc dx                      ; next screen row
    inc word [bp-2]
    mov ax, [bp-2]
    cmp ax, [bp-4]
    jb .row_loop

    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    mov sp, bp
    ret 8

hero_stand1:
    db 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0
    db 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0
    db 0, 0, 6, 6, 6, 42, 42, 6, 42, 0, 0, 0, 0, 0, 0, 0
    db 0, 6, 42, 6, 42, 42, 42, 6, 42, 42, 42, 0, 0, 0, 0, 0
    db 0, 6, 42, 6, 6, 42, 42, 42, 6, 42, 42, 42, 0, 0, 0, 0
    db 0, 6, 6, 42, 42, 42, 42, 6, 6, 6, 6, 0, 0, 0, 0, 0
    db 0, 0, 0, 42, 42, 42, 42, 42, 42, 42, 0, 0, 0, 0, 0, 0
    db 0, 0, 6, 6, 4, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0
    db 0, 6, 6, 6, 4, 6, 6, 4, 6, 6, 6, 0, 0, 0, 0, 0
    db 6, 6, 6, 6, 4, 4, 4, 4, 6, 6, 6, 6, 0, 0, 0, 0
    db 42, 42, 6, 4, 42, 4, 4, 42, 4, 6, 42, 42, 0, 0, 0, 0
    db 42, 42, 42, 4, 4, 4, 4, 4, 4, 42, 42, 42, 0, 0, 0, 0
    db 42, 42, 4, 4, 4, 4, 4, 4, 4, 4, 42, 42, 0, 0, 0, 0
    db 0, 0, 4, 4, 4, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0
    db 0, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0
    db 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0
hero_stand1_end :