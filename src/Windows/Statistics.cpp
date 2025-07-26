#include "../../include/Windows/Statistics.hpp"

void game::Statistics::Align()
{
    _back.SetPosition(Decor.backButtonMargin + _back.getBounds().width / 2.f, Decor.backButtonMargin + _back.getBounds().height / 2.f);

    float currentHeight = ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.stepBetweenTitleAndText;
    for (auto &statistic : _statistics) {
        currentHeight += statistic.x.getGlobalBounds().height / 2.f;
        statistic.x.setPosition(Decor.margin + statistic.x.getGlobalBounds().width / 2.f, currentHeight);
        statistic.y.setPosition(GetRenderTexture()->getSize().x - Decor.margin - statistic.y.getGlobalBounds().width / 2.f, currentHeight);
        currentHeight += statistic.x.getGlobalBounds().height / 2.f + Decor.stepBetweenStatistcs;
    }
}

game::Statistics::Statistics(game::GameStack* gameStack)
    : ReversiTitle(gameStack), 
    _statistics
    ({
        { TextOptions{L"Всего сыгранных игр:", 52}, TextOptions{std::to_string(ResultsSetup::GetTotal()), 52} },
        { TextOptions{L"Победы:", 52},              TextOptions{std::to_string(ResultsSetup::GetWins()), 52} },
        { TextOptions{L"Поражения:", 52},           TextOptions{std::to_string(ResultsSetup::GetLoses()), 52} },
        { TextOptions{L"Ничьи:", 52},               TextOptions{std::to_string(ResultsSetup::GetDraws()), 52} }
    }),
    _back({Decor.buttonSize, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/Back.png")),
    [&]()
    {
        Transition::Get()->SetFunction
        (
            [&]()
            {
                GetGameStack()->PopState();
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
            
        Transition::Get()->SetMode(ShaderMode::Appear);
    }})
{
    init();
    Align();
}

void game::Statistics::Draw(sf::RenderTarget* target)
{
    _back.Draw(target);
    
    for (auto &&text : _statistics) {
        target->draw(text.x);
        target->draw(text.y);
    }

    ReversiTitle::Draw(target);
}

bool game::Statistics::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed) {
        RequestStateClear();
    }

    return _back.Update(mousePositon, event);
}