#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
#include <cassert>

using namespace sf;

unsigned long seed = 1;
const int sizeTs = 25;
const int WIDTHFIELD = 30;
const int HEIGHTFIELD = 20;
const int SPEED = 100;

RenderWindow window(VideoMode(sizeTs * WIDTHFIELD, sizeTs * HEIGHTFIELD), "Snake!");

int my_rand(int max) {
    seed = seed * 1103515245 + 12345;  // Линейный конгруэнтный метод
    return (seed / 65536) % max;
}

class Fruct {
public:
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void positionSelect() {
        x = my_rand(WIDTHFIELD);
        y = my_rand(HEIGHTFIELD);
    }
    void positionSelect(int newX, int newY) {
        x = newX;
        y = newY;
    }
private:
    int x, y;
};

class Snake {
public:
    int getSize() {
        return size;
    }
    void setSize(int newSize) {
        size = newSize;
    }
    int getDirection() {
        return direction;
    }
    int getX(int i) {
        return s[i].x;
    }
    int getY(int i) {
        return s[i].y;
    }
    void setX(int i, int newX) {
        s[i].x = newX;
    }
    void setY(int i, int newY) {
        s[i].y = newY;
    }
    void setDirection(int i) {
        direction = i;
    }
    void eatFruct(Fruct &fruct) {
        if ((s[0].x == fruct.getX()) && (s[0].y) == fruct.getY()) {
            size++;

            fruct.positionSelect();
        }
    }
    void move() {}
    void oversteppingBoundaries() {
        if (s[0].x > WIDTHFIELD - 1)
            s[0].x = 0;
        if (s[0].x < 0)
            s[0].x = WIDTHFIELD - 1;
        if (s[0].y > HEIGHTFIELD - 1)
            s[0].y = 0;
        if (s[0].y < 0)
            s[0].y = HEIGHTFIELD - 1;
    }
    boolean collision() {}
protected:
    struct partPosition {
        int x, y;
    } s[600];
    int size = 4;
    int direction = 2;
};

class SnakeFirst : public Snake {
public:
    SnakeFirst() {
        for (int i = 0; i < size; i++) {
            s[i].x = 4 - i;
            s[i].y = 0;
        }
    }
    void move() {
        //Управление змейкой через клавиатуру
        if (Keyboard::isKeyPressed(Keyboard::A) && direction != 2) //Если стрелка влево нажата
            direction = 1;
        if (Keyboard::isKeyPressed(Keyboard::D) && direction != 1) //Если стрелка вправо нажата
            direction = 2;
        if (Keyboard::isKeyPressed(Keyboard::W) && direction != 0) //Если стрелка вверх нажата
            direction = 3;
        if (Keyboard::isKeyPressed(Keyboard::S) && direction != 3)  //Если стрелка вниз нажата
            direction = 0;

        for (int i = size; i > 0; i--) {
            s[i].x = s[i - 1].x;
            s[i].y = s[i - 1].y;
        }

        //движение змейки
        if (direction == 0)
            s[0].y = s[0].y + 1; //вниз
        if (direction == 3)
            s[0].y = s[0].y - 1; //вверх
        if (direction == 2)
            s[0].x = s[0].x + 1; //право
        if (direction == 1)
            s[0].x = s[0].x - 1; //влево
    }
    boolean collision(Snake snakeSecond) {
        for (int i = 1; i < size; i++) //цикл for для всех плиток змейки
            //Если змейка сталкивается со своим телом
            if (s[0].x == s[i].x && s[0].y == s[i].y)
                return true;
        for (int i = 1; i < snakeSecond.getSize(); i++) //цикл for для всех плиток змейки
            //Если змейка сталкивается со своим телом
            if (s[0].x == snakeSecond.getX(i) && s[0].y == snakeSecond.getY(i))
                return true;
        return false;
    }
};

class SnakeSecond : public Snake {
public:
    SnakeSecond() {
        for (int i = 0; i < size; i++) {
            s[i].x = 4 - i;
            s[i].y = 19;
        }
    }
    void move() {
        //Управление змейкой через клавиатуру
        if (Keyboard::isKeyPressed(Keyboard::Left) && direction != 2) //Если стрелка влево нажата
            direction = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && direction != 1) //Если стрелка вправо нажата
            direction = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && direction != 0) //Если стрелка вверх нажата
            direction = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && direction != 3)  //Если стрелка вниз нажата
            direction = 0;

        for (int i = size; i > 0; i--) {
            s[i].x = s[i - 1].x;
            s[i].y = s[i - 1].y;
        }

        //движение змейки
        if (direction == 0)
            s[0].y = s[0].y + 1; //вниз
        if (direction == 3)
            s[0].y = s[0].y - 1; //вверх
        if (direction == 2)
            s[0].x = s[0].x + 1; //право
        if (direction == 1)
            s[0].x = s[0].x - 1; //влево
    }

    boolean collision(Snake snakeFirst) {
        for (int i = 1; i < size; i++) //цикл for для всех плиток змейки
            //Если змейка сталкивается со своим телом
            if (s[0].x == s[i].x && s[0].y == s[i].y)
                return true;
        for (int i = 1; i < snakeFirst.getSize(); i++) //цикл for для всех плиток змейки
            //Если змейка сталкивается со своим телом
            if (s[0].x == snakeFirst.getX(i) && s[0].y == snakeFirst.getY(i))
                return true;
        return false;
    }
};

