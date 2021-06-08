/**
 Map2D
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

// Include SingletonTemplate
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

// Include the RapidCSV
#include "System/rapidcsv.h"
// Include map storage
#include <map>

// Include Settings
#include "GameControl\Settings.h"

// Include Entity2D
#include "Primitives/Entity2D.h"

// A structure storing information about Map Sizes
struct MapSize {
	unsigned int uiRowSize;
	unsigned int uiColSize;
};

// A structure storing information about a map grid
// It includes data to be used for A* Path Finding
struct Grid {
	unsigned int value;

	// Row and Column index of its parent
	// Note that 0 <= i < uiRowSize & 0 <= j < uiColSize
	unsigned int uiParentRow, uiParentCol;
	// Movement Costs: f = g + h
	double f, g, h;
};

class CMap2D : public CSingletonTemplate<CMap2D>, public CEntity2D
{
	friend CSingletonTemplate<CMap2D>;
public:

	enum TILE_ID {
		//Entities (1-9)
		PLAYER = 3,
		ENEMY = 4,

		ENTITIES_END = 9,

		//Interactables (50-69)
		BOMB_SMALL = 50,
		BOMB_MEDIUM = 51,

		POWERUP_DOUBLEJUMP = 55,

		//Interactable Blocks (70-99)
		ACID_DOWN = 70,
		ACID_UP = 71,
		ACID_RIGHT = 72,
		ACID_LEFT = 73,

		INTERACTABLES_END = 99,

		//Blocks (100-199)
		COLOUR_BLOCK_UP = 100,
		COLOUR_BLOCK_DOWN,
		COLOUR_BLOCK_RIGHT,
		COLOUR_BLOCK_LEFT,
		TILE_COUNT
	};

	// Init
	bool Init(	const unsigned int uiNumLevels = 1,
				const unsigned int uiNumRows = 24,
				const unsigned int uiNumCols = 32);

	// Update
	void Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);

	// Set the specifications of the map
	void SetNumTiles(const CSettings::AXIS sAxis, const unsigned int uiValue);
	void SetNumSteps(const CSettings::AXIS sAxis, const unsigned int uiValue);

	// Set the value at certain indices in the arrMapInfo
	void SetMapInfo(const unsigned int uiRow, const unsigned int uiCol, const int iValue, const bool bInvert = true);

	// Get the value at certain indices in the arrMapInfo
	int GetMapInfo(const unsigned int uiRow, const unsigned int uiCol, const bool bInvert = true) const;

	// Load a map
	bool LoadMap(string filename, const unsigned int uiLevel = 0);

	// Save a tilemap
	bool SaveMap(string filename, const unsigned int uiLevel = 0);

	// Find the indices of a certain value in arrMapInfo
	bool FindValue(const int iValue, unsigned int& uirRow, unsigned int& uirCol, const bool bInvert = true);

	// Set current level
	void SetCurrentLevel(unsigned int uiCurLevel);
	// Get current level
	unsigned int GetCurrentLevel(void) const;

	// Set Color of tile
	void SetColorOfTile(TILE_ID id, glm::vec4 color);

protected:
	// The variable containing the rapidcsv::Document
	// We will load the CSV file's content into this Document
	rapidcsv::Document doc;

	// A 3-D array which stores the values of the tile map
	Grid*** arrMapInfo;

	glm::vec4 blockColor[TILE_COUNT];

	// The current level
	unsigned int uiCurLevel;
	// The number of levels
	unsigned int uiNumLevels;

	// A 1-D array which stores the map sizes for each level
	MapSize* arrMapSizes;

	// Map containing texture IDs
	map<int, int> MapOfTextureIDs;

	//CS: The quadMesh for drawing the tiles
	CMesh* quadMesh;

	// Constructor
	CMap2D(void);

	// Destructor
	virtual ~CMap2D(void);

	// Load a texture
	bool LoadTexture(const char* filename, const int iTextureCode);

	// Render a tile
	void RenderTile(const unsigned int uiRow, const unsigned int uiCol);
};

