#include "../include/Windows/GamingDisplay/EndGame.hpp"
#include "../include/Windows/GamingDisplay/GamingDisplay.hpp"

void game::Winner::init()
{
    _cup.setOrigin(_cup.getGlobalBounds().width / 2.f, _cup.getGlobalBounds().height / 2.f);
    _winnerAvatar.setOrigin(_winnerAvatar.getGlobalBounds().width / 2.f, _winnerAvatar.getGlobalBounds().height / 2.f);
}

void game::Winner::Align()
{
    _background.SetPosition(0.f, _background.getBounds().height / 2.f);
    _cup.setPosition(0.f, Decor.padding + _cup.getGlobalBounds().height / 2.f);

    float totalWidth = _winnerName.getGlobalBounds().width + Decor.sizeBetweenAvatarAndName + _winnerAvatar.getGlobalBounds().width;
    _winnerAvatar.setPosition(-totalWidth / 2.f + _winnerAvatar.getGlobalBounds().width / 2.f, 
                                _background.getBounds().height - Decor.padding - _winnerAvatar.getGlobalBounds().height / 2.f);
    _winnerName.setPosition(totalWidth / 2.f - _winnerName.getGlobalBounds().width / 2.f, _winnerAvatar.getPosition().y);
}

game::Winner::Winner(Text winnerName, sf::Sprite winnerAvatar) 
    : _winnerName(winnerName), _winnerAvatar(winnerAvatar),
    _background(Decor.backgroundSize, Decor.backgroundRadius, 4.f, sf::Color(14, 52, 74)),
    _cup(ResourceLoader::GetTexture("../Images/WinnerCup.png"))
{
    init();
    Align();
}

void game::Winner::SetOffset(sf::Vector2f offset)
{
    _winnerName.setPosition(_winnerName.getPosition() + offset);
    _winnerAvatar.setPosition(_winnerAvatar.getPosition() + offset);
    _cup.setPosition(_cup.getPosition() + offset);
    _background.SetPosition(_background.GetPosition() + offset);
}

void game::Winner::Draw(sf::RenderTarget* target) const
{
    _background.Draw(target);
    target->draw(_cup);
    target->draw(_winnerAvatar);
    target->draw(_winnerName);
}

void game::EndGame::init()
{
    if (_gamingDisplay->GetPlayerRoundScore() > _gamingDisplay->GetOpponenRoundScore())
        _winner = Winner(Text({PlayerSetup::GetName(), 40}), sf::Sprite(ResourceLoader::GetTexture("../Images/Avatar.png")));

    else
        _winner = Winner(Text({GameSetup::GetOpponentName(), 40}), 
                          sf::Sprite(ResourceLoader::GetTexture(GameSetup::GetOpponentAvatarID() == AvatarID::Player ? "../Images/Avatar.png" : "../Images/Computer.png")));

    if (_gamingDisplay->GetPlayerRoundScore() == _gamingDisplay->GetOpponenRoundScore())
        Decor.stepBetweenTextFields = 60.f;

    float totalHeight = _title.getGlobalBounds().height + 3 * Decor.stepBetweenTextFields +
        (_gamingDisplay->GetPlayerRoundScore() != _gamingDisplay->GetOpponenRoundScore() ? _winner.GetBounds().height : _draw.getGlobalBounds().height) + 
        _gameScore.GetHeight() +
        Decor.buttonSize.height + 2 * Decor.titlePositionOnOY;
    
    _background = Rectangle({0.f, 0.f, Decor.backgroundWidth, totalHeight}, Decor.backgroundRadius, 0.f);
}

