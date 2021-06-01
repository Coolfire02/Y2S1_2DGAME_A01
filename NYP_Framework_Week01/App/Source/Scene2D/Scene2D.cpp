#include "Scene2D.h"
#include <iostream>
using namespace std;

// Include Shader Manager
#include "RenderControl\ShaderManager.h"

#include "System\filesystem.h"

/**
 @brief Constructor This constructor has protected access modifier as this class will be a Singleton
 */
CScene2D::CScene2D(void)
	: cKeyboardController(NULL),
	cMap2d(NULL)
	, cGUI(NULL)
	, cPlayer2D(NULL)
{
}

/**
 @brief Destructor
 */
CScene2D::~CScene2D(void)
{
	if (cPlayer2D) {
		cPlayer2D->Destroy();
		cPlayer2D = NULL;
	}

	if (cGUI)
	{
		cGUI->Destroy();
		cGUI = NULL;
	}
	
	if (cMap2d) {
		cMap2d->Destroy();
		cMap2d = NULL;
	}

	// We won't delete this since it was created elsewhere
	cKeyboardController = NULL;
}

/**
@brief Init Initialise this instance
*/ 
bool CScene2D::Init(void)
{
	// Include Shader Manager
	CShaderManager::GetInstance()->Add("2DShader", "Shader\\Scene2D.vs", "Shader\\Scene2D.fs");
	CShaderManager::GetInstance()->Use("2DShader");
	CShaderManager::GetInstance()->Add("2DColorShader", "Shader\\Scene2DColor.vs", "Shader\\Scene2DColor.fs");
	CShaderManager::GetInstance()->Use("2DColorShader");
	CShaderManager::GetInstance()->activeShader->setInt("texture1", 0);

	// Create an init the 2D Map
	cMap2d = CMap2D::GetInstance();
	cMap2d->SetShader("2DShader");
	if (cMap2d->Init() == false) {
		cout << "Failed to load CMap2D" << endl;
		return false;
	}
	// Load the map into an array
	if (cMap2d->LoadMap("Maps/DM2213_Map_Level_01.csv") == false) {
		//Loading was unsuccessful
		cout << "Unable to load DM22213_Map_Level_01.csv" << endl;
		return false;
	}

	// Setup the shaders
	CShaderManager::GetInstance()->Add("textShader", "Shader\\text.vs", "Shader\\text.fs");
	CShaderManager::GetInstance()->Use("textShader");

	// Create and initialise the CPlayer2D
	cPlayer2D = CPlayer2D::GetInstance();
	// Pass shader to cPlayer2D
	cPlayer2D->SetShader("2DColorShader");
	// Initialise the instance
	if (cPlayer2D->Init() == false) {
		cout << "Failed to load CPlayer2D" << endl;

	}
	

	// Store the keyboard controller singleton instance here
	cKeyboardController = CKeyboardController::GetInstance();

	// Setup cGUI
	cGUI = CGUI_Scene2D::GetInstance();
	cGUI->Init();

	return true;
}

/**
@brief Update Update this instance
*/
void CScene2D::Update(const double dElapsedTime)
{
	//Call the Map2d's update method
	cMap2d->Update(dElapsedTime);

	// Call the cPlayer2D's update method
	cPlayer2D->Update(dElapsedTime);

	cGUI->Update(dElapsedTime);
}

/**
 @brief PreRender Set up the OpenGL display environment before rendering
 */
void CScene2D::PreRender(void)
{
	// Reset the OpenGL rendering environment
	glLoadIdentity();

	// Clear the screen and buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Enable 2D texture rendering
	glEnable(GL_TEXTURE_2D);
}

/**
 @brief Render Render this instance
 */
void CScene2D::Render(void)
{
	// Call the Map2D's PreRender()
	cMap2d->PreRender();
	cMap2d->Render();
	cMap2d->PostRender();

	//Call the CPlayer2D's PreRender()
	cPlayer2D->PreRender();
	cPlayer2D->Render();
	cPlayer2D->PostRender();

	// Call the cGUI's PreRender()
	cGUI->PreRender();
	// Call the cGUI's Render()
	cGUI->Render();
	// Call the cGUI's PostRender()
	cGUI->PostRender();
}

/**
 @brief PostRender Set up the OpenGL display environment after rendering.
 */
void CScene2D::PostRender(void)
{
}