class Field {
public:
    Field() {
        //Ставим картинку tiles
        t.loadFromFile("C:/Users/Savva/Desktop/ООП/snake/Snake/Snake/tiles.png");
        tiles.setTexture(t);

        //Ставим картинку змейки
        sn.loadFromFile("C:/Users/Savva/Desktop/ООП/snake/Snake/Snake/snake.png");
        snakeSprite.setTexture(sn);
        snTwo.loadFromFile("C:/Users/Savva/Desktop/ООП/snake/Snake/Snake/snakeTwo.png");
        snakeSpriteTwo.setTexture(snTwo);

        //Ставим картинку яблоко
        ap.loadFromFile("C:/Users/Savva/Desktop/ООП/snake/Snake/Snake/apple.png");
        apple.setTexture(ap);

        //Ставим надпись gameover
        go.loadFromFile("C:/Users/Savva/Desktop/ООП/snake/Snake/Snake/gameover.png");
        gameover.setTexture(go);
    }
    void draw(Snake &snakeOne, Snake &snakeTwo, Fruct &fruct) {
        window.clear();
        // Отрисовка поля
        for (int i = 0; i < WIDTHFIELD; i++) {
            for (int j = 0; j < HEIGHTFIELD; j++) {
                tiles.setPosition(i * sizeTs, j * sizeTs); //Позиция
                window.draw(tiles); //Рисуем
            }
        }
        // Отрисовка змеи
        for (int i = 0; i < snakeTwo.getSize(); i++) {
            if (i != 0) //Рисуем тело змейки
                snakeSprite.setTextureRect(IntRect(1, 1, sizeTs, sizeTs));
            else //Рисуем голову змейки
                snakeSprite.setTextureRect(IntRect(snakeTwo.getDirection() * sizeTs, sizeTs, sizeTs, sizeTs));
            snakeSprite.setPosition(snakeTwo.getX(i) * sizeTs, snakeTwo.getY(i) * sizeTs); //Задаём позицию
            //для плиток змейки
            window.draw(snakeSprite);
        }

        for (int i = 0; i < snakeOne.getSize(); i++) {
            if (i != 0) //Рисуем тело змейки
                snakeSpriteTwo.setTextureRect(IntRect(1, 1, sizeTs, sizeTs));
            else //Рисуем голову змейки
                snakeSpriteTwo.setTextureRect(IntRect(snakeOne.getDirection() * sizeTs, sizeTs, sizeTs, sizeTs));
            snakeSpriteTwo.setPosition(snakeOne.getX(i) * sizeTs, snakeOne.getY(i) * sizeTs); //Задаём позицию
            //для плиток змейки
            window.draw(snakeSpriteTwo);
        }

        apple.setPosition(fruct.getX() * sizeTs, fruct.getY() * sizeTs); //Позиция яблоки
        window.draw(apple);

        window.display();
    }
    void drawGameover(Snake &snake, int playerLost) {
        window.draw(gameover);
        if (playerLost == 2) {
            snakeSprite.setPosition(snake.getX(1) * sizeTs, snake.getY(1) * sizeTs);
            snakeSprite.setTextureRect(IntRect(0, sizeTs * 2, sizeTs, sizeTs));
            window.draw(snakeSprite);
        }
        if (playerLost == 1) {
            snakeSpriteTwo.setPosition(snake.getX(1) * sizeTs, snake.getY(1) * sizeTs);
            snakeSpriteTwo.setTextureRect(IntRect(0, sizeTs * 2, sizeTs, sizeTs));
            window.draw(snakeSpriteTwo);
        }
        window.display();
    }
private:
    Texture t;
    Sprite tiles;
    Texture sn;
    Sprite snakeSprite;
    Texture snTwo;
    Sprite snakeSpriteTwo;
    Texture ap;
    Sprite apple;
    Texture go;
    Sprite gameover;
};

class Game {
public:
    void play() {
        fruct.positionSelect(15, 10);
        while (playerLost == 0) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                    window.close();
                    exit(0);
                }
            }

            snakeFirst.move();
            snakeFirst.oversteppingBoundaries();
            snakeFirst.eatFruct(fruct);

            snakeSecond.move();
            snakeSecond.oversteppingBoundaries();
            snakeSecond.eatFruct(fruct);
         
            field.draw(snakeFirst, snakeSecond, fruct);
            if (snakeFirst.collision(snakeSecond))
                playerLost = 1;
            if (snakeSecond.collision(snakeFirst))
                playerLost = 2;
            Sleep(SPEED);
        }
    }
    void gameOver() {
        if (playerLost == 1)
            field.drawGameover(snakeFirst, playerLost);
        if (playerLost == 2)
            field.drawGameover(snakeSecond, playerLost);
        while (window.isOpen()) {
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                playerLost = 0;
                snakeFirst.setSize(4);
                snakeFirst.setDirection(2);
                for (int i = 0; i < snakeFirst.getSize(); i++) {
                    snakeFirst.setX(i, 4 - i);
                    snakeFirst.setY(i, 0);
                }
                snakeSecond.setSize(4);
                snakeSecond.setDirection(2);
                for (int i = 0; i < snakeSecond.getSize(); i++) {
                    snakeSecond.setX(i, 4 - i);
                    snakeSecond.setY(i, 19);
                }
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                exit(0);
            }
        }
    }
private:
    int playerLost = 0;
    SnakeFirst snakeFirst;
    SnakeSecond snakeSecond;
    Fruct fruct;
    Field field;
};

int main() {
    Game game;

    while (1) {
        game.play();
        game.gameOver();
    }
    return 0;
}