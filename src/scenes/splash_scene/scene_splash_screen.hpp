#ifndef SceneSplashScreen_hpp
#define SceneSplashScreen_hpp

#include "scene_state_machine.hpp"

class SceneSplashScreen : public Scene
{
public:
    SceneSplashScreen(SceneStateMachine& sceneStateMachine);

    void OnCreate() override;
    void OnDestroy() override;
    
    void OnActivate() override;
        
    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw() override;

    void ProcessInput() override;
    
private:
    SceneStateMachine& sceneStateMachine;
    
	// We want to show this scene for a set amount of time
    float showForSeconds;
	
	// How long the scene has currently been visible.
    float currentSeconds;

	// The state we want to transition to when this scenes time expires.
    unsigned int switchToState;
};

#endif /* SceneSplashScreen_hpp */
