#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;
int ALLUNGLE = 360;
//Window
int windowWidth = 800;
int windowHeight = 800;
int window3DWidth = 1500;
int window3DHeight = 1050;
int window3DWidth2 = window3DWidth / 2;
int window3DHeight2 = window3DHeight / 2;
//MathConst
float PI = acos(-1);
float PI_180 = 180 / PI;
//Mouse
float MouseX = 0;
float MouseY = 0;
//Player
float PlayerR = (windowWidth * windowHeight) / 50000;
float PlayerX = 300;
float PlayerY = 300;
float PlayerSpeed = 2;
//RAY
float RayUngle = 0;
float x;
float y;
float dx;
float dy;
double dirX = -1, dirY = 0; //initial direction vector
//Dot
float DotX = 0;
float DotY = 0;
//RAYS SETS
const int RaysLength = 1500;
const int FOV = 60;
const int FOV2 = FOV / 2;
float FOVRAY = FOV2 * 0.01 / (RaysLength / 100);
const int deltaAngle = FOV / RaysLength;
float WtoP = 0;                 /*   0         1        2        3    */
float Rays[RaysLength][4] = {}; /*RayUngle, RayWidth, RayEndX, RayEndY*/
//Rendering3D
float Rect3DWidth = window3DWidth / RaysLength;
int Zoom = 1;
float Den3Drend = RaysLength / abs(2 * (tan(FOV) * (PI_180))) * window3DHeight * Zoom;
int SkyGaridientLength = 10;
int FloorGaridientLength = 50;
int PlayerAngleY = window3DHeight / 2;
int PlayerAngleYforFloor = window3DHeight / 2;
int arrwalls[RaysLength];
//MAP
int WORLDwidth = 32;
int WORLDheight = 32;
float TILE = windowWidth / WORLDwidth;
const char WORLD[] =
"33333333333333333333333333333333"\
"20     2     1 33              3"\
"3   2          33    3         3"\
"3   2   3      33              3"\
"31      3      33    3         3"\
"3   2   3     333    3  3      3"\
"3       3      33 33    3      3"\
"3       3      33              3"\
"3    1  3      33   3   3      3"\
"3 1     3      33       3      3"\
"3       3      33   33  3      3"\
"3   1   3         3333  3      3"\
"3       3             3 3      3"\
"3     1 3     3         3      3"\
"3 1     3          3    3      3"\
"3     1 333333333       3      3"\
"3       1      33   1   3      3"\
"3 1     0 1 2  33   0   33333333"\
"20 0 0         33   0          3"\
"3        2 2 2 33   33  1      3"\
"3              00   3     0    3"\
"3              00   3 1  1     3"\
"2    1  0   3  00   3  0  0    3"\
"2    1  2      00   3        1 3"\
"2 1  1  2 2 0  00   3         12"\
"2    1  1   2  00   33333333   2"\
"2    1  1   0  00              2"\
"2    1  1   2  00      1  1    2"\
"2    1  1   1  00              2"\
"2    1  1   0  00      1  1    2"\
"2    1  1   1  00              2"\
"3333333333333333333333333333333";
//MiniMap
float MiniMapSize = 0.3;
int MiniMapOffsetX = window3DWidth - (window3DWidth * MiniMapSize) + 150;
int MiniMapOffsetY = window3DHeight - (window3DHeight * MiniMapSize) - 30;
//Cross
const int CrossDepth = window3DWidth / 50;
const int CrossWidth = window3DWidth / 300;
const int CrossHeight = window3DWidth / 300;

