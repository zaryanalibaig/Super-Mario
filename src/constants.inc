
; Screen Dimensions
SCREEN_WIDTH       equ 320
SCREEN_HEIGHT      equ 200

; Tile dimensions
TILE_WIDTH         equ 16
TILE_HEIGHT        equ 16

; Level dimensions
LEVEL_WIDTH        equ 60
LEVEL_HEIGHT       equ 12

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


; VGA palette indices
COLOR_BLACK        equ 0
COLOR_BLUE         equ 1
COLOR_GREEN        equ 2
COLOR_RED          equ 4
COLOR_BROWN        equ 6
COLOR_WHITE        equ 15