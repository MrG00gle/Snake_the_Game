#include <SFML/Graphics.hpp>
#include <stdlib.h>

const int  FIELD_CELL_TYPE_APPLE = -1;
const int FIELD_CELL_TYPE_NONE = 0;
const int FSizeX = 35;
const int FSizeY = 25;
const int CSize = 32;
const int WWidth = FSizeX * CSize;
const int WHeight = FSizeY * CSize;

enum SnakeDir{LEFT,RIGHT,UP,DOWN};
SnakeDir dir = RIGHT;


int Field[FSizeY][FSizeX];
int posSnakeX = FSizeX / 2;
int posSnakeY = FSizeY / 2;
int lengSnake = 4;
bool game_over = false;

int getRandomEmptyCell()
{
    int emptyCellCount = 0;
    for (int j = 0; j < FSizeY; ++j)
    {
        for (int i = 0; i < FSizeX; ++i)
        {
            if (Field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                emptyCellCount++;
            };
        }
    }
    int targetemptyCellIndex = rand() % emptyCellCount;
    int emptyCellIndex = 0;
    for (int j = 0; j < FSizeY; ++j)
    {
        for (int i = 0; i < FSizeX; ++i)
        {
            if (emptyCellIndex == targetemptyCellIndex)
            {
                return j * FSizeX + i;
            };
            emptyCellIndex++;
        }
    }
    return -1;
}

void setApple()
{
    int posApple = getRandomEmptyCell();
    if (posApple != -1)
    {
        //
    }
    Field[posApple / FSizeX][posApple % FSizeX] = FIELD_CELL_TYPE_APPLE;
}

void clearField()
{
    for (int j = 0; j < FSizeY; ++j)
    {
        for (int i = 0; i < FSizeX; ++i)
        {
            Field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }

    for (int i = 0; i < lengSnake; ++i)
    {
        Field[posSnakeY][posSnakeX - i] = lengSnake - i;
    }

    setApple();
}

void drawField(sf::RenderWindow & window)
{
    sf::Texture snake_texture;
    snake_texture.loadFromFile("/home/kms/Documents/CLionProjects/Snake_2.0/images/snake.png");
    sf::Sprite snake;
    snake.setTexture(snake_texture);


    sf::Texture none_texture;
    none_texture.loadFromFile("/home/kms/Documents/CLionProjects/Snake_2.0/images/none.png");
    sf::Sprite none;
    none.setTexture(none_texture);

    sf::Texture apple_texture;
    apple_texture.loadFromFile("/home/kms/Documents/CLionProjects/Snake_2.0/images/apple.png");
    sf::Sprite apple;
    apple.setTexture(apple_texture);

    for (int j = 0; j < FSizeY; ++j)
    {
        for (int i = 0; i < FSizeX; ++i)
        {
            switch (Field[j][i])
            {
                case FIELD_CELL_TYPE_NONE:
                    none.setPosition(float(i * CSize), float(j * CSize));
                    window.draw(none);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    apple.setPosition(float(i * CSize), float(j * CSize));
                    window.draw(apple);
                    break;
                default:
                    snake.setPosition(float(i * CSize), float(j * CSize));
                    window.draw(snake);
                    break;
            }
        }
    }
}

void makeMove()
{
    switch (dir)
    {
        case UP:
            posSnakeY--;
            if(posSnakeY < 0)
            {
                posSnakeY = FSizeY - 1;
            }
            break;
        case LEFT:
            posSnakeX--;
            if(posSnakeX < 0)
            {
                posSnakeX = FSizeX - 1;
            }
            break;
        case RIGHT:
            posSnakeX++;
            if(posSnakeX > FSizeX - 1)
            {
                posSnakeX = 0;
            }
            break;
        case DOWN:
            posSnakeY++;
            if(posSnakeY > FSizeY - 1)
            {
                posSnakeY = 0;
            }
            break;
    }

    if (Field[posSnakeY][posSnakeX] != FIELD_CELL_TYPE_NONE)
    {
        switch (Field[posSnakeY][posSnakeX])
        {
            case FIELD_CELL_TYPE_APPLE:
                lengSnake++;
                setApple();
                break;
            default:
                game_over = true;
        }
    }

        Field[posSnakeY][posSnakeX] = lengSnake + 1;

            for (int j = 0; j < FSizeY; ++j)
            {
                for (int i = 0; i < FSizeX; ++i)
                {
                    if(Field[j][i] > FIELD_CELL_TYPE_NONE)
                    {
                        Field[j][i]--;
                    }
                }
            }

}

void handle_controles()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (dir != DOWN)
        {
            dir = UP;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (dir != UP)
        {
            dir = DOWN;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (dir != RIGHT)
        {
            dir = LEFT;
        };
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(dir != LEFT)
        {
            dir = RIGHT;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (dir != DOWN)
        {
            dir = UP;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (dir != UP)
        {
            dir = DOWN;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (dir != RIGHT)
        {
            dir = LEFT;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {   if(dir != LEFT)
        {
            dir = RIGHT;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        game_over = true;
    }
}


int main()
{
    srand(time(NULL));
    // create the window
    sf::RenderWindow window(sf::VideoMode(WWidth, WHeight), "Snake", sf::Style::Close );

    clearField();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        handle_controles();

        makeMove();

        if (game_over == true)
        {
            window.close();
        }

        // clear the window with black color
        window.clear(sf::Color(183,212,168));

        drawField(window);

        // end the current frame
        window.display();

        sf::sleep(sf::milliseconds(200));
    }

    return 0;
}
