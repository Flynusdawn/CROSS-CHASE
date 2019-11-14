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
 
#ifndef _LEVEL
#define _LEVEL

#include "character.h"

// 		initializeCharacter(&ghosts[count], 0,(uint8_t) 0,0,&GHOST_IMAGE);

#if defined(TINY_GAME) || defined(NO_DEAD_GHOSTS)
	#define PLACE_DEAD_GHOST() \
		initializeCharacter(&ghosts[count],(uint8_t) (count),(uint8_t) 1,0,&GHOST_IMAGE);	
#else
	#define PLACE_DEAD_GHOST() \
		initializeCharacter(&ghosts[count],(uint8_t) (GHOSTS_NUMBER-count),(uint8_t) 1,0,&DEAD_GHOST_IMAGE);
#endif


// Check XSize to avoid overflow
#if XSize>48
	#define ROUND_X_POS (uint8_t) ((2*j+1)*(uint8_t)(XSize/6))
#else
	#if defined(OPTIMIZE_ROUND_ENEMIES)
		#define ROUND_X_POS (uint8_t) (6*j)		
	#else
		#define ROUND_X_POS (uint8_t) ((2*j+1)*XSize/6)
	#endif
#endif

// Check YSize to avoid overflow
#if YSize>48
	#define ROUND_Y_POS (uint8_t) ((2*i+1)*(uint8_t)(YSize/6))
#else
	#if defined(OPTIMIZE_ROUND_ENEMIES)
		#define ROUND_Y_POS (uint8_t) (6*i)
	#else
		#define ROUND_Y_POS (uint8_t) ((2*i+1)*YSize/6)
	#endif
#endif


#define PLACE_ROUND_GHOST() \
	initializeCharacter(&ghosts[count], \
		ROUND_X_POS, \
		ROUND_Y_POS, \
		1 ,&GHOST_IMAGE);

#define PLACE_FLAT_GHOST() \
	initializeCharacter(&ghosts[count],(uint8_t) (j*(XSize/5)),(i*(YSize/5)),1,&GHOST_IMAGE);

#define PLACE_FLAT_GHOST_6() \
	initializeCharacter(&ghosts[count],(uint8_t) (j*(XSize>>2)),(i*(YSize/5)),1,&GHOST_IMAGE);	
	
#define PLACE_NINTH_GHOST() \
	initializeCharacter(&ghosts[4],(uint8_t) (XSize-4),(uint8_t) (YSize-4),1,&GHOST_IMAGE);

	
#define ROUND_NINE_GHOSTS() \
	for(i=0;i<=2;++i) \
	{ \
		for(j=0;j<=2;++j) \
		{ \
			if(nGhosts>count) \
			{ \
				if(count!=4) \
				{ \
					PLACE_ROUND_GHOST(); \
				} \
				else \
				{ \
					PLACE_NINTH_GHOST(); \
				} \
			} \
			else \
			{ \
				PLACE_DEAD_GHOST(); \
			} \
			++count; \
		} \
	}

	
#if defined(OPTIMIZE_ROUND_ENEMIES)
	#define OPT_OFFSET 1
#else
	#define OPT_OFFSET 0
#endif

#define ROUND_EIGHT_GHOSTS() \
	for(i=0+OPT_OFFSET;i<=2+OPT_OFFSET;++i) \
	{ \
		for(j=0+OPT_OFFSET;j<=2+OPT_OFFSET;++j) \
		{ \
			if(i!=1+OPT_OFFSET || j !=1+OPT_OFFSET) \
			{ \
				if(nGhosts>count) \
				{ \
					PLACE_ROUND_GHOST(); \
				} \
				else \
				{ \
					PLACE_DEAD_GHOST(); \
				} \
				++count; \
			} \
		} \
	}


#define FLAT_EIGHT_GHOSTS() \
	for(j=1;j<=4;++j) \
	{ \
		for(i=1;i<=4;i+=3) \
		{ \
			if(nGhosts>count) \
			{ \
				PLACE_FLAT_GHOST(); \
			} \
			else \
			{ \
				PLACE_DEAD_GHOST(); \
			} \
			++count; \
		} \
	}

	
