#include <iostream>
#include "shape.hpp"


#pragma region variables
sf::RenderWindow window;
sf::RectangleShape rect;
sf::RectangleShape rect2;
int speed = 10;
sf::Vector2i positionSouris;
sf::Texture perso;
sf::Sprite sprit_perso;
enum Dir{Down, Left, Right, Up};
sf::Vector2i anim(1, Down);
bool updateFPS = true;
int blockSize = 32;
sf::View view;
int screenW = 800, screenH = 600;
#pragma endregion variables

void gestion_clavier();
void gestion_souris();


int main()
{

    window.create(sf::VideoMode(800, 600), "titre de la fenete"); //creer une fenetre de dim 800 et 600
    //modifier la position de la fenetre
    window.setPosition(sf::Vector2i(192,0)); //position de la fenetre sur l'écran
    window.setFramerateLimit(50);

    //dessiner des forme sur la fenetre
    rect = PB_Rect(480,300,32,32);
    rect2 = PB_Rect(1000,1000,32,32);

    sf::Clock time;
    float fpsCount =0, switchFps = 100, fpsSpeed = 500;

    if(!perso.loadFromFile("player.png")){
       std::cerr << "erreur chargement personage\n";
    }
    perso.setSmooth(true);
    sprit_perso.setTexture(perso);
    //conserver le fenetre à l'ecran
    while(window.isOpen()){
        //creer un evenment
        sf::Event event;
        //test des evennement
        while(window.pollEvent(event)){
            //verifier si l'evennemnt permet de fermer la fenetre
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                updateFPS =true;
            }else{
                updateFPS =false;
            }
        }
        //gestion clavier
        gestion_clavier();
        //gestion souris
        gestion_souris();

        if(updateFPS == true){
            if(time.getElapsedTime().asMicroseconds() >= 50){
                anim.x--;
                if(anim.x * blockSize >= perso.getSize().x){
                    anim.x = 2;
                }
                time.restart();

            }
        }

        sprit_perso.setTextureRect(sf::IntRect(anim.x *blockSize, anim.y * blockSize, blockSize, blockSize));

        view.reset(sf::FloatRect(0,0, screenW, screenH));
        sf::Vector2f position(screenW/2, screenH/2);
        position.x = sprit_perso.getPosition().x + (blockSize/2) - (screenW/2);
        position.y = sprit_perso.getPosition().y + (blockSize/2) - (screenH/2);
        if(position.x < 0){
            position.x = 0;
        }
        if(position.y < 0){
            position.y = 0;
        }
        view.reset(sf::FloatRect(position.x,position.y, screenW, screenH));
        window.setView(view);

        window.draw(rect); // attacher la forme à la fenetre
        window.draw(rect2);
        window.draw(sprit_perso);
        window.display(); // afficher les forme sur la fenetre
        window.clear(); //actualiser le contenu de la fenetre
    }

    return 0;
}

void gestion_clavier(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            anim.y = Up;
            //rect.move(0, -speed);
            sprit_perso.move(0, -speed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            anim.y = Down;
            //rect.move(0, speed);
            sprit_perso.move(0, speed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            anim.y = Left;
            //rect.move(-speed, 0);
            sprit_perso.move(-speed, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            anim.y = Right;
            //rect.move(speed, 0);
            sprit_perso.move(speed, 0);
        }
        //gestion des position des perso
        if(sprit_perso.getPosition().x <= 0){
            sprit_perso.setPosition(sf::Vector2f(0, sprit_perso.getPosition().y));
        }
        if(sprit_perso.getPosition().y <= 0){
            sprit_perso.setPosition(sf::Vector2f(sprit_perso.getPosition().x, 0));
        }
}

void gestion_souris(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            positionSouris = sf::Mouse::getPosition(window);
            //rect.setPosition(positionSouris.x-15, positionSouris.y-15);
            sprit_perso.setPosition(positionSouris.x-15, positionSouris.y-15);
        }
}
