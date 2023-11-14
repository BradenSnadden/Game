#ifndef define
#include <SFML/Graphics.hpp>
#include<string>

class window
{
private:

public:
    window();
    window(int sizeX, int sizeY, std::string title);
    ~window();
    void begin();
    void end();
    void update();
    bool isDone();
    bool fullScreen();
    sf::Vector2u getSize();
    void toggleFullScreen();
    void draw(sf::Drawable drawing);
    


};

window::window(/* args */)
{
}

window::~window()
{
}

#endif