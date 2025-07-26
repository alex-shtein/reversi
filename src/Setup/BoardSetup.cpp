#include "../../include/Setup/BoardSetup.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

game::BoardSetup* game::BoardSetup::_boardSetupPtr = nullptr;

game::BoardSetup::BoardSetup() 
{
    if(_boardSetupPtr)
    throw std::logic_error("Trying to create an already existing class BoardSetup");

    _boardSetupPtr = this;
    init();
}

game::BoardSetup::Theme& game::BoardSetup::GetTheme()
{
    return _boardSetupPtr->_theme;
}

bool& game::BoardSetup::GetTips()
{
    return _boardSetupPtr->_tips;
}

void game::BoardSetup::init()
{
    std::filesystem::create_directory("../Files/");
    std::ifstream fin("../Files/BoardSetup.txt", std::ios_base::in);
    if (!fin.is_open())
    {
        std::ofstream fout("../Files/BoardSetup.txt", std::ios_base::out);
        if (!fout.is_open())
            throw std::runtime_error("Invalid board configuration file to write");
        
        _theme = game::BoardSetup::Theme::Solid;
        _tips = true;

        fout << "Solid\n";
        fout << "1\n";

        return;
    }

    std::string buffer;
    std::getline(fin, buffer);

    _theme = game::BoardSetup::Theme::Solid;
    for (auto &theme : GetThemes())
    {
        if (theme.second == buffer)
        {
            _theme = theme.first;
            break;
        }
    }

    std::getline(fin, buffer);
    if (buffer != "1" && buffer != "0")
        throw std::runtime_error("Error loading board data from file");
    
    _tips = bool(std::stoi(buffer));
}

void game::BoardSetup::Save()
{
    std::ofstream fout("../Files/BoardSetup.txt", std::ios_base::out);
    if (!fout.is_open())
        throw std::runtime_error("Invalid board configuration file to write");
    
    fout << GetThemes().at(GetTheme());

    fout << std::endl;
    fout << std::to_string((int)GetTips());
    fout << std::endl;
}