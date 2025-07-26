#include "../include/Windows/GamingDisplay/TimeAndScore.hpp"

void game::TimeAndScore::RoundScore::init()
{
    _blackChip.setOrigin(_blackChip.getGlobalBounds().width / 2.f, _blackChip.getGlobalBounds().height / 2.f);
    _whiteChip.setOrigin(_whiteChip.getGlobalBounds().width / 2.f, _whiteChip.getGlobalBounds().height / 2.f);

    _blur = Rectangle(sf::FloatRect{0.f, 0.f, Decor.backgroundSize.width / 2.f, Decor.backgroundSize.height}, 
                        Decor.backgroundRadius, Decor.backgroundOutlineThickness,
                        Decor.blurColor, Decor.blurColor, Decor.blurColor);

    Reset();
}  

void game::TimeAndScore::RoundScore::Align()
{
    _background.SetPosition(_background.getBounds().width / 2.f, _background.getBounds().height / 2.f);
    _blackChip.setPosition(Decor.margin + _blackChip.getGlobalBounds().width / 2.f, _background.getBounds().height / 2.f);
    _whiteChip.setPosition(_background.getBounds().width - Decor.margin - _whiteChip.getGlobalBounds().width / 2.f, _background.getBounds().height / 2.f);

    _blur.SetPosition(_background.GetPosition().x + _blur.getBounds().width / 2.f, _background.GetPosition().y);
    if (GameSetup::GetOpponentMoveColor() == MoveColor::Black)
    {
        _opponentScoreText.setPosition(_blackChip.getPosition().x + _blackChip.getGlobalBounds().width / 2.f + 
                                        Decor.stepBetweenChipAndScore + _opponentScoreText.getGlobalBounds().width / 2.f,
                                        _background.getBounds().height / 2.f);
        _playerScoreText.setPosition(_whiteChip.getPosition().x - _whiteChip.getGlobalBounds().width / 2.f - 
                                        Decor.stepBetweenChipAndScore - _playerScoreText.getGlobalBounds().width / 2.f,
                                        _background.getBounds().height / 2.f);
    }
    else
    {
        _playerScoreText.setPosition(_blackChip.getPosition().x + _blackChip.getGlobalBounds().width / 2.f + 
                                        Decor.stepBetweenChipAndScore + _playerScoreText.getGlobalBounds().width / 2.f,
                                        _background.getBounds().height / 2.f);
        _opponentScoreText.setPosition(_whiteChip.getPosition().x - _whiteChip.getGlobalBounds().width / 2.f - 
                                        Decor.stepBetweenChipAndScore - _opponentScoreText.getGlobalBounds().width / 2.f,
                                        _background.getBounds().height / 2.f);
    }
}

game::TimeAndScore::RoundScore::RoundScore(GameField& gameField)
    : _gameField(gameField),
    _background(Decor.backgroundSize, Decor.backgroundRadius, Decor.backgroundOutlineThickness, sf::Color(68, 164, 208),  sf::Color(0, 37, 74), sf::Color(0, 87, 126)),
    _blackChip(sf::Sprite(ResourceLoader::GetTexture("../Images/BlackChip/60px.png"))),
    _whiteChip(sf::Sprite(ResourceLoader::GetTexture("../Images/WhiteChip/60px.png"))),
    _playerScoreText({L"", 40}),
    _opponentScoreText({L"", 40})
{
    init();
    Align();
}

void game::TimeAndScore::RoundScore::Reset()
{
    _playerScore = 2;
    _opponentScore = 2;

    _playerScoreText.SetString(std::to_string(_playerScore));
    _opponentScoreText.SetString(std::to_string(_opponentScore));

    _blur.SetPosition(_background.GetPosition().x + _blur.getBounds().width / 2.f, _background.GetPosition().y);
}

