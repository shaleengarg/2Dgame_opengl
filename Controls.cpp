#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "Objects.h"
#include "Untouchable.h"
#include "Main.h"

using namespace std;
bool AngleChangeFlag = false;  // For mouse controls to change the angles
float Topzoom = 10;
float Followzoom = 0;
float Towerzoom = 25;
double OldCursorX;
double OldCursorY;
bool HeliChange; // for click and change the angle
bool AdChange;
bool Jump;

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_C:
                //Flag down
                AngleChangeFlag = false;
                break;
            case GLFW_KEY_P:
                triangle_rot_status = !triangle_rot_status;
                break;
            case GLFW_KEY_X:
                // do something ..
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            case GLFW_KEY_SPACE:
                Jump = 1;
                Human.direction = 1;
                break;
            case GLFW_KEY_UP:
                Human.y += 1;
                break;
            case GLFW_KEY_DOWN:
                Human.y -= 1;
                break;
            case GLFW_KEY_RIGHT:
                Human.x -= 1;
                break;
            case GLFW_KEY_LEFT:
                Human.x += 1;
                break;
            case GLFW_KEY_T:       //TOPVIEW
                TowerView = false;
                HelicopterView = false;
                FollowView = false;
                AdventurerView = false;
                TopView = true;
                break;
            case GLFW_KEY_Y:        //Tower View
                TopView = false;
                FollowView = false;
                HelicopterView = false;
                AdventurerView = false;
                TowerView = true;
                break;
            case GLFW_KEY_A:
                //Adventurer View
                TopView = false;
                FollowView = false;
                TowerView = false;
                HelicopterView = false;
                AdventurerView = true;
                break;
            case GLFW_KEY_F:
                //Follow cam
                TopView = false;
                TowerView = false;
                AdventurerView = false;
                HelicopterView = false;
                FollowView = true;
                break;
            case GLFW_KEY_H:
                //Helicopter view
                TopView = false;
                TowerView = false;
                FollowView = false;
                AdventurerView = false;
                HelicopterView = true;
                break;
            case GLFW_KEY_C:
                //flag up
                AngleChangeFlag = true;
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            case GLFW_KEY_UP:
                Human.y += 0.5;
                break;
            case GLFW_KEY_DOWN:
                Human.y -= 0.5;
                break;
            case GLFW_KEY_RIGHT:
                Human.x -= 0.5;
                break;
            case GLFW_KEY_LEFT:
                Human.x += 0.5;
                break;
            default:
                break;
        }

    }
}

void keyboardChar (GLFWwindow* window, unsigned int key)
{
    switch (key) {
        case 'Q':
        case 'q':
            quit(window);
            break;
        default:
            break;
    }
}

void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS) {
                HeliChange = true;
                AdChange = true;
            }
            else if (action == GLFW_RELEASE){
                HeliChange = false;
                AdChange = false;
            }
            break;
        default:
            break;
    }
}

void CursorPosition (GLFWwindow* window, double x, double y)
{
    if(HeliChange == true)
    {
        Theta += (x-OldCursorX);
        Phi += (y-OldCursorY);
    } 
    if(AdChange == true)
    {
        AdventureViewAngle += x-OldCursorX;
    }

    OldCursorX = x;
    OldCursorY = y;
}

void Scroll (GLFWwindow* window, double x, double y)
{
    if(y <0)
    {
        Roh -= 0.7;
    }
    else
        Roh += 0.7;
}
