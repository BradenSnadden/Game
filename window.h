#pragma once
#include <SFML/Graphics.hpp>
#include<string>

class window{
private:

public:
    window();
    window(const std::string title, const sf::Vector2u& size);
    ~window();
    void begin();
    void end();
    void update();
    bool isDone();
    bool isFullScreen();
    sf::Vector2u getSize();
    void toggleFullScreen();
    void draw(sf::Drawable &drawing);
    sf::RenderWindow* GetRenderWindow();

private:
    void setup(std::string title, const sf::Vector2u& size);
    void destroy();
    void create();
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_title;
    bool m_isDone;
    bool m_isFullscreen;
};

window::window(){
    setup("Window", sf::Vector2u(640,480));
}

window::window(const std::string title, const sf::Vector2u& size){
    setup(title, size);
}

window::~window(){
    destroy();
}

void window::setup(std::string title, const sf::Vector2u& size){

    m_title = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isDone = false;
    create();

}

void window::create(){

    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y}, m_title, style);

}

void window::destroy(){
    m_window.close();
}

void window::update(){

    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_isDone = true;
        }else if(event.type == event.KeyPressed && event.key.code ==  sf::Keyboard::F5){
            toggleFullScreen();
        }
    }

}

void window::toggleFullScreen(){
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

void window::begin(){
    m_window.clear(sf::Color::Black);
}

void window::end(){
    m_window.display();
}

bool window::isDone(){
    return m_isDone;
}

bool window::isFullScreen(){
    return m_isFullscreen;
}

sf::Vector2u window::getSize(){
    return m_windowSize;
}

void window::draw(sf::Drawable &drawing){
    m_window.draw(drawing);
}

sf::RenderWindow* window::GetRenderWindow() {
     return &m_window; 
}

