
; Screen Dimensions
SCREEN_WIDTH       equ 320
SCREEN_HEIGHT      equ 200

; Tile dimensions
TILE_WIDTH         equ 16
TILE_HEIGHT        equ 16

; Level dimensions
LEVEL_WIDTH        equ 60
LEVEL_HEIGHT       equ 12
LEVEL_SIZE   equ LEVEL_WIDTH * LEVEL_HEIGHT

; Visible tile grid
VISIBLE_COLUMNS    equ 20
VISIBLE_ROWS       equ 12

; Video memory
VIDEO_SEGMENT      equ 0A000h

; Mario properties
STARTING_LIVES     equ 3
STARTING_HEALTH    equ 1

; Game limits
STARTING_TIME      equ 300
MAX_LIVES          equ 99
MAX_SCORE          equ 999999

; Keyboard scan codes
KEY_LEFT           equ 4Bh
KEY_RIGHT          equ 4Dh
KEY_UP             equ 48h
KEY_DOWN           equ 50h
KEY_SPACE          equ 39h
KEY_SHIFT          equ 2Ah
KEY_ESCAPE         equ 01h
KEY_ENTER          equ 1Ch
KEY_PAUSE equ 19h

; VGA palette indices
COLOR_BLACK        equ 0
COLOR_BLUE         equ 1
COLOR_GREEN        equ 2
COLOR_RED          equ 4
COLOR_BROWN        equ 6
COLOR_WHITE        equ 15

; Tile codes
TILE_SKY	equ 0 	
TILE_GROUND	equ 1
TILE_BRICK	equ 2
TILE_QUESTION_COIN equ 3
TILE_QUESTION_MUSHROOM	equ 4
TILE_EMPTY_BLOCK equ 5
TILE_PIPE_TOP_LEFT equ 6
TILE_PIPE_TOP_RIGHT equ 7
TILE_PIPE_BODY_LEFT equ 8
TILE_PIPE_BODY_RIGHT equ 9
TILE_STAIR equ 10
TILE_COIN equ 11
TILE_FLAG_POLE equ 12

tile_colours:
    db 0x0B    ; 0  sky
    db 0x06    ; 1  ground
    db 0x06    ; 2  brick
    db 0x0E    ; 3  ? block (coin)
    db 0x0A    ; 4  ? block (mushroom)
    db 0x08    ; 5  empty block
    db 0x02    ; 6  pipe top-left
    db 0x02    ; 7  pipe top-right
    db 0x02    ; 8  pipe body-left
    db 0x02    ; 9  pipe body-right
    db 0x06    ; 10 stair block
    db 0x0E    ; 11 coin
    db 0x0F    ; 12 flag pole


test_colours:
    db 9        ; sky
    db 2        ; ground top (green)
    db 6        ; ground body (brown)
    db 4        ; brick
    db 10       ; pipe
    db 12       ; Mario hat/shirt
    db 14       ; coin / HUD text
    db 6        ; Goomba
    db 2        ; Koopa
    db 12       ; mushroom cap
    db 15       ; text / mushroom spots
    db 0        ; HUD background
    db 7        ; stair block
    db 8        ; empty block
    db 13       ; spare
    db 1        ; spare