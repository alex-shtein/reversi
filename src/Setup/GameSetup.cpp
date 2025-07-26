#include "../../include/Setup/GameSetup.hpp"

game::GameSetup* game::GameSetup::_gameSetupPtr = nullptr;

game::GameSetup::GameSetup() 
{
    if(_gameSetupPtr)
    throw std::logic_error("Trying to create an already existing class GameSetup");

    _gameSetupPtr = this;
}

game::GameTypeID& game::GameSetup::GetGameTypeID()
{
    return _gameSetupPtr->_gameTypeID;
}

unsigned& game::GameSetup::GetComputerDifficulty()
{
    return _gameSetupPtr->_computerDifficulty;
}

sf::String& game::GameSetup::GetOpponentName()
{
    return _gameSetupPtr->_opponentName;
}

game::AvatarID& game::GameSetup::GetOpponentAvatarID()
{
    return _gameSetupPtr->_opponentAvatarID;
}

game::MoveColor& game::GameSetup::GetOpponentMoveColor()
{
    return _gameSetupPtr->_opponentMoveColor;
}

game::GameParametersID& game::GameSetup::GetGameParametersID()
{
    return _gameSetupPtr->_gameParametersID;
}

unsigned& game::GameSetup::GetNumberOfRounds()
{
    return _gameSetupPtr->_numberOfRounds;
}

unsigned& game::GameSetup::GetFieldSize()
{
    return _gameSetupPtr->_fieldSize;
}

sf::Vector2i& game::GameSetup::GetBlackHolePosition()
{
    return _gameSetupPtr->_blackHolePosition;
}

std::vector<sf::Vector2i>& game::GameSetup::GetGameScore()
{
    return _gameSetupPtr->_gameScore;
}