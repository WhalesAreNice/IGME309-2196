#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	//Generate a circle
	//m_pMesh->GenerateCircle(2.0f, 5, C_RED);
	//m_pMesh->AddTri(vector3(-1.0f, -1.0f, 0.0f),
	//	vector3(1.0f, -1.0f, 0.0f),
	//	vector3(0.0f, 1.0f, 0.0f));

	int sides = 12;
	float currentAngle = 0.0f;
	float plusAngle = 2.0f*PI / sides;
	float radius = 1.0f;

	for (int i = 0; i < sides; i++) {
		m_pMesh->AddTri(vector3(0.0f, 0.0f, 0.0f),
			vector3(radius * cos(currentAngle), radius * sin(currentAngle), 0.0f),
			vector3(radius * cos(currentAngle + plusAngle), radius * sin(currentAngle + plusAngle), 0.0f));

		currentAngle += plusAngle;
	}
		



	m_pMesh->CompileOpenGL3X();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Render the mesh
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Safely release the memory
	SafeDelete(m_pMesh);
	//release GUI
	ShutdownGUI();
}