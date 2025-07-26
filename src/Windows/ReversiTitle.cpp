#include "../../include/Windows/ReversiTitle.hpp"

void game::ReversiTitle::Align()
{
    _title.SetPosition(GetRenderTexture()->getSize().x / 2, Decor.titlePositionOnOY + _title.GetHeight() / 2.f);
    _mountainOfChips.setPosition(GetRenderTexture()->getSize().x / 2, GetRenderTexture()->getSize().y -  Decor.titlePositionOnOY / 2.f - _mountainOfChips.getGlobalBounds().height / 2.f);
}

game::ReversiTitle::ReversiTitle(GameStack* gameStack) 
    : State(gameStack), _title(Text({L"Реверси", Decor.titleFontSize, sf::Color::White}), sf::Sprite(ResourceLoader::GetTexture("../Images/PairOfChips.png"))),
    _mountainOfChips(ResourceLoader::GetTexture("../Images/MountainOfChips.png"))
{
    init();
    Align();
}

void game::ReversiTitle::Draw(sf::RenderTarget* target)
{
    target->draw(_mountainOfChips);
    _title.Draw(target);
}
