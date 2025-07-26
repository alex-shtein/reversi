#include "../../include/Setup/ResultsSetup.hpp"

#include "filesystem"

game::ResultsSetup* game::ResultsSetup::_resultsSetupPtr = nullptr;

game::ResultsSetup::ResultsSetup() 
{
    if(_resultsSetupPtr)
    throw std::logic_error("Trying to create an already existing class ResultsSetup");

    _resultsSetupPtr = this;
    Load();
}

void game::ResultsSetup::Load()
{
    std::filesystem::create_directory("../Files/");
    std::ifstream fin("../Files/ResultsSetup.txt", std::ios_base::in);
    
    if (!fin.is_open())
    {
        std::ofstream fout("../Files/ResultsSetup.txt", std::ios_base::out);
        if (!fout.is_open())
            throw std::runtime_error("Invalid results configuration file to write");

        _resultsSetupPtr->_wins = _resultsSetupPtr->_loses = _resultsSetupPtr->_draws = 0;
        fout << _resultsSetupPtr->_wins << std::endl;
        fout << _resultsSetupPtr->_loses << std::endl;
        fout << _resultsSetupPtr->_draws << std::endl;

        return;
    }
        
    fin >> _resultsSetupPtr->_wins;
    fin >> _resultsSetupPtr->_loses;
    fin >> _resultsSetupPtr->_draws;
}

void game::ResultsSetup::Save()
{
    std::ofstream fout("../Files/ResultsSetup.txt", std::ios_base::out);
    if (!fout.is_open())
        throw std::runtime_error("Invalid results configuration file to write");
    
    fout << _resultsSetupPtr->_wins << std::endl;
    fout << _resultsSetupPtr->_loses << std::endl;
    fout << _resultsSetupPtr->_draws << std::endl;
}