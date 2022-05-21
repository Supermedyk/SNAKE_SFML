//////////////// STILL WORKING ON IT ///////////////////






#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

char gameTab[8][8] = {0};

deque<pair<int,int>> moves;

sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));

bool gameWon()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (gameTab[i][j] != 2)
                return false;
        }
    }
    return true;
}

void generateStart(int &x, int &y)
{
    int counter = 0;
    do
    {
        x = rand()%8;
        y = rand()%8;
        counter++;
    }
    while(gameTab[x][y] != 0);
    gameTab[x][y] = 2;

}

void generateFood()
{
    int x,y;
    int counter = 0;
    do
    {
        x = rand()%8;
        y = rand()%8;
        counter++;
    }
    while(gameTab[x][y] != 0 && counter != 64);
    if (counter != 64)
        gameTab[x][y] = 1;
}

void draw(sf::RenderWindow &window)
{
    float posX = 0.0f,posY = 0.0f;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rectangle.setPosition(posX,posY);
            if (gameTab[i][j] == 0)
            {
                rectangle.setFillColor({111,111,111});
            }
            else if (gameTab[i][j] == 1)
            {
                rectangle.setFillColor(sf::Color::Green);
            }
            else
            {
                rectangle.setFillColor(sf::Color::Blue);
            }
            window.draw(rectangle);
            posX+=100.0f;
        }
        posY+=100.0f;
        posX =0.0f;
    }
}

int main()
{
    int x = 0, y = 0;
    int lastMove = 1;

    srand(time(NULL));
    rectangle.setOutlineThickness(10.f);
    rectangle.setOutlineColor(sf::Color(10, 10, 100));
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(800,800),"Snake made by Super medyk",sf::Style::Close);
    window.setFramerateLimit(10);
    generateStart(x,y);
    moves.push_front({x,y});
    generateFood();
    while(window.isOpen())
    {
        bool press = false;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                moves.clear();
                return 0;
                break;
            case sf::Event::KeyPressed:
                if (press == false)
                {
                    switch(event.key.code)
                    {
                    case sf::Keyboard::A:
                        if (lastMove != 2)
                        {
                            lastMove = 1;
                            press = true;
                        }
                        break;
                    case sf::Keyboard::D:
                        if (lastMove != 1)
                        {
                            lastMove = 2;
                            press = true;
                        }
                        break;
                    case sf::Keyboard::W:
                        if (lastMove != 4)
                        {
                            press = true;
                            lastMove = 3;
                        }
                        break;
                    case sf::Keyboard::S:
                        if (lastMove != 3)
                        {
                            press = true;
                            lastMove = 4;
                        }
                        break;
                    }
                }
                break;
            }
        }
        switch (lastMove)
        {
        case 1:
            y--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
        case 4:
            x++;
            break;
        }
        if (x == 8)
            x = 0;
        if (y == 8)
            y = 0;
        if (x == -1)
            x = 7;
        if (y == -1)
            y = 7;
        window.clear(sf::Color::Black);
        if (gameTab[x][y] == 0)
        {
            gameTab[x][y] = 2;
            gameTab[moves.back().first][moves.back().second] = 0;
            moves.pop_back();
            moves.push_front({x,y});

        }
        else if (gameTab[x][y] == 1)
        {
            gameTab[x][y] = 2;
            moves.push_front({x,y});
            generateFood();
        }
        else
        {
            moves.clear();
            window.close();
            return 0;
        }
        if (gameWon())
        {
            window.close();
            return 0;
        }
        draw(window);
        window.display();
    }
}
