
#include "filesystem.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main(char argc, char* argv)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Weight Tacker");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = {0.0f, 0.0f, 0.0f};

    File weightFile;
    weightFile.loadFile("weights.dtr");
    std::string line = weightFile.readLine();
    std::string line2 = weightFile.readLine();
    std::string line3 = weightFile.readLine();
    
    sf::Clock deltaClock;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        float editorHeight;
        float windowPadding = 10.f;
        ImGui::Begin("Editor");
        {
            ImGui::SetWindowPos(ImVec2(windowPadding, 0));
            if(ImGui::ColorEdit3("Background color", color))
            {
                bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
            }

            editorHeight = ImGui::GetWindowHeight();
        }
        ImGui::End();

        ImGui::Begin("Tracker");
        {
            ImGui::SetWindowPos(ImVec2(windowPadding, editorHeight + windowPadding));
            if(ImGui::Button("Update window title"))
            {

            }
        }
        ImGui::End();
    
        window.clear(bgColor);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
}