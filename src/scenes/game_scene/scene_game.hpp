#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "scene.hpp"
//#include "Input.hpp"
//#include "WorkingDirectory.hpp"

class SceneGame : public Scene
{
public:
    SceneGame();
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw() override;
    
private:
    //sf::Texture vikingTexture;
    //sf::Sprite vikingSprite;
    
    //WorkingDirectory& workingDir;
    //Input input;
};

#endif /* SceneGame_hpp */
