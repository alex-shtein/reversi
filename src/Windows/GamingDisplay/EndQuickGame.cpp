#include "../include/Windows/GamingDisplay/EndQuickGame.hpp"
#include "../include/Windows/GamingDisplay/GamingDisplay.hpp"

void game::EndQuickGame::init()
{
    if (((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 1))
        _winner = Winner(Text({PlayerSetup::GetName(), 32}), sf::Sprite(ResourceLoader::GetTexture("../Images/Avatar.png")));

    else
        _winner = Winner(Text({GameSetup::GetOpponentName(), 32}), 
                          sf::Sprite(ResourceLoader::GetTexture(GameSetup::GetOpponentAvatarID() == AvatarID::Player ? "../Images/Avatar.png" : "../Images/Computer.png")));

    float totalHeight = _title.getGlobalBounds().height + 4 * Decor.stepBetweenTextFields +
        (_gamingDisplay->GetPlayerScore() != _gamingDisplay->GetOpponentScore() ? _winner.GetBounds().height : _draw.getGlobalBounds().height) + 
        _timeTitle.getGlobalBounds().height +
        _gameScore.GetHeight() + Decor.buttonSize.height +
        2 * Decor.titlePositionOnOY;

    _background = Rectangle({0.f, 0.f, Decor.backgroundWidth, totalHeight}, Decor.backgroundRadius, 0.f);
}

void game::EndQuickGame::Align()
{
    _background.SetPosition(0.f, _background.getBounds().height / 2.f);
    _title.setPosition(0.f, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);

    float currentHeight = Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTextFields;

    if (_gamingDisplay->GetPlayerScore() != _gamingDisplay->GetOpponentScore())
    {
        _winner.SetPosition(0.f, currentHeight + _winner.GetBounds().height / 2.f);
        currentHeight += _winner.GetBounds().height + Decor.stepBetweenTextFields;
    }
        
    else
    {
        _draw.setPosition(0.f, currentHeight + _draw.getGlobalBounds().height / 2.f);
        currentHeight += _draw.getGlobalBounds().height + Decor.stepBetweenTextFields;
    }

    _timeTitle.setPosition(-Decor.backgroundWidth / 2.f + Decor.margin + _timeTitle.getGlobalBounds().width / 2.f, currentHeight + _timeTitle.getGlobalBounds().height / 2.f);
    _timeText.setPosition(Decor.backgroundWidth / 2.f - Decor.margin - _timeText.getGlobalBounds().width / 2.f, _timeTitle.getPosition().y);
    currentHeight +=  _timeTitle.getGlobalBounds().height + Decor.stepBetweenTextFields;

    _gameScore.SetPosition(0.f, currentHeight + _gameScore.GetHeight() / 2.f);
    currentHeight +=  _gameScore.GetHeight() + Decor.stepBetweenTextFields;

    currentHeight += Decor.buttonSize.height / 2.f;
    _backToMainMenu.SetPosition(-Decor.backgroundWidth / 2.f + Decor.margin + _backToMainMenu.getBounds().width / 2.f, currentHeight);
    _retry.SetPosition(Decor.backgroundWidth / 2.f - Decor.margin - _retry.getBounds().width / 2.f, currentHeight);
}

game::EndQuickGame::EndQuickGame(game::GameStack* gameStack, game::GamingDisplay* gamingDisplay) 
    : game::PopWindow(gameStack), _gamingDisplay(gamingDisplay),
    _title({L"Итоги матча", 56}),
    _gameScore(Text({L"Счет матча", 40}), 
                Text({std::to_string(_gamingDisplay->GetPlayerScore()), 32}), 
                Text({std::to_string(_gamingDisplay->GetOpponentScore()), 32}),
                Decor.backgroundWidth - 2.f * Decor.margin, 30, 20),
    _draw({L"Ничья", 56}),
    _timeTitle({L"Время матча", 40}),
    _timeText({_gamingDisplay->GetGameTime(), 40}),
    _backToMainMenu
    (
        
        Decor.buttonSize, Decor.buttonRadius, Text({L"Вернуться в меню", 32}),
        [&]()
        {
            if (((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 1))
                ++ResultsSetup::GetWins();
            else if (((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 0))
                ++ResultsSetup::GetLoses();
            else
                ++ResultsSetup::GetDraws();

            Transition::Get()->SetFunction
            (
                [&]() 
                {
                    auto ptr = GetGameStack();
                    for (; ptr->Size() != 1; ptr->PopState());
                    Transition::Get()->SetMode(ShaderMode::Disappear);
                }
            );
        
            Transition::Get()->SetMode(ShaderMode::Appear);
        }
    ),
    _retry
    (
        Decor.buttonSize, Decor.buttonRadius, Text({L"Рестарт", 32}),
        [&]()
        {
            if (((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 1))
                ++ResultsSetup::GetWins();
            else if (((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 0))
                ++ResultsSetup::GetLoses();
            else
                ++ResultsSetup::GetDraws();

            Transition::Get()->SetFunction
            (
                [&]() 
                {
                    GetGameStack()->PopState();
                    _gamingDisplay->Restart();
                    Transition::Get()->SetMode(ShaderMode::Disappear);
                }
            );
            Transition::Get()->SetMode(ShaderMode::Appear);
        }
    )
{
    init();
    Align();
}
game::EndQuickGame::~EndQuickGame() {};

sf::Vector2f game::EndQuickGame::GetSize() const
{
    return {_background.getBounds().width, _background.getBounds().height};
}

void game::EndQuickGame::SetOffset(sf::Vector2f offset)
{
    _background.SetPosition(_background.GetPosition() + offset);
    _title.setPosition(_title.getPosition() + offset);

    _winner.SetOffset(offset);
    _draw.setPosition(_draw.getPosition() + offset);

    _timeTitle.setPosition(_timeTitle.getPosition() + offset);
    _timeText.setPosition(_timeText.getPosition() + offset);

    _gameScore.SetOffset(offset);

    _backToMainMenu.SetPosition(_backToMainMenu.GetPosition().x + offset.x, _backToMainMenu.GetPosition().y + offset.y);
    _retry.SetPosition(_retry.GetPosition().x + offset.x, _retry.GetPosition().y + offset.y);
}

void game::EndQuickGame::SetPosition(const sf::Vector2f& position)
{
    SetOffset({position.x - _background.GetPosition().x, position.y - _background.GetPosition().y});
}

void game::EndQuickGame::DrawBackWindow(sf::RenderTarget* target)
{
    GetGameStack()->Penultimate()->Draw(target);
}

void game::EndQuickGame::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);

    target->draw(_background);
    target->draw(_title);

    if (_gamingDisplay->GetPlayerScore() != _gamingDisplay->GetOpponentScore())
        _winner.Draw(target);
    else
        target->draw(_draw);

    target->draw(_timeTitle);
    target->draw(_timeText);

    _gameScore.Draw(target);

    _backToMainMenu.Draw(target);
    _retry.Draw(target);
}

void game::EndQuickGame::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

void game::EndQuickGame::Update(float dt)
{
    return;
}

bool game::EndQuickGame::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed) 
        RequestStateClear();

    if (_backToMainMenu.Update(mousePositon, event))
        return true;

    return _retry.Update(mousePositon, event);
}