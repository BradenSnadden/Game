#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "game.h"

int main(){
    game game;
    while(1){
        game.update();
        game.render();
        //sf::sleep(sf::seconds(0.2));
        game.restartClock();
    }

    return 1;

}