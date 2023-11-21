#pragma once
#include "window.h"
#include "world.h"
#include "snake.h"

class game{
    public:
        game();
        void handleIn();
        void update();
        void render();
        window* getWindow();
        sf::Time getElapsed();
        void restartClock();


        
    private:
        void moveCD();
        window m_window;
        sf::Texture m_CDTexture;
        sf::Sprite m_CD;
        sf::Vector2f m_increment;
        sf::Clock m_clock;
        sf::Time m_elapsed;
        world m_world;
        snake m_snake;

};

window* game::getWindow(){
    return &m_window;
}

void game::handleIn(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetDirection() != Direction::Down){
        m_snake.SetDirection(Direction::Up);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetDirection() != Direction::Up){
        m_snake.SetDirection(Direction::Down);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetDirection() != Direction::Right){
        m_snake.SetDirection(Direction::Left);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetDirection() != Direction::Left){
        m_snake.SetDirection(Direction::Right);
    }
}

game::game() : m_window("Snake", sf::Vector2u(800,600)),m_snake(m_world.GetBlockSize()),m_world(sf::Vector2u(800,600)){
    m_CDTexture.loadFromFile("sprites/CD.png");
    m_CD.setTexture(m_CDTexture);
    m_increment = sf::Vector2f(4,4);

}

void game::update(){
    float timestep = 1.0f / m_snake.GetSpeed();
    if(m_elapsed.asSeconds() >= timestep){
        m_snake.Tick();
        m_world.WUpdate(m_snake);
        m_elapsed -= sf::seconds(timestep);
        if(m_snake.HasLost()){
            m_snake.Reset();
        }
    }
    m_window.update();
    moveCD();
}

void game::moveCD(){

    sf::Vector2u l_windSize = m_window.getSize();
    sf::Vector2u l_textSize = m_CDTexture.getSize();
    if((m_CD.getPosition().x > l_windSize.x - l_textSize.x&&m_increment.x> 0) || (m_CD.getPosition().x < 0 &&m_increment.x< 0)){
        m_increment.x = -m_increment.x;
    }
    if((m_CD.getPosition().y > l_windSize.y - l_textSize.y&&m_increment.y> 0) || (m_CD.getPosition().y < 0 &&m_increment.y< 0)){
        m_increment.y = -m_increment.y;
    }
    
   float frametime = 1.0f / 60.0f;
   if(m_elapsed.asSeconds() >= frametime){
        m_CD.setPosition(m_CD.getPosition().x + m_increment.x, m_CD.getPosition().y + m_increment.y);
        m_elapsed -= sf::seconds(frametime);
   }

}



void game::render(){
    m_window.begin();
    
    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());
    m_window.end();
}

sf::Time game::getElapsed(){
    return m_elapsed; 
}

void game::restartClock(){ 
    m_elapsed += m_clock.restart();
}


