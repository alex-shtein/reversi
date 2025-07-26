#include "../include/Windows/GamingDisplay/GameInformation.hpp"

void game::Score::init()
{
    _playerAvatar = sf::Sprite(ResourceLoader::GetTexture("../Images/Avatar.png")); 
    _playerAvatar.setOrigin(_playerAvatar.getGlobalBounds().width / 2.f, _playerAvatar.getGlobalBounds().height / 2.f);
    _playerName = game::Text({PlayerSetup::GetName(), (int)_playerScoreText.getCharacterSize()});

    _opponentAvatar = sf::Sprite(ResourceLoader::GetTexture(GameSetup::GetOpponentAvatarID() == AvatarID::Player ? 
                                "../Images/Avatar.png" : "../Images/Computer.png"));
    _opponentAvatar.setOrigin(_opponentAvatar.getGlobalBounds().width / 2.f, _opponentAvatar.getGlobalBounds().height / 2.f);
    _opponentName = game::Text({GameSetup::GetOpponentName(), (int)_opponentScoreText.getCharacterSize()});
}   

void game::Score::Align()
{
    _title.setPosition(0.f, 0.f);

    _playerAvatar.setPosition(-_fieldWidth / 2.f + _playerAvatar.getGlobalBounds().width / 2.f, 
                            _title.getGlobalBounds().height / 2.f + Decor.stepBetweenTitleAndTextFields + _playerAvatar.getGlobalBounds().height / 2.f);
    _playerName.setPosition(-_fieldWidth / 2.f + _playerAvatar.getGlobalBounds().width + Decor.stepBetweenAvatarAndName + 
                            _playerName.getGlobalBounds().width / 2.f, _playerAvatar.getPosition().y);

    _playerScoreText.setPosition(_fieldWidth / 2.f - _playerScoreText.getGlobalBounds().width / 2.f, _playerAvatar.getPosition().y);


    _opponentAvatar.setPosition(_playerAvatar.getPosition().x,
            _playerAvatar.getPosition().y + _playerAvatar.getGlobalBounds().height / 2.f + Decor.stepBetweenTextFields + _opponentAvatar.getGlobalBounds().height / 2.f);
    _opponentName.setPosition(-_fieldWidth / 2.f + _opponentAvatar.getGlobalBounds().width + Decor.stepBetweenAvatarAndName + 
                            _opponentName.getGlobalBounds().width / 2.f, _opponentAvatar.getPosition().y);
    _opponentScoreText.setPosition(_fieldWidth / 2.f - _opponentScoreText.getGlobalBounds().width / 2.f, _opponentAvatar.getPosition().y);
}

game::Score::Score(Text title, Text playerScoreText, Text opponentScoreText, float fieldWidth, float stepBetweenTitleAndTextFields, float stepBetweenTextFields)
    : _title(title), _playerScoreText(playerScoreText), _opponentScoreText(opponentScoreText), _fieldWidth(fieldWidth)
{
    Decor.stepBetweenTitleAndTextFields = stepBetweenTitleAndTextFields;
    Decor.stepBetweenTextFields = stepBetweenTextFields;
    
    init();
    Align();
}

void game::Score::Draw(sf::RenderTarget* target) const
{
    target->draw(_title);

    target->draw(_playerAvatar);
    target->draw(_playerName);
    target->draw(_playerScoreText);

    target->draw(_opponentAvatar);
    target->draw(_opponentName);
    target->draw(_opponentScoreText);
}

void game::Score::SetOffset(sf::Vector2f offset)
{
    _title.setPosition(_title.getPosition() + offset);

    _playerAvatar.setPosition(_playerAvatar.getPosition() + offset);
    _playerName.setPosition(_playerName.getPosition() + offset);
    _playerScoreText.setPosition(_playerScoreText.getPosition() + offset);

    _opponentAvatar.setPosition(_opponentAvatar.getPosition() + offset);
    _opponentName.setPosition(_opponentName.getPosition() + offset);
    _opponentScoreText.setPosition(_opponentScoreText.getPosition() + offset);
}

void game::gameInformation::RoundScore::AlignScores()
{
    _playerScoreText.setPosition(_title.getPosition().x + fieldWidth / 2.f - _playerScoreText.getGlobalBounds().width / 2.f, _playerAvatar.getPosition().y);
    _opponentScoreText.setPosition(_title.getPosition().x + fieldWidth / 2.f - _opponentScoreText.getGlobalBounds().width / 2.f, _opponentAvatar.getPosition().y);
}

