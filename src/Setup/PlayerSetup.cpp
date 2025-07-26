#include "../../include/Setup/PlayerSetup.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

game::PlayerSetup* game::PlayerSetup::_playerSetupPtr = nullptr;

game::PlayerSetup::PlayerSetup() 
{
    if(_playerSetupPtr)
    throw std::logic_error("Trying to create an already existing class PlayerSetup");

    _playerSetupPtr = this;
    init();
}

sf::String& game::PlayerSetup::GetName()
{
    return _playerSetupPtr->_name;
}

void SaveName(std::ofstream& fout, std::basic_string<sf::Uint8> data)
{
    for (auto &&ch : data)
    {
        fout << ch;
    }
    fout << std::endl;

}

void game::PlayerSetup::init()
{
    std::filesystem::create_directory("../Files/");
    std::ifstream fin("../Files/PlayerSetup.txt", std::ios_base::in);
    if (!fin.is_open())
    {
        std::ofstream fout("../Files/PlayerSetup.txt", std::ios_base::out);
        if (!fout.is_open())
            throw std::runtime_error("Invalid player configuration file to write");
        
        SaveName(fout, (_name = L"Без имени").toUtf8());
        return;
    }

    std::string buffer;
    std::getline(fin, buffer);
    _name = sf::String::fromUtf8(buffer.begin(), buffer.end());
}

void game::PlayerSetup::Save()
{
    std::ofstream fout("../Files/PlayerSetup.txt", std::ios_base::out);
    if (!fout.is_open())
        throw std::runtime_error("Invalid player configuration file to write");
    
    SaveName(fout, _playerSetupPtr->_name.toUtf8());
}