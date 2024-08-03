#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

enum direction {
    LEFT, RIGHT, UP, DOWN, STOPED
};

void drawMap(sf::RenderWindow *window, sf::Sprite *mapSprite, sf::Sprite *appleSprite, int apple_posX, int apple_posY) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    mapSprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
                } else {
                    mapSprite->setTextureRect(sf::IntRect(0, 32, 32, 32));
                }
            } else {
                if (j % 2 == 0) {
                    mapSprite->setTextureRect(sf::IntRect(0, 32, 32, 32));
                } else {
                    mapSprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
                }
            }
            mapSprite->setPosition((float) j * 32, (float) i * 32);
            window->draw(*mapSprite);
            if (i == apple_posX && j == apple_posY) {
                appleSprite->setPosition((float) j * 32, (float) i * 32);
                window->draw(*appleSprite);
            }
        }
    }
}

void updateSnakeDirection(direction *dir) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        *dir = LEFT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        *dir = RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        *dir = UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        *dir = DOWN;
    }
}

void snakeMovement(sf::Clock *clock, direction *snakeDirection, int *snake_posX, int *snake_posY){
    if (clock->getElapsedTime().asSeconds() >= 0.7f) {
        if (*snakeDirection == UP) {
            *snake_posY -= 1;
        } else if (*snakeDirection == DOWN) {
            *snake_posY += 1;
        } else if (*snakeDirection == RIGHT) {
            *snake_posX += 1;
        } else if (*snakeDirection == LEFT) {
            *snake_posX -= 1;
        }
        if (*snake_posY < 0) {
            *snake_posY = 13;
        }
        if (*snake_posX < 0) {
            *snake_posX = 13;
        }
        if (*snake_posY > 13) {
            *snake_posY = 0;
        }
        if (*snake_posX > 13) {
            *snake_posX = 0;
        }
        clock->restart();
    }
}


void snakeRender(sf::Sprite *snakeHeadSprite, sf::Sprite *snakeBodySprite, sf::Sprite *snakeTailSprite, int snake_posX, int snake_posY, direction snakeDirection, sf::RenderWindow *window){
    if(snakeDirection == STOPED || snakeDirection == UP) {
        snakeBodySprite->setRotation(0);
        snakeTailSprite->setRotation(0);
        snakeHeadSprite->setRotation(0);
        snakeHeadSprite->setPosition(snake_posX * 32, (snake_posY) * 32);
        snakeBodySprite->setPosition(snake_posX * 32, (snake_posY + 1) * 32);
        snakeTailSprite->setPosition(snake_posX * 32, (snake_posY + 2) * 32);
    }else if(snakeDirection == DOWN){
        snakeHeadSprite->setPosition(snake_posX * 32, (snake_posY) * 32);
        snakeBodySprite->setPosition(snake_posX * 32, (snake_posY - 1) * 32);
        snakeTailSprite->setPosition(snake_posX * 32, (snake_posY - 2) * 32);
        snakeHeadSprite->setRotation(180);
        snakeBodySprite->setRotation(180);
        snakeTailSprite->setRotation(180);
    }else if(snakeDirection == LEFT){
        snakeHeadSprite->setPosition(snake_posX * 32, snake_posY * 32);
        snakeBodySprite->setPosition((snake_posX+1) * 32, snake_posY * 32);
        snakeTailSprite->setPosition((snake_posX+2) * 32, snake_posY * 32);
        snakeHeadSprite->setRotation(270);
        snakeBodySprite->setRotation(270);
        snakeTailSprite->setRotation(270);
    }else if(snakeDirection == RIGHT){
        snakeHeadSprite->setPosition(snake_posX * 32, snake_posY * 32);
        snakeBodySprite->setPosition((snake_posX-1) * 32, snake_posY * 32);
        snakeTailSprite->setPosition((snake_posX-2) * 32, snake_posY * 32);
        snakeHeadSprite->setRotation(90);
        snakeBodySprite->setRotation(90);
        snakeTailSprite->setRotation(90);
    }

    window->draw(*snakeHeadSprite);
    window->draw(*snakeBodySprite);
    window->draw(*snakeTailSprite);
}

int main() {
    std::srand(time(NULL));

    sf::Clock clock;

    sf::Image mapImage;
    mapImage.loadFromFile("Resources/Sprites/Map/Full_map_32.png");
    sf::Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    sf::Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    sf::Image appleImage;
    appleImage.loadFromFile("Resources/Sprites/Map/Full_map_32.png");
    sf::Texture appleTexture;
    appleTexture.loadFromImage(appleImage);
    sf::Sprite appleSprite;
    appleSprite.setTexture(appleTexture);
    appleSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
    int apple_posX = rand() % 16;
    int apple_posY = rand() % 16;

    int snake_posX = 8;
    int snake_posY = 11;
    sf::Image snakeImg;
    snakeImg.loadFromFile("Resources/Sprites/Snake/Full_snake32.png");
    sf::Texture snakeTexture;
    snakeTexture.loadFromImage(snakeImg);
    direction snakeDirection = STOPED;

    sf::Sprite snakeHeadSprite;
    snakeHeadSprite.setTexture(snakeTexture);
    snakeHeadSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    sf::Sprite snakeBodySprite;
    snakeBodySprite.setTexture(snakeTexture);
    snakeBodySprite.setTextureRect(sf::IntRect(0, 32, 32, 32));

    sf::Sprite snakeTailSprite;
    snakeTailSprite.setTexture(snakeTexture);
    snakeTailSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));

    sf::RenderWindow window(sf::VideoMode(512, 512), "SNAKE!");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        drawMap(&window, &mapSprite, &appleSprite, apple_posX, apple_posY);
        snakeMovement(&clock, &snakeDirection, &snake_posX, &snake_posY);
        updateSnakeDirection(&snakeDirection);
        snakeRender(&snakeHeadSprite, &snakeBodySprite, &snakeTailSprite, snake_posX, snake_posY, snakeDirection, &window);

        window.display();
    }

    return 0;
}