/**
 CGUI_Scene2D
 By: Toh Da Jun
 Date: May 2021
 */
#include "GUI_Scene2D.h"

#include <iostream>
using namespace std;

/**
 @brief Constructor This constructor has protected access modifier as this class will be a Singleton
 */
CGUI_Scene2D::CGUI_Scene2D(void)
	: cSettings(NULL)
	, window_flags(0)
	, m_fProgressBar(0.0f)
	, cInventoryManager(NULL)
	, cInventoryItem(NULL)
{
}

/**
 @brief Destructor This destructor has protected access modifier as this class will be a Singleton
 */
CGUI_Scene2D::~CGUI_Scene2D(void)
{
	// We won't delete this since it was created elsewhere
	cSettings = NULL;

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (cInventoryManager)
	{
		cInventoryManager->Destroy();
		cInventoryManager = NULL;
	}
}

/**
  @brief Initialise this instance
  */
bool CGUI_Scene2D::Init(void)
{
	// Get the handler to the CSettings instance
	cSettings = CSettings::GetInstance();

	// Store the CFPSCounter singleton instance here
	cFPSCounter = CFPSCounter::GetInstance();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui Style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup platform/render bindings
	ImGui_ImplGlfw_InitForOpenGL(CSettings::GetInstance()->pWindow, true);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Define the window flags
	window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	// Initialise the cInventoryManager
	cInventoryManager = CInventoryManager::GetInstance();
	cInventoryItem = cInventoryManager->Add("Tree", "Image/Scene2D_TreeTile.tga", 5, 0);
	cInventoryItem->vec2Size = glm::vec2(25, 25);

	return true;
}

/**
 @brief Update this instance
 */
void CGUI_Scene2D::Update(const double dElapsedTime)
{
	//Start the Dear ImGui Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Invisible Window", NULL, window_flags);
		ImGui::SetWindowPos(ImVec2(0.f, 0.f));
		ImGui::SetWindowSize(ImVec2((float)cSettings->iWindowHeight, (float)cSettings->iWindowWidth));
		ImGui::SetWindowFontScale(1.5f);

		//Display FPS
		ImVec4 col = ImVec4(0.f, 1.0f, 0.f, 1.0f);
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "FPS: %d", cFPSCounter->GetFrameRate());

		m_fProgressBar += 0.001f;
		if (m_fProgressBar > 1.0f)
			m_fProgressBar = 0.f;
		col = ImVec4(0.f, 0.f, 1.f, 1.f);
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, col);
			col = ImVec4(1.0f, 0.f, 0.f, 1.f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, col);
				ImGui::ProgressBar(m_fProgressBar, ImVec2(100.f, 20.f));
			ImGui::PopStyleColor();
		ImGui::PopStyleColor();

	ImGui::End();


	cInventoryItem = cInventoryManager->GetItem("Tree");
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 1.f, 1.f));
		
	ImGuiWindowFlags inventoryWindowFlags = ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("Image", NULL, inventoryWindowFlags);
			ImGui::SetWindowPos(ImVec2(25.0f, 550.0f));
			ImGui::SetWindowSize(ImVec2(200.f, 25.f));
			ImGui::Image((void*)(intptr_t)cInventoryItem->GetTextureID(),
				ImVec2(cInventoryItem->vec2Size.x, cInventoryItem->vec2Size.y),
				ImVec2(0,1), ImVec2(1,0));
			ImGui::SameLine();
			ImGui::SetWindowFontScale(1.5f);
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "Tree: %d / %d",
				cInventoryItem->GetCount(), cInventoryItem->GetMaxCount());
		ImGui::End();
	ImGui::PopStyleColor();


}

/**
 @brief Set up the OpenGL display environment before rendering
 */
void CGUI_Scene2D::PreRender(void)
{
}

/**
 @brief Render this instance
 */
void CGUI_Scene2D::Render(void)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/**
 @brief PostRender Set up the OpenGL display environment after rendering.
 */
void CGUI_Scene2D::PostRender(void)
{
}