game::gameInformation::RoundScore::RoundScore()
    : IGameInformation(), Score(Text({L"Счет по раундам"}), Text({L"0", 40}), Text({L"0", 40}), fieldWidth), _playerScore(0), _opponentScore(0)
{
    Score::init();
    Score::Align();
}

void game::gameInformation::RoundScore::Update(int playerScore, int opponentScore)
{
    if (playerScore == opponentScore)
        return;

    if (((playerScore > opponentScore) + (GameSetup::GetGameParametersID() == GameParametersID::Antireversi)) % 2 == 1)
        ++_playerScore;

    else
        ++_opponentScore;

    _playerScoreText.SetString(std::to_string(_playerScore));
    _opponentScoreText.SetString(std::to_string(_opponentScore));

    AlignScores();
}

void game::gameInformation::RoundScore::Reset()
{
    _playerScore = 0;
    _opponentScore = 0;

    _playerScoreText.SetString(std::to_string(_playerScore));
    _opponentScoreText.SetString(std::to_string(_opponentScore));

    AlignScores();
}

void game::gameInformation::GameColors::init()
{
    _playerAvatar = sf::Sprite(ResourceLoader::GetTexture("../Images/Avatar.png")); 
    _playerAvatar.setOrigin(_playerAvatar.getGlobalBounds().width / 2.f, _playerAvatar.getGlobalBounds().height / 2.f);
    _playerName = game::Text({PlayerSetup::GetName(), 40});

    _opponentAvatar = sf::Sprite(ResourceLoader::GetTexture(GameSetup::GetOpponentAvatarID() == AvatarID::Player ? 
                                "../Images/Avatar.png" : "../Images/Computer.png"));
    _opponentAvatar.setOrigin(_opponentAvatar.getGlobalBounds().width / 2.f, _opponentAvatar.getGlobalBounds().height / 2.f);
    _opponentName = game::Text({GameSetup::GetOpponentName(), 40});

    Update();
}

void game::gameInformation::GameColors::Align()
{
    _playerColor.setPosition(_playerColor.getGlobalBounds().width / 2.f, _playerColor.getGlobalBounds().height / 2.f);
    _playerAvatar.setPosition(fieldWidth - _playerAvatar.getLocalBounds().width / 2.f, _playerColor.getPosition().y);
    _playerName.setPosition(fieldWidth - _playerAvatar.getLocalBounds().width - Decor.sizeBetweenAvatarAndName - _playerName.getGlobalBounds().width / 2.f, _playerColor.getPosition().y);

    _opponentAvatar.setPosition(fieldWidth - _opponentAvatar.getLocalBounds().width / 2.f, 
                                _playerAvatar.getGlobalBounds().height + Decor.sizeBetweenMoveColors + _opponentAvatar.getGlobalBounds().height / 2.f);
    _opponentName.setPosition(fieldWidth - _opponentAvatar.getLocalBounds().width - Decor.sizeBetweenAvatarAndName - _opponentName.getGlobalBounds().width / 2.f, _opponentAvatar.getPosition().y);
    _opponentColor.setPosition(_opponentColor.getGlobalBounds().width / 2.f, _opponentAvatar.getPosition().y);
}

void game::gameInformation::GameColors::AlignColors()
{
    _playerColor.setPosition(_playerAvatar.getPosition().x + _playerAvatar.getGlobalBounds().width / 2.f - fieldWidth + _playerColor.getGlobalBounds().width / 2.f, 
                            _playerColor.getPosition().y);
    _opponentColor.setPosition(_opponentAvatar.getPosition().x + _opponentAvatar.getGlobalBounds().width / 2.f - fieldWidth + _opponentColor.getGlobalBounds().width / 2.f, 
                                _opponentColor.getPosition().y);
}   

game::gameInformation::GameColors::GameColors()
{
    init();
    Align();
}

void game::gameInformation::GameColors::Update()
{
    if (GameSetup::GetOpponentMoveColor() == MoveColor::White) {
        _playerColor.SetString(L"Черные:");
        _opponentColor.SetString(L"Белые:");
    }

    else {
        _playerColor.SetString(L"Белые:");
        _opponentColor.SetString(L"Черные:");
    }

    AlignColors();
}

