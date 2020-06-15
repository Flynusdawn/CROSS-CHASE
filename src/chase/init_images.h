#ifndef _INIT_IMAGES_H
#define _INIT_IMAGES_H

// TODO: MOVE THIS TO TARGET SPECIFIC SETTINGS
#define CPC_WHITE 1
#define CPC_YELLOW 2 
#define CPC_RED 3
#define CPC_BLACK 4

#define _AQUARIUS_RED 16
#define _AQUARIUS_WHITE (16+32+64)
#define _AQUARIUS_YELLOW (16+32) 
#define _AQUARIUS_VIOLET (16+64) 
#define _AQUARIUS_CYAN (32+64)

/*
					; 0: black
					; 1: green
					; 2: blue
					; 3: cyan
					; 4: red
					; 5: yellow
					; 6: magenta
					; 7: white
*/


#ifndef COLOR_CYAN
	#define COLOR_CYAN COLOR_BLUE
#endif

#if defined(NO_GRAPHICS) || defined(NO_PRINT)
    #if !defined(COLOR_RED)
        #define COLOR_RED 0
    #endif
    #if !defined(COLOR_BLUE)
        #define COLOR_BLUE 0
    #endif
    #if !defined(COLOR_WHITE)
        #define COLOR_WHITE 0
    #endif
    #if !defined(COLOR_YELLOW)
        #define COLOR_YELLOW 0
    #endif
    #if !defined(COLOR_GREEN)
        #define COLOR_GREEN 0
    #endif
#endif 


#if defined(CPCRSLIB)
	#define _PLAYER_COLOR CPC_YELLOW
	#define _GHOST_COLOR CPC_WHITE
	#define _DEAD_GHOST_COLOR CPC_RED
	#define _SKULL_COLOR CPC_YELLOW
	#define _BOMB_COLOR CPC_RED
	#define _MISSILE_COLOR CPC_WHITE
	#define _ROCKET_COLOR CPC_WHITE
	#define _POWERUP_COLOR CPC_YELLOW
	#define _FREEZE_COLOR CPC_WHITE
	#define _SUPER_COLOR CPC_RED
	#define _GUN_COLOR CPC_YELLOW
	#define _BULLET_COLOR CPC_WHITE
	#define _BRICK_COLOR CPC_YELLOW
	#define _EXTRA_POINTS_COLOR CPC_YELLOW
	#define _EXTRA_LIFE_COLOR CPC_WHITE
	#define _INVINCIBILITY_COLOR CPC_YELLOW
	#define _CONFUSE_COLOR CPC_RED
	#define _ZOMBIE_COLOR CPC_YELLOW	
#elif defined(__AQUARIUS__) && defined(MEMORY_MAPPED)
	#define _PLAYER_COLOR _AQUARIUS_CYAN
	#define _GHOST_COLOR _AQUARIUS_WHITE
	#define _DEAD_GHOST_COLOR _AQUARIUS_RED
	#define _SKULL_COLOR _AQUARIUS_YELLOW
	#define _BOMB_COLOR _AQUARIUS_RED
	#define _MISSILE_COLOR _AQUARIUS_WHITE
	#define _ROCKET_COLOR _AQUARIUS_WHITE
	#define _POWERUP_COLOR _AQUARIUS_YELLOW
	#define _FREEZE_COLOR _AQUARIUS_CYAN
	#define _SUPER_COLOR _AQUARIUS_RED
	#define _GUN_COLOR _AQUARIUS_YELLOW
	#define _BULLET_COLOR _AQUARIUS_WHITE
	#define _BRICK_COLOR _AQUARIUS_YELLOW
	#define _EXTRA_POINTS_COLOR _AQUARIUS_YELLOW
	#define _EXTRA_LIFE_COLOR _AQUARIUS_YELLOW
	#define _INVINCIBILITY_COLOR _AQUARIUS_YELLOW
	#define _CONFUSE_COLOR _AQUARIUS_RED
	#define _ZOMBIE_COLOR _AQUARIUS_YELLOW	
#elif defined(__PC6001__) || defined(__SPC1000__)
	#define _PLAYER_COLOR COLOR_BLUE 
	#define _GHOST_COLOR COLOR_CYAN
	#define _DEAD_GHOST_COLOR COLOR_RED
	#define _SKULL_COLOR COLOR_YELLOW
	#define _BOMB_COLOR COLOR_RED
	#define _MISSILE_COLOR COLOR_CYAN
	#define _ROCKET_COLOR COLOR_CYAN
	#define _POWERUP_COLOR COLOR_CYAN
	#define _FREEZE_COLOR COLOR_BLUE
	#define _SUPER_COLOR COLOR_RED
	#define _GUN_COLOR COLOR_BLUE
	#define _BULLET_COLOR COLOR_CYAN
	#define _BRICK_COLOR COLOR_YELLOW
	#define _EXTRA_POINTS_COLOR COLOR_YELLOW
	#define _EXTRA_LIFE_COLOR COLOR_YELLOW
	#define _INVINCIBILITY_COLOR COLOR_YELLOW
	#define _CONFUSE_COLOR COLOR_RED
	#define _ZOMBIE_COLOR COLOR_YELLOW
#elif defined(NO_GRAPHICS)
	#define _PLAYER_COLOR 0 
	#define _GHOST_COLOR 0
	#define _DEAD_GHOST_COLOR 0
	#define _SKULL_COLOR 0
	#define _BOMB_COLOR 0
	#define _MISSILE_COLOR 0
	#define _ROCKET_COLOR 0
	#define _POWERUP_COLOR 0
	#define _FREEZE_COLOR 0
	#define _SUPER_COLOR 0
	#define _GUN_COLOR 0
	#define _BULLET_COLOR 0
	#define _BRICK_COLOR 0
	#define _EXTRA_POINTS_COLOR 0
	#define _EXTRA_LIFE_COLOR 0
	#define _INVINCIBILITY_COLOR 0
	#define _CONFUSE_COLOR 0
	#define _ZOMBIE_COLOR 0
#else
	#define _PLAYER_COLOR COLOR_CYAN
	#define _GHOST_COLOR COLOR_WHITE
	#define _DEAD_GHOST_COLOR COLOR_RED
	#define _SKULL_COLOR COLOR_YELLOW
	#define _BOMB_COLOR COLOR_RED
	#define _MISSILE_COLOR COLOR_WHITE
	#define _ROCKET_COLOR COLOR_WHITE
	#define _POWERUP_COLOR COLOR_GREEN
	#define _FREEZE_COLOR COLOR_CYAN
	#define _SUPER_COLOR COLOR_RED
	#if !defined(__NCURSES__)
		#define _GUN_COLOR COLOR_BLUE
	#else
		#define _GUN_COLOR COLOR_YELLOW
	#endif
	#define _BULLET_COLOR COLOR_WHITE
	#define _BRICK_COLOR COLOR_YELLOW
	#define _EXTRA_POINTS_COLOR COLOR_YELLOW
	#define _EXTRA_LIFE_COLOR COLOR_WHITE
	#define _INVINCIBILITY_COLOR COLOR_YELLOW
	#define _CONFUSE_COLOR COLOR_RED
	#define _ZOMBIE_COLOR COLOR_YELLOW
#endif


void INIT_IMAGES(void);




#endif // _INIT_IMAGES_H