//Framework
float getPlayerPos(string name) 
{
    if (name == "x") 
    {
        return PlayerX + PlayerR;
    }
    else if (name == "y") 
    {
        return PlayerY + PlayerR;
    }
}
float toRad(float u) 
{
    return u / (180 / PI);
}
const float moveLen = 500 / sin(toRad(90));
float toDegree(float u) 
{
    return u * (180 / PI);
}
void ClsSound()
{
    Beep(500,50);
}
void MoveLeft() 
{
    float stepX = PlayerSpeed * moveLen * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0] + 90)) / 500;
    float stepY = PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0] + 90)), 2)) / 500;
    if (Rays[RaysLength / 2][0] + 90 > 0 && Rays[RaysLength / 2][0] + 90 < 180)
    {
        if (WORLD[int((getPlayerPos("x") - stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") - stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY -= stepY;
            PlayerX -= stepX;
        }
        else
        {
            ClsSound();
        }
    }
    else
    {
        if (WORLD[int((getPlayerPos("x") - stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") + stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY += stepY;
            PlayerX -= stepX;
        }
        else
        {
            ClsSound();
        }
    }
}
void MoveRight()
{
    float stepX = PlayerSpeed * moveLen * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0] + 90)) / 500;
    float stepY = PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0] + 90)), 2)) / 500;
    if (Rays[RaysLength / 2][0] + 90 > 0 && Rays[RaysLength / 2][0] + 90 < 180) 
    {
        if (WORLD[int((getPlayerPos("x") + stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") + stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY += stepY;
            PlayerX += stepX;
        }
        else
        {
            ClsSound();
        }
    }
    else 
    {
        if (WORLD[int((getPlayerPos("x") + stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") - stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY -= stepY;
            PlayerX += stepX;
        }
        else
        {
            ClsSound();
        }
    }
}
void MoveUp()
{
    float stepX = PlayerSpeed * moveLen * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])) / 500;
    float stepY = PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])), 2)) / 500;
    if (Rays[RaysLength / 2][0] > 0 && Rays[RaysLength / 2][0] < 180) 
    {
        if (WORLD[int((getPlayerPos("x") - stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") + stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY += PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])), 2)) / 500;
            PlayerX -= stepX;
        }
        else
        {
            ClsSound();
        }
    }
    else 
    {
        if (WORLD[int((getPlayerPos("x") - stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") - stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY -= PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])), 2)) / 500;
            PlayerX -= stepX;
        }
        else
        {
            ClsSound();
        }
    }
}
void MoveDown()
{
    float stepX = PlayerSpeed * moveLen * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])) / 500;
    float stepY = PlayerSpeed * sqrt(pow(500, 2) - pow(500 / sin(toRad(90)) * sin(toRad(ALLUNGLE - 90 - Rays[RaysLength / 2][0])), 2)) / 500;
    if (Rays[RaysLength / 2][0] > 0 && Rays[RaysLength / 2][0] < 180)
    {
        if (WORLD[int((getPlayerPos("x") + stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") - stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY -= stepY;
            PlayerX += stepX;
        }
        else
        {
            ClsSound();
        }
    }
    else
    {
        if (WORLD[int((getPlayerPos("x") + stepX) / (windowWidth / WORLDwidth)) + int((getPlayerPos("y") + stepY) / (windowHeight / WORLDheight)) * WORLDheight] == ' ')
        {
            PlayerY += stepY;
            PlayerX += stepX;
        }
        else
        {
            ClsSound();
        }
    }
}
float toRealCord(string type, float c) 
{
    if (type == "x") 
    {
        return c * (windowWidth / WORLDwidth);
    } 
    else if (type == "y")
    {
        return c * (windowHeight / WORLDheight);
    }
}
float toWorldCord(string type, float c)
{
    if (type == "x")
    {
        return int(c / TILE) * TILE;
    }
    else if (type == "y")
    {
        return int(c / TILE) * TILE;
    }

}
float mapping(float c)
{
    return c / (windowWidth / WORLDwidth);
}
//TEXTURES
float offset = 0;

const int Texture0Width = 4;
const int Texture0Height = 600;
const int TAH0 = 300;
float TextureTime0 = 0;
string TexturePath0 = "E:/C++/russianflag.png";

const int Texture1Width = 4;
const int Texture1Height = 350;
const int TAH1 = 30;
float TextureTime1 = 0;
string TexturePath1 = "E:/C++/bricks.png";

const int Texture2Width = 4;
const int Texture2Height = 700;
const int TAH2 = 350;
float TextureTime2 = 0;
string TexturePath2 = "E:/C++/rainbow.png";

const int Texture3Width = 259;
const int Texture3Height = 194;
const float Texture3Scale = Texture3Width / TILE;//fmod(Texture3Width, TILE);
string TexturePath3 = "E:/C++/bricks.jpg";

int main()
{
    for (size_t i = 0; i < RaysLength; i++)
    {
        for (size_t l = 0; l < 4; l++)
        {
            Rays[i][l] = 1;
        }
    }
    sf::ContextSettings ctxsettings;
    ctxsettings.antialiasingLevel = 8;
    sf::RenderWindow window3D(sf::VideoMode(window3DWidth, window3DHeight), "3D Game", sf::Style::Default, ctxsettings);
    window3D.setMouseCursorVisible(false);
    //sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Ray Caster");
    sf::CircleShape Player(PlayerR * MiniMapSize); //�����
    Player.setFillColor(sf::Color::Green);
    //Ray
    sf::RectangleShape Ray(sf::Vector2f(50, 1));
    Ray.setFillColor(sf::Color::Red);
    Ray.setPosition(PlayerX, PlayerY);
    //Dot
    sf::CircleShape Dot(5);
    Dot.setFillColor(sf::Color::Red);
    //Cross
    sf::RectangleShape Cross(sf::Vector2f(1,1));
    Cross.setFillColor(sf::Color(255, 255, 255, 150));
    //Walls
    sf::RectangleShape Wall(sf::Vector2f(1, 1));
    //3D
    sf::RectangleShape Rect3D(sf::Vector2f(100, Rect3DWidth));
    Rect3D.setFillColor(sf::Color::Red);
    Rect3D.setPosition(400, 400);
    sf::RectangleShape Floor(sf::Vector2f(window3DWidth, window3DHeight / 2));
    Floor.setPosition(0, window3DHeight / 2);
    Floor.setFillColor(sf::Color(0, 150, 0));
    sf::RectangleShape Sky(sf::Vector2f(window3DWidth, window3DHeight));
    Sky.setPosition(0, 0);
    Sky.setFillColor(sf::Color(0, 0, 255));
    //FPS CONTROLLER
    sf::Clock clock;
    sf::Time Time;
    sf::Font font;
    font.loadFromFile("gardens.ttf");
    sf::Text FPStext;
    FPStext.setPosition(10, 10);
    FPStext.setFillColor(sf::Color(255, 0, 0, 150));
    FPStext.setCharacterSize(30);
    FPStext.setStyle(sf::Text::Bold);
    FPStext.setFont(font);

    //TEXTURES
    sf::Texture texture0;
    texture0.loadFromFile(TexturePath0);
    sf::Sprite Rect3D0(texture0);
    Rect3D0.setTextureRect(sf::IntRect(0, 0, 100, 100));
    sf::Texture texture1;
    texture1.loadFromFile(TexturePath1);
    sf::Sprite Rect3D1(texture1);
    Rect3D1.setTextureRect(sf::IntRect(0, 0, 100, 100));
    sf::Texture texture2;
    texture2.loadFromFile(TexturePath2);
    sf::Sprite Rect3D2(texture2);
    Rect3D2.setTextureRect(sf::IntRect(0, 0, 100, 100));
    sf::Texture texture3;
    texture3.loadFromFile(TexturePath3);
    sf::Sprite Rect3D3(texture3);
    Rect3D3.setTextureRect(sf::IntRect(0, 0, 100, 100));

    //texture0.setSmooth(true);
    texture1.setSmooth(true);
    texture2.setSmooth(true);
    texture3.setSmooth(true);
    //TEXTURES

    while (window3D.isOpen())
    {
        Time = clock.getElapsedTime();
        float currentTime = Time.asSeconds();
        sf::Event event;
        while (window3D.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                //window.close();
                window3D.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window3D.close();
                //window.close();
            }
        }

        float PlayerWorldX = mapping(getPlayerPos("x"));// (windowWidth / WORLDwidth);
        float PlayerWorldY = mapping(getPlayerPos("y"));// (windowHeight / WORLDheight);
        //cout << PlayerWorldY << endl;
        window3D.clear();
        window3D.draw(Sky);
        for (size_t i = 0; i < FloorGaridientLength; i++)
        {
            /*Floor.setSize(sf::Vector2f(window3DWidth, (PlayerAngleY) / FloorGaridientLength));
            Floor.setPosition(0, (window3DHeight / 2) + window3DHeight / 2 / FloorGaridientLength * i);
            Floor.setFillColor(sf::Color(0, 255 / FloorGaridientLength * i, 0));
            window3D.draw(Floor);*/
            Floor.setSize(sf::Vector2f(window3DWidth, PlayerAngleYforFloor / FloorGaridientLength + 10));
            Floor.setPosition(0, (PlayerAngleY)+(PlayerAngleYforFloor / FloorGaridientLength + 10) * i);
            Floor.setFillColor(sf::Color(0, 255 / FloorGaridientLength * i, 0));
            window3D.draw(Floor);
        }

        float ox = getPlayerPos("x");
        float oy = getPlayerPos("y");
        float xm = mapping(ox);
        float ym = mapping(oy);

        for (size_t i = 0; i < RaysLength; i++)
        {
            Rays[i][0] = RayUngle + FOVRAY * i;
            float cosA = cos(toRad(Rays[i][0]));
            float sinA = sin(toRad(Rays[i][0]));
            //NEW OPTIMIZED SISTEM OF THE DEPTH :
            //if (i == RaysLength / 2)
            //{
                if (cosA >= 0)
                {
                    x = xm + 1;
                    dirX = 1;
                }
                else
                {
                    x = xm;
                    dirX = -1;
                }
                if (sinA >= 0)
                {
                    y = ym + 1;
                    dirY = 1;
                }
                else
                {
                    y = ym;
                    dirY = -1;
                }

                //cout << dirY << endl;
            //}

            for (float d = 0; d < 1000; d += 0.002)
            {

                float cx = PlayerWorldX + d * cosA;
                float cy = PlayerWorldY + d * sinA;
                if (WORLD[int(cx) + int(cy) * WORLDheight] != ' ')
                {
                    DotX = toRealCord("x", cx);                                             // * (windowWidth / WORLDwidth);
                    DotY = toRealCord("y", cy);                                             // * (windowHeight / WORLDheight);

                    //OFFSET
                    float offset_h = fmod(DotX, TILE);
                    float offset_v = fmod(DotY, TILE);
                    //if (offset_v < offset_h)
                    //{
                    if (dirY == 1)
                    {
                        offset = TILE - 1 - offset_h;

                    }
                    else
                    {
                        offset = offset_h;
                    }

                    if (offset_h < offset_v && 24 - int(offset_v) != 0)
                    {
                        if (dirX == 1)
                        {
                            offset = offset_v;
                        }
                    }
                    if (offset_h > offset_v && int(offset_h) == 24)
                    {
                        if (dirX == -1)
                        {
                            offset = TILE - 1 - offset_v;
                        }
                    }

                        if (int(offset_h) == 24 && int(offset_v) == 24)
                        {
                            offset = offset_v - 1;
                        }
                        if (i == RaysLength / 2)
                        {
                            cout << int(offset_h) << " " << int(offset_v) << endl;
                        }
                    
                    //OFFSET

                    Rays[i][1] = hypot(DotX - getPlayerPos("x"), DotY - getPlayerPos("y")); //RAY WIDTH
                    int cac = int(cx) + int(cy) * WORLDheight;                              //WALL'S CHAR IN ARRAY
                    if (WORLD[cac] == '0')
                    {
                        float WtoP = Den3Drend / Rays[i][1];
                        Rect3D0.setTextureRect(sf::IntRect(100, TAH0 - TextureTime0, Rect3DWidth, Texture0Height - TAH0));
                        Rect3D0.setPosition(Rect3DWidth * i, PlayerAngleY - WtoP / 2);
                        Rect3D0.setScale(1, WtoP / (Texture0Height - TAH0));
                        float wallClr = 255 / (1 + Rays[i][1] * Rays[i][1] * 0.000025);
                        Rect3D0.setColor(sf::Color(wallClr, wallClr, wallClr));
                        window3D.draw(Rect3D0);
                        break;
                    }
                    else if (WORLD[cac] == '1')
                    {
                        float WtoP = Den3Drend / Rays[i][1];
                        Rect3D1.setTextureRect(sf::IntRect(0, TAH1 - TextureTime1, Rect3DWidth, Texture1Height - TAH1));
                        Rect3D1.setPosition(Rect3DWidth * i, PlayerAngleY - WtoP / 2);
                        Rect3D1.setScale(1, WtoP / (Texture1Height - TAH1));
                        float wallClr = 255 / (1 + Rays[i][1] * Rays[i][1] * 0.000025);
                        Rect3D1.setColor(sf::Color(wallClr, wallClr, wallClr));
                        window3D.draw(Rect3D1);
                        break;
                    }
                    else if (WORLD[cac] == '2')
                    {
                        float WtoP = Den3Drend / Rays[i][1];
                        Rect3D2.setTextureRect(sf::IntRect(0, TAH2 - TextureTime2, Rect3DWidth, Texture2Height - TAH2));
                        Rect3D2.setPosition(Rect3DWidth * i, PlayerAngleY - WtoP / 2);
                        Rect3D2.setScale(1, WtoP / (Texture2Height - TAH2));
                        float wallClr = 255 / (1 + Rays[i][1] * Rays[i][1] * 0.000025);
                        Rect3D2.setColor(sf::Color(wallClr, wallClr, wallClr));
                        window3D.draw(Rect3D2);
                        break;
                    }
                    else if (WORLD[cac] == '3')
                    {
                        if (i == 150)
                        {
                            //cout << DotY << endl;
                        }
                        float WtoP = Den3Drend / Rays[i][1];
                        //Rect3D3.setTextureRect(sf::IntRect(offset * Texture3Scale, 0, Texture3Scale / 5, Texture3Height));
                        Rect3D3.setTextureRect(sf::IntRect((offset * 0.9) * Texture3Scale, 0, Texture3Scale, Texture3Height));
                        Rect3D3.setScale(1, WtoP / Texture3Height);
                        Rect3D3.scale(Rect3DWidth / Texture3Scale, 1);
                        Rect3D3.setPosition(Rect3DWidth * i, PlayerAngleY - WtoP / 2);
                        float wallClr = 255 / (1 + Rays[i][1] * Rays[i][1] * 0.000025);
                        Rect3D3.setColor(sf::Color(wallClr, wallClr, wallClr));
                        window3D.draw(Rect3D3);
                        break;
                    }
                }
            }
        }

        //MiniMap
        Player.setPosition(PlayerX * MiniMapSize + MiniMapOffsetX, PlayerY * MiniMapSize + MiniMapOffsetY);
        for (int i = 0; i < WORLDwidth; i++) 
        {
            for (int l = 0; l < WORLDheight; l++) 
            {
                if (WORLD[i + l * WORLDheight] == ' ') 
                {
                    continue; 
                }
                Wall.setSize(sf::Vector2f(windowWidth / WORLDwidth * MiniMapSize, windowHeight / WORLDheight * MiniMapSize));
                int wX = i * windowWidth / WORLDwidth * MiniMapSize;
                int wY = l * windowHeight / WORLDheight * MiniMapSize;
                Wall.setPosition(wX + MiniMapOffsetX, wY + MiniMapOffsetY);
                window3D.draw(Wall);
            }
        }
        /*for (size_t i = 0; i < RaysLength; i++)
        {
            Ray.setPosition(getPlayerPos("x"), getPlayerPos("y"));
            Ray.setSize(sf::Vector2f(Rays[i][1], 1));
            Ray.setRotation(Rays[i][0]);
            window.draw(Ray);
        }*/
        Ray.setPosition(getPlayerPos("x") * MiniMapSize + MiniMapOffsetX, getPlayerPos("y") * MiniMapSize + MiniMapOffsetY);
        Ray.setSize(sf::Vector2f(Rays[RaysLength / 2][1] * MiniMapSize, 1));
        Ray.setRotation(Rays[RaysLength / 2][0]);
        window3D.draw(Ray);
        window3D.draw(Player);

        //Controls
        int mouseX = sf::Mouse::getPosition().x;
        int mouseY = sf::Mouse::getPosition().y;
        int mouseVectorX = window3DWidth2 - mouseX;
        int mouseVectorY = window3DHeight2 - mouseY;
        if (PlayerAngleY + (mouseVectorY) * 2.5 < window3DHeight && PlayerAngleY + (mouseVectorY) * 1.5 > 0)
        {
            PlayerAngleY += (mouseVectorY) * 2.5;
        }
        if (PlayerAngleYforFloor - (mouseVectorY) * 2.5 < window3DHeight && PlayerAngleYforFloor - (mouseVectorY) * 1.5 > 0)
        {
            PlayerAngleYforFloor -= (mouseVectorY) * 2.5;
        }
        if (RayUngle - mouseVectorX * 0.1 < 180 && RayUngle - mouseVectorX * 0.1 > -180) 
        {
            RayUngle -= mouseVectorX * 0.1;
        }
        else 
        {
            if (RayUngle - mouseVectorX * 0.1 > 180)
            {
                RayUngle = -180;
            }
            else if (RayUngle - mouseVectorX * 0.1 < -180)
            {
                RayUngle = 180;
            }
        }

        SetCursorPos(window3DWidth2, window3DHeight2);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            Sleep(1);
            MoveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            Sleep(1);
            MoveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Sleep(1);
            MoveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Sleep(1);
            MoveRight();
        }
        //CONTROL TIMERS FOR TEXTURES ANIMATIONS
        if (TextureTime0 >= TAH0) 
        {
            TextureTime0 = 0;
        }
        TextureTime0 += 3;
        if (TextureTime1 >= TAH1) 
        {
            TextureTime1 = 0;
        }
        TextureTime1 += 3;
        if (TextureTime2 >= TAH2) 
        {
            TextureTime2 = 0;
        }
        TextureTime2 += 3;
        //DRAW CROSS
            //HORIZONTALLY
                Cross.setPosition(window3DWidth / 2 + CrossWidth / 2, window3DHeight / 2 + CrossDepth / 2);
                Cross.setSize(sf::Vector2f(CrossDepth, CrossWidth));
                window3D.draw(Cross);
            //VERTICALLY
                Cross.setPosition(window3DWidth / 2 + CrossDepth / 2, window3DHeight / 2 + CrossHeight / 2);
                Cross.setSize(sf::Vector2f(CrossWidth, CrossDepth));
                window3D.draw(Cross);

        //FPS
        Time = clock.getElapsedTime();
        float lastTime = Time.asSeconds();
        int fps = 1 / (lastTime - currentTime);
        FPStext.setString(to_string(fps));
        window3D.draw(FPStext);

        window3D.display();
    }
    return 0;
}
