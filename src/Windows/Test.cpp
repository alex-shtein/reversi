#include "../../include/Windows/Test.hpp"

void game::Test::init()
{   

}

void game::Test::Align()
{
    _title.setPosition(_background.getBounds().width / 2, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);
}


game::Test::Test(game::GameStack* gameStack)
    : PopWindow(gameStack), _background({700.f, 280.f, 1400, 360}, 30.f, 0.f),
    _title({L"Вы хотите выйти из игры?", 70})
{
    init();
    Align();
}

void game::Test::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);
    _background.Draw(target);
    target->draw(_title);
    for (auto &button : _buttons) {
        button.Draw(target);
    }
}

void game::Test::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

bool game::Test::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
}

void game::Test::SetOffset(float OXOffset, float OYOffset)
{
}