void game::TimeAndScore::RoundScore::Update()
{
    _playerScore = 0;
    _opponentScore = 0;

    CellDefinitions playerColor = (GameSetup::GetOpponentMoveColor() == MoveColor::Black ? CellDefinitions::White : CellDefinitions::Black);
    CellDefinitions opponentColor = (GameSetup::GetOpponentMoveColor() == MoveColor::Black ? CellDefinitions::Black : CellDefinitions::White);

    for (int i = 0; i < GameSetup::GetFieldSize(); ++i)
    {
        for (int j = 0; j < GameSetup::GetFieldSize(); ++j)
        {
            if (_gameField.GetCell({i, j}).GetCellDefinition() == playerColor)
                ++_playerScore;
            
            if (_gameField.GetCell({i, j}).GetCellDefinition() == opponentColor)
                ++_opponentScore;
        }
    }
    _playerScoreText.SetString(std::to_string(_playerScore));
    _opponentScoreText.SetString(std::to_string(_opponentScore));

    if (_gameField.GetMoveColor() == CellDefinitions::White)
        _blur.SetPosition(_background.GetPosition().x - _blur.getBounds().width / 2.f, _background.GetPosition().y);
    else
        _blur.SetPosition(_background.GetPosition().x + _blur.getBounds().width / 2.f, _background.GetPosition().y);
}

void game::TimeAndScore::RoundScore::SetOffset(sf::Vector2f offset)
{
    _background.SetPosition(_background.GetPosition() + offset);
    _blur.SetPosition(_blur.GetPosition() + offset);

    _whiteChip.setPosition(_whiteChip.getPosition() + offset);
    _blackChip.setPosition(_blackChip.getPosition() + offset);

    _playerScoreText.setPosition(_playerScoreText.getPosition() + offset);
    _opponentScoreText.setPosition(_opponentScoreText.getPosition() + offset);
}

void game::TimeAndScore::RoundScore::Draw(sf::RenderTarget* target) const
{
    _background.Draw(target);
    target->draw(_whiteChip);
    target->draw(_blackChip);

    target->draw(_playerScoreText);
    target->draw(_opponentScoreText);

    _blur.Draw(target);
}

sf::String game::TimeAndScore::RoundTime::ConvertSecondToStringTime() const
{
    sf::String ans = "";

    int minutes = (int)(_time) / 60;
    ans += (minutes < 10 ? "0" : "") + std::to_string(minutes) + " : ";

    int seconds = (int)(_time) % 60;
    ans += (seconds < 10 ? "0" : "") + std::to_string(seconds);

    return ans;
}

void game::TimeAndScore::RoundTime::Align()
{
    _background.SetPosition(_background.getBounds().width / 2.f, _background.getBounds().height / 2.f);
    _timeIcon.setPosition(_background.getBounds().width / 2.f, Decor.padding + _timeIcon.getGlobalBounds().height / 2.f);
    _timeText.setPosition(_background.getBounds().width / 2.f, _background.getBounds().height - Decor.padding - _timeText.getGlobalBounds().height / 2.f);
}

game::TimeAndScore::RoundTime::RoundTime()
    : _background(Decor.backgroundSize, Decor.backgroundRadius, Decor.backgroundOutlineThickness),
        _timeIcon(sf::Sprite(ResourceLoader::GetTexture("../Images/Time.png"))),
        _time(0.f),
        _timeText({ConvertSecondToStringTime(), 32})
{
    init();
    Align();
}

void game::TimeAndScore::RoundTime::Reset()
{
    _time = 0.f;
    _timeText.setString(ConvertSecondToStringTime());
}

void game::TimeAndScore::RoundTime::Update(float dt)
{
    _time += dt;
    if (_time >= 60.f * 60.f)
        _time = 60.f * 60.f - 1.f;

    _timeText.setString(ConvertSecondToStringTime());
}

void game::TimeAndScore::RoundTime::SetOffset(sf::Vector2f offset)
{
    _background.SetPosition(_background.GetPosition() + offset);
    _timeIcon.setPosition(_timeIcon.getPosition() + offset);
    _timeText.setPosition(_timeText.getPosition() + offset);
}

void game::TimeAndScore::RoundTime::Draw(sf::RenderTarget* target) const
{
    _background.Draw(target);
    target->draw(_timeIcon);
    target->draw(_timeText);
}

void game::TimeAndScore::SetPostion(float x, float y) //// center top
{
    _score.SetPosition(x, y + _score.GetBounds().height / 2.f);
    _time.SetPosition(x, y + _time.GetBounds().height / 2.f);
}

void game::TimeAndScore::Draw(sf::RenderTarget* target) const
{
    _score.Draw(target);
    _time.Draw(target);
}

void game::TimeAndScore::Reset()
{
    _score.Reset();
    _time.Reset();
}