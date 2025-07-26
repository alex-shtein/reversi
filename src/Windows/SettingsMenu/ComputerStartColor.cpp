#include "../include/Windows/SettingsMenu/ComputerStartColor.hpp"

game::ComputerStartColor::ButtonWithColor::ButtonWithColor(const sf::FloatRect& rectangle, const float& radius, const sf::Sprite& icon, const std::function<void()>& function, 
                sf::Color topDefaultColor, 
                sf::Color bottomDefaultColor,
                sf::Color topHoverColor,
                sf::Color bottomHoverColor,
                sf::Color shadowColor,
                sf::Color outlineColor,
                float outlineThickness
        ) : ButtonWithIcon(rectangle, radius, icon, function, topDefaultColor, bottomDefaultColor, topHoverColor, bottomHoverColor, shadowColor, outlineColor, outlineThickness),
        _blur(rectangle, radius, outlineThickness, Decor.blurColor, Decor.blurColor, Decor.blurColor)
{
    init();
    Align();
}

void game::ComputerStartColor::ButtonWithColor::Draw(sf::RenderTarget* target) const
{
    ButtonWithIcon::Draw(target);
    if (!_isSelected)
        target->draw(_blur);
}

void game::ComputerStartColor::ButtonWithColor::SetPosition(float x, float y)
{
    ButtonWithIcon::SetPosition(x, y);
    _blur.SetPosition(x, y);
}

void game::ComputerStartColor::UpdateColor()
{
    _colorButtons[_position].GetSelected() = true;   
    _currentText.SetString(Decor.colors[_position]);
    Align();
}

void game::ComputerStartColor::ResetButtons()
{
    for (auto &&button : _colorButtons)
        button.GetSelected() = false;
}

void game::ComputerStartColor::init()
{
    _colorButtons.push_back
    (ButtonWithColor
    (
        Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/WhiteChip/60px.png")),
        [&]()
        {
            ResetButtons();
            _position = 0;
            UpdateColor();
        }
    ));
    _colorButtons.push_back
    (ButtonWithColor
    (
        Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/BWChip_60px.png")),
        [&]()
        {
            ResetButtons();
            _position = 1;
            UpdateColor();
        }
    ));
    _colorButtons.push_back
    (ButtonWithColor
    (
        Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/BlackChip/60px.png")),
        [&]()
        {
            ResetButtons();
            _position = 2;
            UpdateColor();
        }
    ));

    UpdateColor();
}

void game::ComputerStartColor::Align()
{
    _settingName.setPosition(Decor.margin + _settingName.getGlobalBounds().width / 2, _settingName.getPosition().y);

    _currentText.setPosition(_settingName.getPosition().x + _settingName.getGlobalBounds().width / 2 + Decor.stepBetweenTitleAndColor + _currentText.getGlobalBounds().width / 2.f,
                                _currentText.getPosition().y);

    float currentWidth = _renderTexture->getSize().x - Decor.margin;
    for (auto &&button : _colorButtons) {
        currentWidth -= button.getBounds().width / 2.f;
        button.SetPosition(currentWidth, button.GetPosition().y);
        currentWidth -= button.getBounds().width / 2.f + Decor.sizeBetweenButtons;
    }
}

game::ComputerStartColor::ComputerStartColor(sf::RenderTexture* renderTexture)
    : game::IGameSetting(renderTexture, game::TextOptions{L"Ваш цвет:", 40}), _position(0), 
    _currentText(game::TextOptions{L"", Decor.fontSize, Decor.titleColor})
{
    init();
}

void game::ComputerStartColor::SetPositionOnOY(float positionOnOY)
{
    _settingName.setPosition(_settingName.getPosition().x, positionOnOY);
    _currentText.setPosition(_currentText.getPosition().x, positionOnOY);
    for (auto &&button : _colorButtons)
        button.SetPosition(button.GetPosition().x, positionOnOY);
}

void game::ComputerStartColor::Draw(sf::RenderTarget* target)
{
    target->draw(_settingName);
    target->draw(_currentText);
    for (auto &&button : _colorButtons)
        button.Draw(target);
}

void game::ComputerStartColor::Update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    for (auto &&button : _colorButtons)
        if (!button.GetSelected())
            button.Update(mousePos, event);
}