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
