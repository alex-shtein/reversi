#include "../include/Windows/SettingsMenu/ChoiceWithSlider.hpp"

void game::ChoiceWithSlider::Update()
{
    _currentText.SetString(std::to_string(_currentValue));
    Align();
}

game::ChoiceWithSlider::ChoiceWithSlider(sf::RenderTexture* renderTexture, Text title, Slider slider)
    : game::IGameSetting(renderTexture, title), _slider(slider), _currentValue(_slider.GetValue()), 
    _currentText(game::TextOptions{std::to_string(_currentValue), (int)title.getCharacterSize(), title.getFillColor()})
{
    init();
    Align();
}

void game::ChoiceWithSlider::Align()
{
    _settingName.setPosition(Decor.margin + _settingName.getGlobalBounds().width / 2, _settingName.getPosition().y);

    _currentText.setPosition(_settingName.getPosition().x + _settingName.getGlobalBounds().width / 2 + Decor.stepBetweenTitleAndValue + _currentText.getGlobalBounds().width / 2.f,
                                    _currentText.getPosition().y);

    _slider.SetPosition(_renderTexture->getSize().x - Decor.margin - _slider.GetSize().x / 2.f, _slider.getPosition().y);

}

void game::ChoiceWithSlider::SetPositionOnOY(float positionOnOY)
{
    _settingName.setPosition(_settingName.getPosition().x, positionOnOY);
    _currentText.setPosition(_currentText.getPosition().x, positionOnOY);
    _slider.SetPosition(_slider.getPosition().x, positionOnOY);
}

void game::ChoiceWithSlider::Draw(sf::RenderTarget* target)
{
    target->draw(_settingName);
    target->draw(_currentText);

    _slider.Draw(target);
}

void game::ChoiceWithSlider::Update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    if (_slider.Update(event, mousePos))
    {
        _currentValue = _slider.GetValue();
        Update();
    }
}
