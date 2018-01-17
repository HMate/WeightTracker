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

struct WeightFileLine
{
    float m_weight;
    DateTime m_date;

    WeightFileLine(DateTime date, float weight) : m_date(date), m_weight(weight) {}
    std::string toString()
    {
        return StringFormatter::format("%s %s", m_date.toString(), StringFormatter::roundFloat(m_weight, 1));
    }
};

class WeightFile
{
    std::vector<WeightFileLine> m_weights;
public:
    WeightFile(){}

    void loadWeightFile(const std::string& weightFilePath)
    {
        m_weights.clear();
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
                m_weights.push_back(WeightFileLine(dt, StringParser::parseFloat(parts[1])));
            }
            else
                Log::log("Error: less than 2 parts in: %s", line);
        }
    }

    void save(const std::string& weightFilePath)
    {
        File weightFile;
        weightFile.writeLine("Date,Weight");
        for(auto& w : m_weights)
        {
            std::string line = StringFormatter::format("%s,%s", w.m_date.toString(), StringFormatter::roundFloat(w.m_weight, 1));
            weightFile.writeLine(line);
        }
        weightFile.saveFile(weightFilePath);
    }

    void addWeight(const WeightFileLine& w)
    {
        m_weights.push_back(w);
    }

    std::vector<WeightFileLine>& getWeights()
    {
        return m_weights;
    }
};

// Fill empty dates with interolated values and plot that
// Get at least one index for every day from first date to last.  Interpolate missing days.
void loadInterpolatedWeightsData(const std::vector<WeightFileLine>& weights, std::vector<WeightFileLine>& interpolatedWeights)
{
    interpolatedWeights.clear();
    if(weights.size() <= 0)
    {
        return;
    }
    WeightFileLine prevLine = WeightFileLine(weights[0].m_date, 0.0f);
    for(auto w : weights)
    {
        auto nextDay = prevLine.m_date + TimeSpan::Day(1);
        auto lastDay = prevLine.m_date.getDay();
        auto targetDay = w.m_date.getDay();

        while(targetDay > nextDay.getDay())
        {
            float middleWeight = prevLine.m_weight + ((w.m_weight - prevLine.m_weight) * (nextDay.getDay() - lastDay) / (targetDay - lastDay));
            interpolatedWeights.push_back(WeightFileLine(nextDay, middleWeight));
            nextDay = nextDay + TimeSpan::Day(1);
        }
        interpolatedWeights.push_back(w);
        prevLine = w;
    }
}

void loadTableText(std::vector<WeightFileLine>& interpolatedWeights, std::vector<std::string>& interpolatedTexts)
{
    interpolatedTexts.clear();
    for(size_t i = 0; i < interpolatedWeights.size(); i++)
    {
        interpolatedTexts.push_back(StringFormatter::format("%s - %s", i, WeightFileLine(interpolatedWeights[i].m_date, interpolatedWeights[i].m_weight).toString()));
    }
}

class CacheFile
{
    // Change version if structure of cache file is modified.
    const int32 m_version = 1;

    std::string m_path;
    File m_file;
    std::string m_lastLoadedFilePath;
public:
    CacheFile()
    {
        m_path = FileSystem::getCurrentWorkingDirectory() + "\\wtstate.wts";
        m_file.loadFile(m_path);
        
        auto line = m_file.readLine();
        if(StringParser::isInt32(line))
        {
            int32 version = StringParser::parseInt32(line);
            m_lastLoadedFilePath = m_file.readLine();
        }
    }

    void setFilePath(const std::string& newFilePath)
    {
        m_lastLoadedFilePath = newFilePath;
        saveFile();
    }

    std::string getFilePath()
    {
        return m_lastLoadedFilePath;
    }

    void saveFile()
    {
        m_file.clear();
        m_file.writeLine(std::to_string(m_version));
        m_file.writeLine(m_lastLoadedFilePath);
        m_file.saveFile(m_path);
    }
};

int main(char argc, char* argv)
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Weight Tracker");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = {0.0f, 0.0f, 0.0f};


    int year = 2018, month = 1, day = 16, hour = 19, minute = 2, sec = 21;
    float newWeight = 90.0f;
    
    // Set initial weight file from save, and load it in. 
    CacheFile cacheFile;
    std::string weightFilePath = cacheFile.getFilePath();

    WeightFile weightsFile;
    weightsFile.loadWeightFile(weightFilePath);
    bool justLoaded = true;
    
    auto& weights = weightsFile.getWeights();
    std::vector<WeightFileLine> interpolatedWeights;

    std::vector<std::string> interpolatedTexts;

    loadInterpolatedWeightsData(weights, interpolatedWeights);
    loadTableText(interpolatedWeights, interpolatedTexts);

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

            const int32 pathLength = 2048;
            char newPath[pathLength] = {0};
            weightFilePath.copy(newPath, weightFilePath.size());
            ImGui::InputText("Input file", newPath, pathLength);
            ImGui::SameLine();
            if(ImGui::Button("Load file"))
            {
                justLoaded = true;
                weightFilePath = newPath;
                weightsFile.loadWeightFile(weightFilePath);
                weights = weightsFile.getWeights();
                loadInterpolatedWeightsData(weights, interpolatedWeights);
                loadTableText(interpolatedWeights, interpolatedTexts);
                cacheFile.setFilePath(weightFilePath);
            }
            
            {
                ImGui::BeginGroup();
                ImGui::PushID("DatePicker");

                ImGui::PushItemWidth(90.0f);
                
                ImGui::InputInt("##Year", &year, 1);
                ImGui::SameLine();
                ImGui::InputInt("##Month", &month, 1);
                ImGui::SameLine();
                ImGui::InputInt("-##Day", &day, 1);
                ImGui::SameLine();
                ImGui::InputInt("##Hour", &hour, 1);
                ImGui::SameLine();
                ImGui::InputInt("##Minute", &minute, 1);
                ImGui::SameLine();
                ImGui::InputInt("##Sec", &sec, 1);

                ImGui::SameLine();
                ImGui::PopItemWidth();
                ImGui::PushItemWidth(120.0f);
                ImGui::InputFloat("kg Weight", &newWeight, 0.1f, 0.01f, 1);

                if(ImGui::Button("Save"))
                {
                    DateTime date = DateTime(year, month, day, hour, minute, sec);
                    weightsFile.addWeight(WeightFileLine(date, newWeight));
                    weights = weightsFile.getWeights();
                    loadInterpolatedWeightsData(weights, interpolatedWeights);
                    loadTableText(interpolatedWeights, interpolatedTexts);

                    weightsFile.save(weightFilePath);
                }

                ImGui::PopItemWidth();

                ImGui::PopID();
                ImGui::EndGroup();
            }
            ImGui::PlotLines("##Weights", reinterpret_cast<float*>(weights.data()), weights.size(), 0, "Weights", 60.0f, 120.0f, ImVec2(0,200), sizeof(WeightFileLine));
            
            ImGui::Separator();

            ImGui::BeginChild("WeightsInterp Table", ImVec2(ImGui::GetWindowContentRegionWidth(), 300), false, ImGuiWindowFlags_HorizontalScrollbar);
            for(auto s : interpolatedTexts)
            {
                ImGui::Text(s.c_str());
            }
            if(justLoaded)
                ImGui::SetScrollPosHere();
            ImGui::EndChild();

            justLoaded = false;
        }
        ImGui::End();
    
        window.clear(bgColor);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
}