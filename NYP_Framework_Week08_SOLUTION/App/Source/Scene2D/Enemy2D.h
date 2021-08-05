/**
 CEnemy2D
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

// Include Singleton template
#include "DesignPatterns\SingletonTemplate.h"

// Include GLEW
#ifndef GLEW_STATIC
#include <GL/glew.h>
#define GLEW_STATIC
#endif

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include CEntity2D
#include "Primitives/Entity2D.h"

// Include the Map2D as we will use it to check the player's movements and actions
class CMap2D;

// Include Keyboard controller
#include "Inputs\KeyboardController.h"

// Include Physics2D
#include "Physics2D.h"

// Include Player2D
#include "Player2D.h"

// Include AnimatedSprites
#include "Primitives/SpriteAnimation.h"

// Include InventoryManager
#include "InventoryManager.h"

// Include SoundController
#include "..\SoundController\SoundController.h"

class CEnemy2D : public CEntity2D
{

public:

	enum ENEMY_TYPE {
		ENEMY_GOLEM,
		ENEMY_COUNT
	};

	// Init
	bool Init(ENEMY_TYPE type);

	// Update
	void Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);

	void CollidedWith(CEntity2D*);

	// Constructor
	CEnemy2D(void);

	// Destructor
	~CEnemy2D(void);

protected:

	glm::i32vec2 i32vec2OldIndex;
	glm::i32vec2 i32vec2OldMicroIndex;

	ENEMY_TYPE type;
	float enemySpeed;

	// Handler to the CMap2D instance
	CMap2D* cMap2D;

	// Player Attached
	CPlayer2D* cPlayer2D;

	// InventoryManager
	CInventoryManager* cInventoryManager;
	// InventoryItem
	CInventoryItem* cInventoryItem;

	// Physics
	CPhysics2D cPhysics2D;

	//CS: Animated Sprite
	CSpriteAnimation* animatedSprites;

	// Current color
	glm::vec4 currentColor;

	// Handler to the CSoundController
	CSoundController* cSoundController;

	// Let enemy interact with the map
	void InteractWithMap(void);

	// Load a texture
	bool LoadTexture(const char* filename, GLuint& iTextureID);

	// Update the health and lives
	void UpdateHealthLives(void);
};

