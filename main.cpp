#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <iostream>

int main(){
    srand(time(NULL));
    int i = 0;
    int j = 0,k = 100,l = 200;
    float CDS = 0;
    bool flag = 0;
    int screenX = 1280, screenY = 720;
    sf::RenderWindow window(sf::VideoMode(screenX,screenY), "Idle Too");
    sf::Texture CD;
    CD.loadFromFile("sprites/CD.png"); 
    sf::Sprite CrazyD(CD);
    sf::Vector2u size = CD.getSize();
    CrazyD.setOrigin(size.x/2, size.y/2);
    CrazyD.setPosition(400,400);
    sf::Vector2f velocity (0.5f, 0.5f);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        
        if(flag){CDS += 0.001;}
        else{CDS-=0.001;}
        CrazyD.setPosition(CrazyD.getPosition() + velocity);
        if(CrazyD.getPosition().x - CrazyD.getScale().x * (size.x)/2 <= 0 || CrazyD.getPosition().x + CrazyD.getScale().x * size.x/2>= screenX){
            velocity.x *= -1;
        }
        if(CrazyD.getPosition().y - CrazyD.getScale().y * (size.y)/2 <= 0 || CrazyD.getPosition().y + CrazyD.getScale().y * size.y/2 >= screenY ){
            velocity.y *= -1;
            
        }
        CrazyD.setScale(CDS,CDS);
        if(CDS >= 4){flag = 0;}
        if(CDS <=0.25){flag = 1;}

        std::cout << CrazyD.getPosition().y << "     " << CrazyD.getScale().y * size.y/2 <<  std::endl;
        window.clear(sf::Color::Black);
        window.draw(CrazyD);
        
        window.display();
    }

    return 1;

}