void game::gameInformation::GameColors::SetOffset(sf::Vector2f offset)
{
    _playerAvatar.setPosition(_playerAvatar.getPosition() + offset);
    _playerName.setPosition(_playerName.getPosition() + offset);
    _playerColor.setPosition(_playerColor.getPosition() + offset);

    _opponentAvatar.setPosition(_opponentAvatar.getPosition() + offset);
    _opponentName.setPosition(_opponentName.getPosition() + offset);
    _opponentColor.setPosition(_opponentColor.getPosition() + offset);
}

void game::gameInformation::GameColors::SetPosition(float x, float y)
{
    SetOffset({x - _playerColor.getPosition().x - fieldWidth / 2.f + _playerColor.getGlobalBounds().width / 2.f, 
                y - _playerColor.getPosition().y - GetHeight() / 2.f + _playerColor.getGlobalBounds().height / 2.f});
}

void game::gameInformation::GameColors::Draw(sf::RenderTarget* target) const
{
    target->draw(_playerAvatar);
    target->draw(_playerName);
    target->draw(_playerColor);

    target->draw(_opponentAvatar);
    target->draw(_opponentName);
    target->draw(_opponentColor);
}

void game::gameInformation::GameParameters::init()
{
    if (GameSetup::GetGameParametersID() == GameParametersID::Antireversi)
        _text = game::TextOptions{L"Антиреверси", 40};
    else if (GameSetup::GetGameParametersID() == GameParametersID::DefaultReversi)
        _text = game::TextOptions{L"Реверси", 40};
    else
        _text = game::TextOptions{L"Реверси с черной дырой", 40};
}

void game::gameInformation::GameParameters::Align()
{
    _title.setPosition(0.f, 0.f);
    _text.setPosition(0.f, _title.getGlobalBounds().height / 2.f + Decor.sizeBetweenTitleAndTextField + _text.getGlobalBounds().height / 2.f);
}

game::gameInformation::GameParameters::GameParameters()
{
    init();
    Align();
}

void game::gameInformation::GameParameters::SetPosition(float x, float y) // center top
{
    _title.setPosition(x, y + _title.getGlobalBounds().height / 2.f - GetHeight() / 2.f);
    _text.setPosition(x, y - _text.getGlobalBounds().height / 2.f + GetHeight() / 2.f);
}

void game::gameInformation::GameParameters::Draw(sf::RenderTarget* target) const
{
    target->draw(_title);
    target->draw(_text);
}

void game::gameInformation::Difficulty::init()
{
    switch (GameSetup::GetComputerDifficulty())
    {
    case 1:
        _difficulty.SetString(L"Новичок");
        break;
    case 2:
        _difficulty.SetString(L"Любитель");
        break;
    case 3:
        _difficulty.SetString(L"Эксперт");
        break;

    default:
        break;
    }
}

void game::gameInformation::Difficulty::Align()
{
    _title.setPosition(0.f, 0.f);
    _difficulty.setPosition(-_title.getGlobalBounds().width / 2.f + fieldWidth - _difficulty.getGlobalBounds().width / 2.f, _title.getPosition().y);
}

game::gameInformation::Difficulty::Difficulty()
{
    init();
    Align();
}


void game::gameInformation::Difficulty::SetPosition(float x, float y) // center
{
    _title.setPosition(x + _title.getGlobalBounds().width / 2.f - fieldWidth / 2.f, y);
    _difficulty.setPosition(x - _difficulty.getGlobalBounds().width / 2.f + fieldWidth / 2.f, y);
}

void game::gameInformation::Difficulty::Draw(sf::RenderTarget* target) const
{
    target->draw(_title);
    target->draw(_difficulty);
}

void game::gameInformation::Round::Align()
{
    _title.setPosition(0.f, 0.f);
    _text.setPosition(0.f, _title.getGlobalBounds().height / 2.f + Decor.sizeBetweenTitleAndTextField + _text.getGlobalBounds().height / 2.f);
}

game::gameInformation::Round::Round(int& currentRound)
    : _currentRound(currentRound)
{
    init();
    Align();
}

void game::gameInformation::Round::SetPosition(float x, float y)
{
    _title.setPosition(x, y + _title.getGlobalBounds().height / 2.f - GetHeight() / 2.f);
    _text.setPosition(x, y - _text.getGlobalBounds().height / 2.f + GetHeight() / 2.f);
}

void game::gameInformation::Round::Draw(sf::RenderTarget* target) const
{
    target->draw(_title);
    target->draw(_text);
}
