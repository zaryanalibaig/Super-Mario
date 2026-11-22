; getTile gets the px and py as parameters and return the tile 
; only ax is used bacause it is needed to return the value and 
; calculates the pixel location then uses the that to move the tile
; in al and set ah to 0 
getTile:
push bp
mov bp,sp
push bx
push cx
push dx
; bp+6 gives px   
mov bx,[bp+6]
mov ax,LEVEL_WIDTH
mov cx,TILE_WIDTH
mul cx ; the value after mul is stored in ax
mov cx,ax ; saving value of ax caus ax is needed for returning the values
mov ax,TILE_SKY
cmp bx,cx ; if out of bound return the Sky tile
jae getTile_end

; bp+4 gives py  
mov bx,[bp+4]
mov ax,LEVEL_HEIGHT
mov cx, TILE_HEIGHT
mul cx
mov cx,ax ; done so that we can return value in ax
mov ax,TILE_SKY
cmp bx,cx
jae getTile_end

; bp+6 gives px   

mov bx,[bp+6]
shr bx,4
; bp+4 gives py  

mov ax,[bp+4]
shr ax,4
mov cx,60
mul cx
add ax,bx
mov bx,ax
mov al,[original_map+bx]
xor ah,ah
getTile_end:
pop dx
pop cx
pop bx
pop bp

ret 4

Validate_map:
push ax
mov ax, original_map_end
sub ax, original_map

cmp ax, LEVEL_SIZE
jne map_error

; Map is valid
jmp map_valid

map_error:
    ; Handle incorrect map size
    mov ax, 0x4c01
    int 0x21
    ret
map_valid:
pop ax
ret

original_map:

; Row 0 - HUD
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

; Row 1
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

; Row 2 - Flag pole top
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0

; Row 3
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0

; Row 4
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0

; Row 5
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0

; Row 6 - Top stair step and pole
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,12,0,0,0

; Row 7 - Blocks, pipe 2, bricks, stairs
db 0,0,0,0,0,0,0,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,7,0,0,0,0,2,3,2,2,3,0,0,0,0,2,2,4,2,0,0,10,10,0,0,12,0,0,0

; Row 8 - Coins, pipe 1, pipe 2, stairs
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,11,11,0,0,11,11,11,0,0,0,8,9,9,0,11,11,0,0,0,0,0,11,0,0,0,0,0,0,0,0,0,10,10,10,11,11,12,0,0,0

; Row 9 - Pipe bodies, stairs, flag base
db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,0,0,0,0,0,0,0,0,0,8,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,0,1,0,0,0

; Row 10 - Ground and pits
db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1

; Row 11 - Ground and pits
db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1


working_map:
times LEVEL_SIZE db 0