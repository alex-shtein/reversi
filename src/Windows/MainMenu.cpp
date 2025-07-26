#include "../../include/Windows/MainMenu.hpp"

void game::MainMenu::init()
{
    _play = ButtonWithText({Decor.buttonSize, Decor.buttonRadius, game::TextOptions(L"Играть", 40), 
    [&]()
    {
        Transition::Get()->SetFunction
        (
            [&]()
            {
                GetGameStack()->PushState(new game::GameParameters(GetGameStack()));
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
        Transition::Get()->SetMode(ShaderMode::Appear);
    }});

    _statistics = ButtonWithText({Decor.buttonSize, Decor.buttonRadius, game::TextOptions(L"Статистика", 40), 
    [&]()
    {
        Transition::Get()->SetFunction
        (
            [&]() 
            {
                GetGameStack()->PushState(new Statistics(GetGameStack()));
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
        Transition::Get()->SetMode(ShaderMode::Appear);
    }});
}

game::MainMenu::MainMenu(game::GameStack* gameStack)
    : ReversiTitle(gameStack),
    _exit({0.f, 0.f, 90.f, 90.f}, 15.f, sf::Sprite(ResourceLoader::GetTexture("../Images/Back.png")),
    [&]()
    {
        auto state = new game::ExitWindow(GetGameStack());
        GetGameStack()->PushState(state);
        state->TransitAnimation(Direction::Appear);
    }),
    _settings({0.f, 0.f, 90.f, 90.f}, 15.f, sf::Sprite(ResourceLoader::GetTexture("../Images/Settings.png")),
    [&]()
    {
        Transition::Get()->SetFunction
        (
            [&]() 
            {
                GetGameStack()->PushState(new Options(GetGameStack()));
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
        Transition::Get()->SetMode(ShaderMode::Appear);
    })
{
    init();
    Align();
}

void game::MainMenu::AlignWidth()
{

    _play.SetPosition(GetRenderTexture()->getSize().x / 2, _play.GetPosition().y);
    _statistics.SetPosition(GetRenderTexture()->getSize().x / 2, _statistics.GetPosition().y);
    _exit.SetPosition(GetRenderTexture()->getSize().x / 2 - Decor.buttonSize.width / 2.f + _exit.getBounds().width / 2.f, _exit.GetPosition().y);
    _settings.SetPosition(GetRenderTexture()->getSize().x / 2 + Decor.buttonSize.width / 2.f - _settings.getBounds().width / 2.f, _settings.GetPosition().y);
}

void game::MainMenu::Align()
{
    AlignWidth();

    _play.SetPosition(_play.GetPosition().x, ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.stepBetweenTitleAndButtons + _play.getBounds().height / 2.f);
    _statistics.SetPosition(_statistics.GetPosition().x, _play.GetPosition().y + _play.getBounds().height / 2.f + Decor.stepBetweenButtons + _statistics.getBounds().height / 2.f);
    _exit.SetPosition(_exit.GetPosition().x, _statistics.GetPosition().y + _statistics.getBounds().height / 2.f + Decor.stepBetweenButtons + _exit.getBounds().height / 2.f);
    _settings.SetPosition(_settings.GetPosition().x, _statistics.GetPosition().y + _statistics.getBounds().height / 2.f + Decor.stepBetweenButtons + _exit.getBounds().height / 2.f);
}

void game::MainMenu::Draw(sf::RenderTarget* target)
{
    if (GetGameStack()->Back() == this) {
        sf::Vector2f mousePosition = GetWindow()->mapPixelToCoords(sf::Mouse::getPosition(*GetWindow()));
        _play.Update(mousePosition);
        _statistics.Update(mousePosition);
        _exit.Update(mousePosition);
        _settings.Update(mousePosition);
    }

    _play.Draw(target);
    _statistics.Draw(target);
    _exit.Draw(target);
    _settings.Draw(target);

    ReversiTitle::Draw(target);
}

bool game::MainMenu::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed)
        RequestStateClear();

    if (_play.Update(mousePositon, event))
        return true;

    if (_statistics.Update(mousePositon, event))
        return true;

    if (_exit.Update(mousePositon, event))
        return true;

    return _settings.Update(mousePositon, event);
}