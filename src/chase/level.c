/* --------------------------------------------------------------------------------------- */ 
// 
// CROSS CHASE by Fabrizio Caruso
//
// Fabrizio_Caruso@hotmail.com
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.

// Permission is granted to anyone to use this software for non-commercial applications, 
// subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in
// a product, an acknowledgment in the product documentation would be
// appreciated but is not required.

// 2. Altered source versions must be plainly marked as such, and must not
// be misrepresented as being the original software.

// 3. This notice may not be removed or altered from any source distribution.
/* --------------------------------------------------------------------------------------- */ 
 
#include "character.h"
#include "item.h"
#include "item.h"
#include "settings.h"
#include "ghost.h"

#if defined(__CMOC__) && !defined(__WINCMOC__)
	#include <cmoc.h>
#else
	#include <stdlib.h>
#endif

#include "../cross_lib/cross_lib.h"

#include "level.h"

extern unsigned char level;

extern Image PLAYER_IMAGE;
extern Image GHOST_IMAGE;
extern Image BOMB_IMAGE;
extern Image DEAD_GHOST_IMAGE;

#if !defined(TINY_GAME)
	extern Image SKULL_IMAGE;
	extern Image BULLET_IMAGE;
	extern Image POWERUP_IMAGE;
	extern Image GUN_IMAGE;
	extern Image EXTRA_POINTS_IMAGE;
#endif

extern Character player; 

#if !defined(TINY_GAME)
	extern Character skull;

	extern Item powerUp;
	extern Item powerUp2;
	extern Item gun;
	extern Item extraPoints;

	extern Character bullet;

#endif

extern Character ghosts[GHOSTS_NUMBER];
extern Character bombs[BOMBS_NUMBER];


#if defined(FULL_GAME) 

	extern Item chase;
	extern Character chasingBullet;

	extern unsigned char innerVerticalWallX;
	extern unsigned char innerVerticalWallY;
	extern unsigned char innerVerticalWallLength;

	extern Image ROCKET_IMAGE;

	extern Image FREEZE_IMAGE;
	extern Image LEFT_HORIZONTAL_MISSILE_IMAGE;
	extern Image RIGHT_HORIZONTAL_MISSILE_IMAGE;

	extern Image EXTRA_LIFE_IMAGE;
	extern Image INVINCIBILITY_IMAGE;
	extern Image SUPER_IMAGE;
	extern Image CONFUSE_IMAGE;
	extern Image ZOMBIE_IMAGE;

	extern Character leftHorizontalMissile;
	extern Character rightHorizontalMissile;

	extern Item freeze;
	extern Item extraLife;
	extern Item invincibility;
	extern Item super;
	extern Item confuse;
	extern Item zombie;
	
	extern Character rockets[ROCKETS_NUMBER];

	extern char rockets_x[ROCKETS_NUMBER];
	
	extern char skullsKilled;
#endif


#if defined(FULL_GAME)
	void updateInnerWallVerticalData(void)
	{	
	unsigned char lvmod = level%5;
	if((lvmod==1)||(lvmod==0))
	{
		innerVerticalWallLength = 0;
	}
	else
	{
		#if defined(WIDE)
			innerVerticalWallLength = YSize-10+(lvmod-2)*2;
		#elif YSize<=12
			innerVerticalWallLength = 4;
		#else
			innerVerticalWallLength = YSize-14+(lvmod-2)*2;			
		#endif
	}

	innerVerticalWallX = (XSize>>1);
	innerVerticalWallY = (YSize>>1)-(innerVerticalWallLength>>1);
	}

	unsigned char oneMissileLevel(void)
	{
		return ((level%5)==3) || (level==5);
	}

	unsigned char rocketLevel(void)
	{
		return (level >= FIRST_ROCKETS_LEVEL) && ((level%5)==2 || (level%5)==3);
	}

	unsigned char missileLevel(void)
	{
		return level%5==4;
	}	

	unsigned char bossLevel(void)
	{
		return !(level%5);
	}
	
	unsigned char horizontalWallsLevel(void)
	{
		return ((level >= FIRST_HORIZONTAL_WALLS_LEVEL) && ((level%5==1) || (level%5==4)));
	}	

	void initializeAwayFromWall(Character * characterPtr, unsigned char x, unsigned char y, unsigned char status, Image *imagePtr)
	{
		do{
			initializeCharacter(characterPtr, x, y, status, imagePtr);
			relocateCharacter(characterPtr);
		} while(nearInnerWall(characterPtr));
	}

#endif 

#if defined(BETWEEN_LEVEL)

void _spiral_slow_down()
{
	unsigned char k;
	
	for(k=0;k<254;++k){};
}

void spiral(register Character *characterPtr, unsigned char length)
{
	unsigned char i;
	unsigned char j;
	
	characterPtr->_x = XSize/2;
	characterPtr->_y = YSize/2;
	for(i=0;i<length;++i)
	{
		for(j=0;j<i/2;++j)
			{
				displayCharacter(characterPtr);		
				if(i&2)
				{
					++(*((unsigned char *) characterPtr + (i&1)));
				}
				else
				{
					--(*((unsigned char *) characterPtr + (i&1)));				
				}
				#if defined(SLOW_DOWN)
				_spiral_slow_down();	
				#endif
			}
	}
}

#endif


