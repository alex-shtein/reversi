#include "../include/Windows/GamingDisplay/EndRound.hpp"
#include "../include/Windows/GamingDisplay/GamingDisplay.hpp"

void game::EndRound::init()
{
    _timeTitle = game::TextOptions(L"Время раунда", 40);
    _timeText = game::TextOptions(_gamingDisplay->GetGameTime(), 40);

    if (_gamingDisplay->GetPlayerScore() == _gamingDisplay->GetOpponentScore()) {
        _winnerAvatar = {};
        _winnerName = {};
        _winnerText = game::TextOptions(L"Ничья", 40);
    }

    else {
        _winnerText = game::TextOptions(L"Победитель", 40);
        if ((GameSetup::GetGameParametersID() == GameParametersID::Antireversi) + (_gamingDisplay->GetPlayerScore() > _gamingDisplay->GetOpponentScore()) % 2 == 0) {
            _winnerAvatar = sf::Sprite(ResourceLoader::GetTexture(GameSetup::GetOpponentAvatarID() == AvatarID::Player ? "../Images/Avatar.png" : "../Images/Computer.png"));
            _winnerName = Text({GameSetup::GetOpponentName(), 40});
        }
        
        else {
            _winnerAvatar = sf::Sprite(ResourceLoader::GetTexture("../Images/Avatar.png"));
            _winnerName = Text({PlayerSetup::GetName(), 40});
        }
        _winnerAvatar.setOrigin(_winnerAvatar.getGlobalBounds().width / 2.f, _winnerAvatar.getGlobalBounds().height / 2.f);
    }    
}

void game::EndRound::Align()
{
    _background.SetPosition(0.f, _background.getBounds().height / 2.f);
    _title.setPosition(0.f, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);

    float currentHeight = 0;
    if (_gamingDisplay->GetPlayerScore() == _gamingDisplay->GetOpponentScore()) {
        _winnerText.setPosition(0.f, Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTextFields + _winnerText.getGlobalBounds().height / 2.f);
        currentHeight = _winnerText.getPosition().y + _winnerText.getGlobalBounds().height / 2.f + Decor.stepBetweenTextFields;
    }
        
    else {
        _winnerAvatar.setPosition(_background.getBounds().width / 2.f - Decor.margin - _winnerName.getGlobalBounds().width - 
                                    Decor.stepBetweenAvatarAndName - _winnerAvatar.getGlobalBounds().width / 2.f,
            Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTextFields + _winnerAvatar.getGlobalBounds().height / 2.f
        );
        _winnerName.setPosition(_background.getBounds().width / 2.f - Decor.margin - _winnerName.getGlobalBounds().width / 2.f, _winnerAvatar.getPosition().y);
        _winnerText.setPosition(-_background.getBounds().width / 2.f + Decor.margin + _winnerText.getGlobalBounds().width / 2.f, _winnerAvatar.getPosition().y);

        currentHeight = _winnerAvatar.getPosition().y + _winnerAvatar.getGlobalBounds().height / 2.f + Decor.stepBetweenTextFields;
    }

    currentHeight += _timeTitle.getGlobalBounds().height / 2.f;
    _timeTitle.setPosition(-_background.getBounds().width / 2.f + Decor.margin + _timeTitle.getGlobalBounds().width / 2.f, currentHeight);
    _timeText.setPosition(_background.getBounds().width / 2.f - Decor.margin - _timeText.getGlobalBounds().width / 2.f, currentHeight);
    currentHeight += _timeTitle.getGlobalBounds().height / 2.f + Decor.stepBetweenTextFields;

    _roundScore.SetPosition(0.f, currentHeight + _roundScore.GetHeight() / 2.f);
    currentHeight += _roundScore.GetHeight() + Decor.stepBetweenTextFields;
    _gameScore.SetPosition(0.f, currentHeight + _gameScore.GetHeight() / 2.f);
    currentHeight += _gameScore.GetHeight() + Decor.stepBetweenTextFields;

    _button.SetPosition(0.f, currentHeight + _button.getBounds().height / 2.f);
}

game::EndRound::EndRound(game::GameStack* gameStack, game::GamingDisplay* gamingDisplay) 
    : game::PopWindow(gameStack), _gamingDisplay(gamingDisplay),
    _background(Decor.backgroundSize, Decor.backgroundRadius, 0.f),
    _title({L"Итоги раунда", 48}),
    _roundScore(Text({L"Счет раунда", 36}), 
                Text({std::to_string(_gamingDisplay->GetPlayerScore()), 32}), 
                Text({std::to_string(_gamingDisplay->GetOpponentScore()), 32}),
                Decor.backgroundSize.width - 2.f * Decor.margin, 30.f, 20.f),
    _gameScore(Text({L"Счет матча", 36}), 
                Text({std::to_string(_gamingDisplay->GetPlayerRoundScore()), 32}), 
                Text({std::to_string(_gamingDisplay->GetOpponenRoundScore()), 32}),
                Decor.backgroundSize.width - 2.f * Decor.margin, 30.f, 20.f),
    _button(
        Decor.buttonSize, Decor.buttonRadius, Text({L"Начать следующий раунд", 32}),
        [&]()
        {
            Transition::Get()->SetFunction
            (
                [&]() 
                {
                    GetGameStack()->PopState();
                    _gamingDisplay->StartNextRound();
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
game::EndRound::~EndRound() {};

sf::Vector2f game::EndRound::GetSize() const
{
    return {_background.getBounds().width, _background.getBounds().height};
}

void game::EndRound::SetOffset(sf::Vector2f offset)
{
    _background.SetPosition(_background.GetPosition() + offset);
    _title.setPosition(_title.getPosition() + offset);

    _winnerAvatar.setPosition(_winnerAvatar.getPosition() + offset);
    _winnerName.setPosition(_winnerName.getPosition() + offset);
    _winnerText.setPosition(_winnerText.getPosition() + offset);

    _timeTitle.setPosition(_timeTitle.getPosition() + offset);
    _timeText.setPosition(_timeText.getPosition() + offset);

    _gameScore.SetOffset(offset);
    _roundScore.SetOffset(offset);

    _button.SetPosition(_button.GetPosition().x + offset.x, _button.GetPosition().y + offset.y);
}

void game::EndRound::SetPosition(const sf::Vector2f& position)
{
    SetOffset({position.x - _background.GetPosition().x, position.y - _background.GetPosition().y});
}

void game::EndRound::DrawBackWindow(sf::RenderTarget* target)
{
    GetGameStack()->Penultimate()->Draw(target);
}

void game::EndRound::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);

    target->draw(_background);
    target->draw(_title);

    target->draw(_winnerText);
    target->draw(_winnerAvatar);
    target->draw(_winnerName);

    target->draw(_timeTitle);
    target->draw(_timeText);

    _roundScore.Draw(target);
    _gameScore.Draw(target);

    _button.Draw(target);
}

void game::EndRound::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

void game::EndRound::Update(float dt)
{
    return;
}

bool game::EndRound::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed) 
        RequestStateClear();

    return _button.Update(mousePositon, event);
}