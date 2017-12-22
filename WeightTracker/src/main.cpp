#define _SCL_SECURE_NO_WARNINGS
#include <cstring>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "mammoth/types.h"
#include "mammoth/logger.h"
#include "mammoth/filesystem.h"
#include "mammoth/string.h"
#include "mammoth/datetime.h"

std::vector<std::string> loadWeightFile(const std::string& weightFilePath)
{
    std::vector<std::string> result;

    File weightFile;
    weightFile.loadFile(weightFilePath);
    std::string header = weightFile.readLine();
    while(!weightFile.isEndOfFile())
    {
        String line = weightFile.readLine();
        std::vector<std::string> parts = line.split(",");
        if(parts.size() >= 2)
        {
            std::string date = parts[0];
            DateTime dt(date);
            std::string weight = parts[1];
            result.push_back(line);
        }
        else
            Log::log("Error: less than 2 parts in: %s", line);
    }
    return result;
}

int main(char argc, char* argv)
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Weight Tracker");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = {0.0f, 0.0f, 0.0f};
    
    char weightFilePath[2048] = "";
    FileSystem::getCurrentWorkingDirectory().copy(weightFilePath, 2048);
    strcat_s(weightFilePath, "\\weights.dtr");
    std::vector<std::string> weights = loadWeightFile(weightFilePath);
    
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
            ImGui::SetWindowSize(ImVec2(window.getSize().x - 2.0f*windowPadding, window.getSize().y - editorHeight - 2.0f*windowPadding));
            ImGui::InputText("Input file", weightFilePath, 2048);
            if(ImGui::Button("Load file"))
            {
                weights = loadWeightFile(weightFilePath);
            }
            ImGui::BeginChild("Sub1", ImVec2(ImGui::GetWindowContentRegionWidth(), 300), false, ImGuiWindowFlags_HorizontalScrollbar);
            for(auto w : weights)
            {
                ImGui::Text(w.c_str());
            }
            ImGui::SetScrollHere();
            ImGui::EndChild();
        }
        ImGui::End();
    
        window.clear(bgColor);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
}