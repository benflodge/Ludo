#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <utility>
#include <assert.h>
#include <stdio.h>

//#include <GL/gl3w.h>

#include <GL/glew.h>   
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "SpaceColour/SpaceColour.h"
#include "HomeRun/HomeRun.h"
#include "Player/Player.h"
#include "Board/Board.h"
#include "Game/Game.h"

int main (int argc, char **argv)
{

    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync


    //bool err = gl3wInit() != 0;
    bool err = glewInit() != GLEW_OK;



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    size_t players = 4;
    std::srand(std::time(nullptr));
    Game game = Game{ players };

    bool playing = true;


    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        
        ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        ImGui::End();
        

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);


        if (playing)
        {
            // take in turns to roll dice
            for (size_t i = 0; i < players; i++)
            {
                if (!playing) break;

                Player* player = game.getPlayer(i);
                int rollResult = Game::rollDice();
                bool moved = false;
                std::cout << "Player: " << i << " Rolls: " << rollResult << std::endl;
                for (int j = 0; j < COUNTERS; j++)
                {
                    Counter* counter = player->getCounter(j);
                    int currentPosition = counter->getPosition();
                    if (currentPosition == HOME_POSITION)
                    {
                        continue;
                    }

                    int newPosition = game.findNewCounterPosition(*counter, player->getColour(), rollResult);
                    std::cout << "Player: " << i << " Current Position: " << currentPosition << " newPosition: " << newPosition << std::endl;

                    if (newPosition >= 56)
                    {
                        moved = game.moveHomeRunCounter(*counter, newPosition);
                        std::cout << "Player: " << i << " Rolls: " << rollResult << " Counter: " << j << " NewPosition on Home Run: " << newPosition << " Moved: " << moved << std::endl;
                    }
                    else if (newPosition >= 0)
                    {
                        moved = game.moveCounter(*counter, newPosition);
                        std::cout << "Player: " << i << " Rolls: " << rollResult << " Counter: " << j << " NewPosition: " << newPosition << " Moved: " << moved << std::endl;
                    }

                    if (newPosition == HOME_POSITION)
                    {
                        bool hasWon = true;
                        // Check others see if player has won
                        for (size_t k = 0; k < COUNTERS; k++)
                        {
                            Counter* counter = player->getCounter(k);
                            if (counter->getPosition() != HOME_POSITION)
                            {
                                hasWon = false;
                            }
                        }

                        if (hasWon)
                        {
                            std::cout << "Player: " << i << " Has Won!!!!" << std::endl;
                            playing = false;
                            break;
                        }
                    }

                    if (moved) {
                        // Only move one counter per roll!
                        break;
                    }
                }
            }
        }

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
