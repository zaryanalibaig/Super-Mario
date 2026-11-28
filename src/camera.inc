update_camera:
    push ax

    mov ax, [hero_x]
    sub ax, [camera_x]
    cmp ax, CAMERA_FOLLOW_X
    jle .walls

    mov ax, [hero_x]
    sub ax, CAMERA_FOLLOW_X
    cmp ax, MAX_CAMERA_X
    jle .below_limit
    mov ax, MAX_CAMERA_X
.below_limit:
    cmp ax, [camera_x]
    jle .walls                      ; camera never scrolls backward
    mov [camera_x], ax

.walls:
    mov ax, [camera_x]
    cmp [hero_x], ax
    jge .right_wall
    mov [hero_x], ax                ; clamp to left screen edge
    mov word [hero_vx], 0
.right_wall:
    cmp word [hero_x], WORLD_MAX_X
    jle .done
    mov word [hero_x], WORLD_MAX_X
    mov word [hero_vx], 0
.done:
    pop ax
    ret


reset_view:
    mov word [camera_x], 0
    mov word [hero_x], HERO_START_X
    mov word [hero_vx], 0
    mov word [hero_face], 0
    ret


; Locals: [bp-2] = first map column, [bp-4] = horizontal pixel offset
drawLevel_scrolled:
    push bp
    mov bp, sp
    sub sp, 4
    push ax
    push bx
    push cx
    push dx
    push si
    push di

    mov ax, [camera_x]
    mov bx, ax
    shr ax, 4
    and bx, 15
    mov [bp-2], ax
    mov [bp-4], bx

    xor si, si
.row_loop:
    xor di, di
.col_loop:
    mov ax, [bp-2]
    add ax, di
    shl ax, 4
    push ax
    mov ax, si
    shl ax, 4
    push ax
    call getTile
    mov bx, ax
    mov dl, [tile_colours + bx]
    xor dh, dh

    mov ax, di
    shl ax, 4
    sub ax, [bp-4]
    mov bx, 16
    cmp di, 0
    jne .not_first
    xor ax, ax
    mov bx, 16
    sub bx, [bp-4]                  ; trim left partial tile to screen edge
    jmp .draw
.not_first:
    cmp di, VISIBLE_COLUMNS
    jne .draw
    mov bx, [bp-4]                  ; trim right edge to visible offset
    test bx, bx
    jz .next_col

.draw:
    push ax
    mov ax, si
    shl ax, 4
    push ax
    push bx
    push word 16
    push dx
    call fill_rect

.next_col:
    inc di
    cmp di, VISIBLE_COLUMNS + 1
    jae .next_row
    jmp .col_loop
.next_row:
    inc si
    cmp si, LEVEL_HEIGHT
    jae .finished
    jmp .row_loop

.finished:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    mov sp, bp
    pop bp
    ret