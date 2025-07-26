#include "../include/Windows/ExitWindow.hpp"

void game::ExitWindow::init()
{   
    _buttons.push_back({Decor.buttonSize, Decor.buttonRadius, game::TextOptions(L"Да", 40), 
    [&]()
    {
        RequestStateClear();
    }});
    _buttons.push_back({Decor.buttonSize, Decor.buttonRadius, game::TextOptions(L"Нет", 40), 
    [&]()
    {
        RequestStackPop();
        TransitAnimation(Direction::Disappear);
        
    }});
}

void game::ExitWindow::Align()
{
    _title.setPosition(_background.getBounds().width / 2, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);

    _buttons[0].SetPosition(Decor.margin + _buttons[0].getBounds().width / 2.f, 
                            _background.getBounds().height - Decor.titlePositionOnOY - _buttons[0].getBounds().height / 2.f);
    _buttons[1].SetPosition(_background.getBounds().width - Decor.margin - _buttons[1].getBounds().width / 2.f, 
                            _background.getBounds().height - Decor.titlePositionOnOY - _buttons[1].getBounds().height / 2.f);
}


game::ExitWindow::ExitWindow(game::GameStack* gameStack)
    : PopWindow(gameStack), _background({700.f, 180.f, 1400, 360}, 30.f, 0.f),
    _title({L"Вы хотите выйти из игры?", 70})
{
    init();
    Align();
};

void game::ExitWindow::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);
    _background.Draw(target);
    target->draw(_title);
    for (auto &button : _buttons) {
        button.Draw(target);
    }
}

void game::ExitWindow::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

bool game::ExitWindow::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    for (size_t i = 0; i < _buttons.size(); ++i)
        if(_buttons[i].Update(mousePositon, event))
            return true;
    
    return false;
}

void game::ExitWindow::SetOffset(float OXOffset, float OYOffset)
{
    _background.SetPosition(_background.GetPosition().x + OXOffset, _background.GetPosition().y + OYOffset);
    _title.setPosition(_title.getPosition().x + OXOffset, _title.getPosition().y + OYOffset);
    for (auto &button : _buttons) {
        button.SetPosition(button.GetPosition().x + OXOffset, button.GetPosition().y + OYOffset);
    }
}