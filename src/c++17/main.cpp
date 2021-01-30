#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <utility>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <sstream>

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ludo Game", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    bool err = glewInit() != GLEW_OK;
    if (err)
        return 1;


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
    Game game;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        GameState gameState = game.getState();
        ImGui::Begin("Ludo");

        // In GUI
        if (gameState == GameState::GAME_MENU) 
        {
            if (ImGui::Button("Start 1 Player Game")) 
            {
                game.startGame(1);
            }
            if (ImGui::Button("Start 2 Player Game"))
            {
                game.startGame(2);
            }
            if (ImGui::Button("Start 3 Player Game"))
            {
                game.startGame(3);
            }
            if (ImGui::Button("Start 4 Player Game"))
            {
                game.startGame(4);
            }
        }
        

        if (gameState == GameState::GAME_ROLL)
        {
            Player* player = game.getPlayerForTurn();
            SpaceColour colour = player->getColour();
            std::stringstream goInfoText;
            goInfoText << "Player " << (int)colour << " Turn To Roll Dice" << std::endl;
            std::string playerText = goInfoText.str();

            if (ImGui::Button(playerText.c_str())) {
                game.rollDice();
            }
        }

        if (gameState == GameState::GAME_MOVE)
        {
            int rollResult = game.getRollResult();
            Player* player = game.getPlayerForTurn();
            SpaceColour colour = player->getColour();

            std::stringstream goInfoText;
            goInfoText << "Player " << (int)colour << " rolled a " << rollResult << " which counter will you move?" << std::endl;
            std::string playerText = goInfoText.str();
            ImGui::Text(playerText.c_str());

            bool canMove = false;
            for (int j = 0; j < COUNTERS; j++)
            {
                Counter* counter = player->getCounter(j);
                int currentPosition = counter->getPosition();
                if (currentPosition == HOME_POSITION)
                {
                    ImGui::Text("Counter Home!");
                    continue;
                }

                int newPosition = game.findNewCounterPosition(*counter, rollResult);

                if (newPosition == currentPosition)
                {
                    ImGui::Text("Counter cannot move!");
                    continue;
                }
                if (newPosition >= BOARD_SIZE + HOME_RUN_SIZE)
                {
                    ImGui::Text("You must get an exact roll to finish the game!");
                    continue;
                }

                bool spaceTakenByPlayer = false;
                for (int k = 0; k < COUNTERS; k++)
                {
                    Counter* counter = player->getCounter(k);
                    int counterPos = counter->getPosition();
                    if (newPosition == counterPos) {
                        spaceTakenByPlayer = true;
                        break;
                    }
                }

                if (spaceTakenByPlayer)
                {
                    ImGui::Text("You are already on this space");
                    continue;
                }

                canMove = true;

                std::stringstream goInfoText;
                goInfoText << "Player: " << (int)colour << " Counter: " << j << " Current Position: " << currentPosition << " newPosition: " << newPosition << std::endl;
                std::string playerText = goInfoText.str();

                if (ImGui::Button(playerText.c_str())) {

                    if (newPosition >= BOARD_SIZE)
                    {
                        game.moveHomeRunCounter(*counter, newPosition);
                        std::cout << "Player: " << (int)colour << " Rolls: " << rollResult << " Counter: " << j << " NewPosition on Home Run: " << newPosition << std::endl;
                    }
                    else if (newPosition >= 0)
                    {
                        game.moveCounter(*counter, newPosition);
                        std::cout << "Player: " << (int)colour << " Rolls: " << rollResult << " Counter: " << j << " NewPosition: " << newPosition << std::endl;
                    }

                }
            }


            if (!canMove && ImGui::Button("Cannot move, skip turn.")) {
                game.turnOver();
            }
        }

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

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
