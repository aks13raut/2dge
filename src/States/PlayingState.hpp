#pragma once

#include <vector>

#include "State.hpp"
#include "../GameLogic/GameObject.hpp"
#include "../Graphics/TileArray.hpp"
#include "../Graphics/OrthoLayer.hpp"

/**
    Game state for the main part of the game
*/
class PlayingState : public State
{
     public:
        PlayingState(Game& game);

        void handleEvent    (sf::Event e)                   override;
        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        sf::View m_view;
        GameObject player;
        sf::Clock m_clock;
        int m_score;
        sf::Text scoreDisplay;
        std::vector<MapLayer*> layers; 
        std::vector<GameObject*> m_objects;
        std::vector<GameObject*> collisonObjects;
        std::vector<GameObject*> collectableObjects;

        sf::Vector2u limit;
};