void fillLevelWithCharacters(unsigned char nGhosts)
{
	unsigned char i;
	unsigned char j;
	unsigned char count = 0;
	
	#if defined(FULL_GAME)
		if(rocketLevel() || bossLevel())
		{
			for(i=0;i<ROCKETS_NUMBER;i++)
			{
				rockets_x[i] = (unsigned char) (i+1)*(XSize/(ROCKETS_NUMBER+1));
				initializeCharacter(&rockets[i],(unsigned char) rockets_x[i],(unsigned char)(YSize-1),1,&ROCKET_IMAGE);
				displayRocket(&rockets[i]);
			}
		}

		if(bossLevel())
		{
			nGhosts = level>>2;
		}				
	#endif
	
	#if GHOSTS_NUMBER >= 9
		ROUND_NINE_GHOSTS();
	#elif GHOSTS_NUMBER>=7 
		#if (!defined(TINY_GAME) || defined(ROUND_ENEMIES)) && !defined(FLAT_ENEMIES)
			ROUND_EIGHT_GHOSTS();	
		#else
			FLAT_EIGHT_GHOSTS();
		#endif
	#else
		FLAT_SIX_GHOSTS();
	#endif
	
	#if BOMBS_NUMBER==4
		FOUR_BOMBS();
	#elif BOMBS_NUMBER==3	
		THREE_BOMBS();
	#elif BOMBS_NUMBER==2
		TWO_BOMBS();
	#elif BOMBS_NUMBER==1
		ONE_BOMB();
	#endif
	
	#if defined(FULL_GAME)
		initializeAwayFromWall(&(powerUp._character),(XSize>>1),(YSize>>1),1,&POWERUP_IMAGE);
		initializeAwayFromWall(&(powerUp2._character),(XSize>>1),(YSize>>1),0,&POWERUP_IMAGE);
		initializeAwayFromWall(&(freeze._character),(XSize>>1),(YSize>>1),0,&FREEZE_IMAGE);
		initializeAwayFromWall(&(extraPoints._character), (XSize>>1), (YSize>>1), 0, &EXTRA_POINTS_IMAGE);
		initializeAwayFromWall(&(super._character), (XSize>>1), (YSize>>1), 0, &SUPER_IMAGE);
		initializeAwayFromWall(&(confuse._character), (XSize>>1), (YSize>>1), 0, &CONFUSE_IMAGE);		
		initializeAwayFromWall(&(zombie._character), (XSize>>1), (YSize>>1), 0, &ZOMBIE_IMAGE);	
		
		initializeAwayFromWall(&(gun._character),(XSize>>1), (YSize>>1), (bossLevel() ? 1 : 0), &GUN_IMAGE);

		initializeAwayFromWall(&player,(unsigned char) ((XSize>>1)+(rand()&1)),(unsigned char) ((YSize>>1)+(rand()&1)),1,&PLAYER_IMAGE);
				
		initializeAwayFromWall(&(extraLife._character), (XSize>>1), (YSize>>1), 0, &EXTRA_LIFE_IMAGE);

		initializeAwayFromWall(&(invincibility._character), (XSize>>1), (YSize>>1), 0, &INVINCIBILITY_IMAGE);

		if(oneMissileLevel())
		{
			initializeCharacter(&rightHorizontalMissile,         XSize-1,                      (YSize>>1), 1,&RIGHT_HORIZONTAL_MISSILE_IMAGE);			
		}
		else if(missileLevel() || bossLevel())
		{	
			initializeCharacter(&rightHorizontalMissile,         XSize-1,         HORIZONTAL_MISSILE_OFFSET, 1,&RIGHT_HORIZONTAL_MISSILE_IMAGE);
			initializeCharacter(&leftHorizontalMissile,                0, YSize-1-HORIZONTAL_MISSILE_OFFSET, 1,&LEFT_HORIZONTAL_MISSILE_IMAGE);		
		}		
		
		initializeAwayFromWall(&(chase._character), (XSize>>1), (YSize>>1),0,&BULLET_IMAGE);
		initializeCharacter(&chasingBullet, 0,0, 0, &BULLET_IMAGE);
	#else
		#if !defined(TINY_GAME)
			initializeCharacter(&(powerUp._character),(XSize>>1),(YSize>>1),1,&POWERUP_IMAGE);
			initializeCharacter(&(powerUp2._character),(XSize>>1),(YSize>>1),0,&POWERUP_IMAGE);
			initializeCharacter(&(gun._character),(XSize>>1), (YSize>>1), 0, &GUN_IMAGE);	
			initializeCharacter(&(extraPoints._character), (XSize>>1), (YSize>>1), 0, &EXTRA_POINTS_IMAGE);	
		#endif
		
		#if defined(NO_RANDOM_LEVEL) || defined(TINY_GAME)
			initializeCharacter(&player,(unsigned char) ((XSize>>1)),(unsigned char) ((YSize>>1)),1,&PLAYER_IMAGE);			
		#else
			initializeCharacter(&player,(unsigned char) ((XSize>>1)+(unsigned char) (rand()&1)),
										(unsigned char) ((YSize>>1)+(unsigned char) (rand()&1)),1,&PLAYER_IMAGE);	
		#endif
	#endif
	#if !defined(TINY_GAME)
		displayPlayer(&player);
			
		initializeCharacter(&bullet, 0, 0,0,&BULLET_IMAGE);
		initializeCharacter(&skull,XSize-2,YSize-2, 0, &SKULL_IMAGE);
	#endif
	
}