void game::EndGame::Align()
{
    _background.SetPosition(0.f, _background.getBounds().height / 2.f);
    _title.setPosition(0.f, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);

    float currentHeight = Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTextFields;

    if (_gamingDisplay->GetPlayerRoundScore() != _gamingDisplay->GetOpponenRoundScore()) {
        _winner.SetPosition(0.f, currentHeight + _winner.GetBounds().height / 2.f);
        currentHeight += _winner.GetBounds().height + Decor.stepBetweenTextFields;
    }
        
    else {
        _draw.setPosition(0.f, currentHeight + _draw.getGlobalBounds().height / 2.f);
        currentHeight += _draw.getGlobalBounds().height + Decor.stepBetweenTextFields;
    }

    _gameScore.SetPosition(0.f, currentHeight + _gameScore.GetHeight() / 2.f);
    currentHeight +=  _gameScore.GetHeight() + Decor.stepBetweenTextFields;

    currentHeight += Decor.buttonSize.height / 2.f;
    _backToMainMenu.SetPosition(-Decor.backgroundWidth / 2.f + Decor.margin + _backToMainMenu.getBounds().width / 2.f, currentHeight);
    _retry.SetPosition(Decor.backgroundWidth / 2.f - Decor.margin - _retry.getBounds().width / 2.f, currentHeight);
}

game::EndGame::EndGame(game::GameStack* gameStack, game::GamingDisplay* gameDisplay) 
    : game::PopWindow(gameStack), _gamingDisplay(gameDisplay),
    _title({L"Итоги матча"}),
    _gameScore(Text({L"Счет матча", 48}), 
                Text({std::to_string(_gamingDisplay->GetPlayerRoundScore()), 40}), 
                Text({std::to_string(_gamingDisplay->GetOpponenRoundScore()), 40}),
                Decor.backgroundWidth - 2.f * Decor.margin, 40, 20),
    _draw({L"Ничья"}),
    _backToMainMenu(
        Decor.buttonSize, Decor.buttonRadius, Text({L"Вернуться в меню", 40}),
        [&]()
        {
            if (_gamingDisplay->GetPlayerRoundScore() > _gamingDisplay->GetOpponenRoundScore())
                ++ResultsSetup::GetWins();
            
            else if (_gamingDisplay->GetPlayerRoundScore() < _gamingDisplay->GetOpponenRoundScore())
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
    _retry(
        Decor.buttonSize, Decor.buttonRadius, Text({L"Рестарт", 40}),
        [&]()
        {
            if (_gamingDisplay->GetPlayerRoundScore() > _gamingDisplay->GetOpponenRoundScore())
                ++ResultsSetup::GetWins();

            else if (_gamingDisplay->GetPlayerRoundScore() < _gamingDisplay->GetOpponenRoundScore())
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
game::EndGame::~EndGame() {};

sf::Vector2f game::EndGame::GetSize() const
{
    return {_background.getBounds().width, _background.getBounds().height};
}

void game::EndGame::SetOffset(sf::Vector2f offset)
{
    _background.SetPosition(_background.GetPosition() + offset);
    _title.setPosition(_title.getPosition() + offset);

    _winner.SetOffset(offset);
    _draw.setPosition(_draw.getPosition() + offset);

    _gameScore.SetOffset(offset);

    _backToMainMenu.SetPosition(_backToMainMenu.GetPosition().x + offset.x, _backToMainMenu.GetPosition().y + offset.y);
    _retry.SetPosition(_retry.GetPosition().x + offset.x, _retry.GetPosition().y + offset.y);
}

void game::EndGame::SetPosition(const sf::Vector2f& position)
{
    SetOffset({position.x - _background.GetPosition().x, position.y - _background.GetPosition().y});
}

void game::EndGame::DrawBackWindow(sf::RenderTarget* target)
{
    GetGameStack()->Penultimate()->Draw(target);
}

void game::EndGame::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);

    target->draw(_background);
    target->draw(_title);

    if (_gamingDisplay->GetPlayerRoundScore() != _gamingDisplay->GetOpponenRoundScore())
        _winner.Draw(target);

    else
        target->draw(_draw);

    _gameScore.Draw(target);

    _backToMainMenu.Draw(target);
    _retry.Draw(target);
}

void game::EndGame::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

void game::EndGame::Update(float dt)
{
    return;
}

bool game::EndGame::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed) 
        RequestStateClear();

    if (_backToMainMenu.Update(mousePositon, event))
        return true;

    return _retry.Update(mousePositon, event);
}