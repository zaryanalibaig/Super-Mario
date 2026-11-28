; HERO DATA
mario_x             dw 32
mario_y             dw 144

mario_velocity_x    dw 0
mario_velocity_y    dw 0

mario_health        db STARTING_HEALTH
mario_lives         db STARTING_LIVES

mario_direction     db 1
mario_is_jumping    db 0

; ENEMY DATA

enemy_count         db 0

; SCORE DATA

game_score          dd 0
coin_count          dw 0

; CLOCK DATA

game_time           dw STARTING_TIME

; INPUT DATA

key_left_pressed    db 0
key_right_pressed   db 0
key_jump_pressed    db 0
key_run_pressed     db 0

; GAME STATE

game_state          db 0
game_running        db 1


frame_seg           dw 0                ; segment of the frame buffer (set by alloc_buffer)
msg_alloc_failed    db 'Frame buffer allocation failed.', 13, 10, '$'


camera_x        dw 0                ; world x of the left edge of the screen
hero_x          dw HERO_START_X     ; Mario's WORLD x (whole pixels)
hero_vx         dw 0                ; horizontal speed
hero_face       dw 0                ; 0 = facing right, 1 = facing left

LEVEL_PIXEL_WIDTH   equ LEVEL_WIDTH * TILE_WIDTH
MAX_CAMERA_X        equ LEVEL_PIXEL_WIDTH - SCREEN_WIDTH
WORLD_MAX_X         equ LEVEL_PIXEL_WIDTH - 16
CAMERA_FOLLOW_X     equ 160
HERO_START_X        equ 32
