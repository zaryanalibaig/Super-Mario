i dw 0
j dw 0
; putpixel with parameters color,y(rows),x(cols)
putpixel:
push bp
mov bp,sp
push ax
push bx
push cx
push di


mov cx,[bp+4]
mov ax,[bp+6]
mov bx,ax
shl ax,8

shl bx,6
add bx,ax
mov ax,[bp+8]
add bx,ax
mov di,bx
mov [es:di],cl

pop di
pop cx
pop bx
pop ax

pop bp

ret 6

fill_rect:
push bp
mov bp,sp
push ax
push bx
push cx
push dx

mov dx,[bp+8]
mov word [i],0
mov word [j],0

l1:
mov cx,[bp+6]

calling_putpixel:
mov ax,[bp+12]
add ax,[j]
push ax

mov ax,[bp+10]
add ax,[i]
push ax

mov ax,[bp+4] ; color
push ax

call putpixel;
inc word [i]
dec cx
jnz calling_putpixel

; now outer loop
inc word [j]
mov word [i],0
dec dx
jnz l1

pop dx
pop cx
pop bx
pop ax
pop bp
ret 10