#define FLAT_SIX_GHOSTS() \
	for(j=1;j<=3;++j) \
	{ \
		for(i=1;i<=4;i+=3) \
		{ \
			if(nGhosts>count) \
			{ \
				PLACE_FLAT_GHOST_6(); \
			} \
			else \
			{ \
				PLACE_DEAD_GHOST(); \
			} \
			++count; \
		} \
	}

#if defined(NO_RANDOM_LEVEL)
	#define PLACE_BOMB_4() \
		initializeCharacter(&bombs[count],(uint8_t) ((XSize/3)*i), (uint8_t) ((YSize/3)*j),0,&BOMB_IMAGE)
#elif defined(TINY_GAME) || defined(SIMPLE_RANDOM_LEVEL)
	#define PLACE_BOMB_4() \
		initializeCharacter(&bombs[count],(uint8_t) (((XSize/3)*i)+(uint8_t)(rand()&1)), \
													  (uint8_t) ((YSize/3)*j),0,&BOMB_IMAGE);
#else
	#define PLACE_BOMB_4() \
		initializeCharacter(&bombs[count],(uint8_t) (((XSize/3)*i)-(uint8_t)(rand()&1)), \
									  (uint8_t) (((YSize/3)*j)+(uint8_t)(rand()&1)),0,&BOMB_IMAGE);		
#endif

	
#define FOUR_BOMBS() \
	do \
	{ \
		count = 0; \
		for(i=1;i<=2;++i) \
		{ \
			for(j=1;j<=2;++j) \
			{ \
				PLACE_BOMB_4(); \
				++count; \
			} \
		} \
	} \
	while(0)

	
#if defined(NO_RANDOM_LEVEL)
	#define THREE_BOMBS() \
		do \
		{ \
			initializeCharacter(&bombs[0],(XSize>>1), ((YSize/3)<<1),0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[1],XSize/3, (YSize/3),0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[2],((XSize/3)<<1), (YSize/3),0,&BOMB_IMAGE);	\
		} \
		while(0)
#else
	#define THREE_BOMBS() \
		do \
		{ \
			uint8_t rnd = rand()&1; \
			initializeCharacter(&bombs[0],XSize/3+rnd, (YSize/3)+rnd,0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[1],(XSize>>1)+rnd, ((YSize/3)*2)+rnd,0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[2],2*(XSize/3)+rnd, (YSize/3)-rnd,0,&BOMB_IMAGE); \
		} \
		while(0)
#endif	


#if defined(NO_RANDOM_LEVEL)
	#define TWO_BOMBS() \
		do \
		{ \
			initializeCharacter(&bombs[0],(XSize>>1), ((YSize/3)),0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[1],(XSize>>1), ((YSize/3)<<1),0,&BOMB_IMAGE); \
		} \
		while(0)
#else
	#define TWO_BOMBS() \
		do \
		{ \
			initializeCharacter(&bombs[0],(XSize>>1), ((YSize/3))+rand()%3,0,&BOMB_IMAGE); \
			initializeCharacter(&bombs[1],(XSize>>1)-1+rand()%3, ((YSize/3)*2)-1+rand()%3,0,&BOMB_IMAGE); \
		} \
		while(0)
#endif	


#if defined(NO_RANDOM_LEVEL)
	#define ONE_BOMB() \
		initializeCharacter(&bombs[0],(XSize>>1), (YSize>>1),0,&BOMB_IMAGE);			
#else
	#define ONE_BOMB() \
		initializeCharacter(&bombs[0],(XSize>>1)+rand()&1, (YSize>>1)+rand()&1,0,&BOMB_IMAGE);
#endif

#if defined(BETWEEN_LEVEL)
	void spiral(register Character *characterPtr, uint8_t length);
#endif

void fillLevelWithCharacters(uint8_t nGhosts);

#if defined(FULL_GAME)
	void updateInnerWallVerticalData(void);
	
	uint8_t oneMissileLevel(void);
	
	uint8_t rocketLevel(void);

	uint8_t missileLevel(void);	

	uint8_t bossLevel(void);
	
	uint8_t horizontalWallsLevel(void);
	
	void initializeAwayFromWall(Character * characterPtr, uint8_t x, uint8_t y, uint8_t status, Image *imagePtr);

#endif 



#endif // _LEVEL
