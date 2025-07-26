#include "../include/Windows/SettingsMenu/Slider.hpp"

void game::Slider::init()
{
    RectangleShape::setSize({(_total - 1) * _step, Decor.sliderHeight});
    RectangleShape::setFillColor(Decor.sliderColor);
    RectangleShape::setOrigin(getSize().x / 2.f, getSize().y / 2.f);

    for (size_t i = 0; i < _total; ++i)
    {
        _marks.push_back(sf::CircleShape(Decor.markRadius));
        _marks.back().setOrigin(_marks.back().getGlobalBounds().width / 2.f, _marks.back().getGlobalBounds().height / 2.f);
        _marks.back().setFillColor(Decor.markDefaultColor);
        _marks.back().setOutlineColor(Decor.markDefaultOutlineColor);
        _marks.back().setOutlineThickness(Decor.markDefaultOutlineThickness);
    }

    SetActiveMark(_currentIndex);
}

void game::Slider::Align()
{
    RectangleShape::setPosition(0.f, 0.f);
    sf::Vector2f position = RectangleShape::getPosition() - sf::Vector2f(RectangleShape::getSize().x / 2.f, 0.f);
    for (auto &&mark : _marks)
    {
        mark.setPosition(position);
        position += sf::Vector2f(_step, 0.f);
    }
}

void game::Slider::Update(float OXMousePosition)
{
    if (!_locked)
        return;

    ResetMarks();
    if (OXMousePosition < getPosition().x - getGlobalBounds().width / 2.f)
    {
        SetActiveMark(_currentIndex = 0);
        return;
    }
    if (OXMousePosition > getPosition().x + getGlobalBounds().width / 2.f)
    {
        SetActiveMark(_currentIndex = _total - 1);
        return;
    }

    SetActiveMark(_currentIndex = round((OXMousePosition - getPosition().x + getGlobalBounds().width / 2.f) / _step));
}

game::Slider::Slider(int begin, int valueStep, int total, float step, int currentIndex)
    : _begin(begin), _valueStep(valueStep), _total(total), _step(step), _currentIndex(currentIndex)
{
    init();
    Align();
}

void game::Slider::SetOffset(float OXOffset, float OYOffset)
{
    sf::Vector2f offset = sf::Vector2f(OXOffset, OYOffset);

    RectangleShape::setPosition(getPosition() + offset);
    for (auto &&mark : _marks)
        mark.setPosition(mark.getPosition() + offset);
}

void game::Slider::ResetMarks()
{
    for (auto &&mark : _marks)
    {
        mark.setRadius(Decor.markRadius);
        mark.setOrigin(Decor.markRadius, Decor.markRadius);
        mark.setFillColor(Decor.markDefaultColor);
        mark.setOutlineColor(Decor.markDefaultOutlineColor);
        mark.setOutlineThickness(Decor.markDefaultOutlineThickness);
    }
}

void game::Slider::SetActiveMark(int index)
{
    _marks[index].setRadius(Decor.selectedMarkRadius);
    _marks[index].setOrigin(Decor.selectedMarkRadius, Decor.selectedMarkRadius);
    _marks[index].setOutlineColor(Decor.markSelectedOutlineColor);
    _marks[index].setFillColor(Decor.markSelectedColor);
    _marks[index].setOutlineThickness(Decor.markSelectedOutlineThickness);
}

void game::Slider::Draw(sf::RenderTarget* target) const
{
    target->draw(*this);
    for (auto &&mark : _marks)
        target->draw(mark);
}

bool game::Slider::Update(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::MouseMoved)
    {
        Update(mousePositon.x);
        return true;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && _marks[_currentIndex].getGlobalBounds().contains(mousePositon))
        Lock();

    else
        Unlock();

    return false;
}