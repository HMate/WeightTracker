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

class WeightFileLine
{
    float m_weight;
    DateTime m_date;
public:
    WeightFileLine(DateTime date, float weight) : m_date(date), m_weight(weight) {}
    std::string toString()
    {
        return StringFormatter::format("%s %s", m_date.toString(), m_weight);
    }
};

std::vector<WeightFileLine> loadWeightFile(const std::string& weightFilePath)
{
    std::vector<WeightFileLine> result;

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
            result.push_back(WeightFileLine(dt, StringParser::parseFloat(parts[1])));
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
    
    // Set initial weight file, and load it in. 
    // TODO: This will be replaced by loading in the last saved file path
    char weightFilePath[2048] = "";
    FileSystem::getCurrentWorkingDirectory().copy(weightFilePath, 2048);
    strcat_s(weightFilePath, "\\weights.dtr");
    std::vector<WeightFileLine> weights = loadWeightFile(weightFilePath);
    
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
            ImGui::SameLine();
            if(ImGui::Button("Load file"))
            {
                weights = loadWeightFile(weightFilePath);
            }

            ImGui::BeginChild("Sub1", ImVec2(ImGui::GetWindowContentRegionWidth(), 300), false, ImGuiWindowFlags_HorizontalScrollbar);
            for(auto w : weights)
            {
                ImGui::Text(w.toString().c_str());
            }
            ImGui::SetScrollHere();
            ImGui::EndChild();

            // TODO: Fill empty dates with interolated values and plot that
            ImGui::PlotLines("Weights", reinterpret_cast<float*>(weights.data()), weights.size(), 0, "Weights", 60.0f, 120.0f, ImVec2(0,200), sizeof(WeightFileLine));
        }
        ImGui::End();
    
        window.clear(bgColor);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
}