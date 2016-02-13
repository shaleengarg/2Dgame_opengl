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


bool AngleChangeFlag = false;  // For mouse controls to change the angles
float Topzoom = 10;
float Followzoom = 0;
float Towerzoom = 25;

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.
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
            case GLFW_KEY_UP:
                Human.y -= 1;
                break;
            case GLFW_KEY_DOWN:
                Human.y += 1;
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
                Human.y -= 0.5;
                break;
            case GLFW_KEY_DOWN:
                Human.y += 0.5;
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

/* Executed for character input (like in text boxes) */
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

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE)
                triangle_rot_dir *= -1;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_RELEASE) {
                rectangle_rot_dir *= -1;
            }
            break;
        default:
            break;
    }
}

void CursorPosition (GLFWwindow* window, double x, double y)
{
    if(AngleChangeFlag == true)
    {
    }
}

void Scroll (GLFWwindow* window, double x, double y)
{
   // this will change the zoom. 
}
