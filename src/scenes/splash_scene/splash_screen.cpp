#include <stdio.h>

#include <raylib.h>
#include "scene_splash_screen.hpp"
#include "../../librocket/sync.h"

SceneSplashScreen::SceneSplashScreen(SceneStateMachine& sceneStateMachine) 
    : sceneStateMachine(sceneStateMachine),
      switchToState(0),
      currentSeconds(0.f),
      showForSeconds(3000.0f)
      /* We’ll show this splash screen for 3 seconds. */
{ } 

void SceneSplashScreen::OnCreate() 
{

    printf("IS THIS BEING CALLED? \n");
	// We’ll initialise our splash screen image here.
	
    //splashTexture.loadFromFile(workingDir.Get() 
							   //+ "that_games_guy_logo.png");
    //splashSprite.setTexture(splashTexture);
    
    //sf::FloatRect spriteSize = splashSprite.getLocalBounds();
	
	//// Set the origin of the sprite to the centre of the image:
    //splashSprite.setOrigin(spriteSize.width * 0.5f, 
						   //spriteSize.height * 0.5f); 
    //splashSprite.setScale(0.5f, 0.5f);
    
    //sf::Vector2u windowCentre = window.GetCentre();
	
	// Positions sprite in centre of screen:
    //splashSprite.setPosition(windowCentre.x, windowCentre.y); 
}

void SceneSplashScreen::OnActivate()
{
	// Resets the currentSeconds count whenever the scene is activated.
	currentSeconds = 0.f; 
}

void SceneSplashScreen::OnDestroy() { }

void SceneSplashScreen::ProcessInput()
{
    if ( IsKeyDown(KEY_SPACE) )
    {
        printf("SPACE IS PRESSED\n");
    }
}

void SceneSplashScreen::SetSwitchToScene(unsigned int id) 
{
	// Stores the id of the scene that we will transition to.
    switchToState = id; 
}

void SceneSplashScreen::Update(float deltaTime)
{
    currentSeconds += deltaTime;
    
    if(currentSeconds >= showForSeconds) 
    {
		// Switches states.
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneSplashScreen::Draw()
{
    const int screenWidth = 1024;
    const int screenHeight = 600;

    const Color BACKGROUND = {60, 80, 120};
    const Color cube_color = {230, 47, 230, 255};

    Vector3 enemySpherePos = { 0.0f, 0.0f, 5.0f };
    Camera camera = { 
        { 0.0f, 12.0f, -10.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f }, 
        90.0f, 0 
    };

    ClearBackground(BACKGROUND);
    BeginMode3D(camera);

        DrawCube(enemySpherePos, 10.0f, 10.0f, 10.0f, cube_color);
        //DrawGrid(10, 1.0f);        // Draw a grid

    EndMode3D();
    //DrawText("GAME OVER..", screenWidth / 3.0, screenHeight / 2.0, 68, WHITE);
}
