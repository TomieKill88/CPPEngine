#include <SFML/Graphics.hpp>

#include "GeoWarsPauseScene.hpp"
#include "GameEngine.hpp"

namespace Scene
{
    void GeoWarsPauseScene::registerActions()
    {
        registerAction(GameEngine::Input::InputCode::KEYBOARD_ENTER, ActionTypeEnum::START);
    }   

	GeoWarsPauseScene::GeoWarsPauseScene(GameEngine::GameEngine* gameEngine) : BaseScene(gameEngine)
	{
        registerActions();

       
	}

	void GeoWarsPauseScene::update() 
	{
        ++mFrameCounter;
    }

	void GeoWarsPauseScene::doAction(Action pAction)
	{
        if (pAction.getState() == ActionStateEnum::END)
        {
            if (pAction.getType() == ActionTypeEnum::START)
            {
                mGameEngine->changeScene(std::string("Main"));
            }
        }
	}
	
    void GeoWarsPauseScene::sRender() 
	{
        sf::Text mPauseLabel(mGameEngine->mFontsData.font);
        mPauseLabel.setString(sf::String("PAUSE"));
        mPauseLabel.setCharacterSize(mGameEngine->mFontsData.fontsize);
        mPauseLabel.setFillColor(mGameEngine->mFontsData.fontcolor);
        mPauseLabel.setOrigin(mPauseLabel.getLocalBounds().getCenter());
        mPauseLabel.setPosition(sf::Vector2f(mGameEngine->mWindowData.width/2, mGameEngine->mWindowData.height/2));
        mGameEngine->getWindow().draw(mPauseLabel);
    }    
}