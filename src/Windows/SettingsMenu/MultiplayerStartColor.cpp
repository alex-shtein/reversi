#include "../include/Windows/SettingsMenu/MultiplayerStartColor.hpp"

game::TextBox::TextBox()
    : Rectangle({0.f, 0.f, 320.f, 90.f}, 15.f, 0.f), 
    _currentText(game::TextOptions("", 40, sf::Color::White)), 
    _hintText(game::TextOptions(L"Введите имя", 40, sf::Color(255, 255, 255, 140)))
{
    init();
}

void game::TextBox::SetPosition(float x, float y)
{
    Rectangle::SetPosition(x, y);
    _currentText.setPosition(x, y);
    _hintText.setPosition(x, y);

    UpdateCursorPosition();
}

void game::TextBox::Update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    _isHover = Rectangle::getBounds().contains(mousePos);

    if (_isHover && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        _isActive = true;

    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        _isActive = false;
    
    SetOutlineThickness(_isHover || _isActive ? 4.f : 0.f);
    if (!_isActive)
        return;

    if (event.type == sf::Event::TextEntered)
    {
        auto size = _currentText.getString().getSize();
        switch (event.text.unicode)
        {
            case 0x8:
                if (size > 0)
                    _currentText.SetString(_currentText.getString().substring(0, size - 1));
                break;
            default:
                if (size < 9)
                    _currentText.SetString(_currentText.getString() + static_cast<wchar_t>(event.text.unicode));
                break;
        }
        UpdateCursorPosition();
    }
}

void game::TextBox::Update(float dt)
{   
    _elapsedTime += dt;
    if (_elapsedTime < 0.5f)
        return;

    _isUpdate = !_isUpdate;
    _elapsedTime = 0.f;
}

void game::TextBox::Draw(sf::RenderTarget* target)
{
    Rectangle::Draw(target);
    if (IsFill())
    {
        target->draw(_currentText);
        if (_isActive && _isUpdate)
            target->draw(_cursor);
        
        return;
    }
    
    if (_isActive)
    {
        if (_isUpdate)
            target->draw(_cursor);
        
        return;
    }
    
    target->draw(_hintText);
}

void game::MultiplayerStartColor::UpdateColor()
{
    auto position = _opponentColor.GetPosition();
    _opponentColor.SetPosition(_color.GetPosition().x, _color.GetPosition().y);
    _color.SetPosition(position.x, position.y);
}

void game::MultiplayerStartColor::init()
{
    _avatar.setOrigin(_avatar.getGlobalBounds().width / 2.f, _avatar.getGlobalBounds().height / 2.f);
    _opponentAvatar.setOrigin(_opponentAvatar.getGlobalBounds().width / 2.f, _opponentAvatar.getGlobalBounds().height / 2.f);

    _name = game::Text({PlayerSetup::GetName(), Decor.fontSize, Decor.color});

    _changeButton = ButtonWithIcon({Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/Swap.png")),
    [&]()
    {
        _currentOpponentColor = (_currentOpponentColor == MoveColor::Black ? MoveColor::White : MoveColor::Black);
        UpdateColor();
    }});
    
    _opponentColor = ButtonWithIcon({Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/BlackChip/60px.png"))});
    _color = ButtonWithIcon({Decor.sizeofButton, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/WhiteChip/60px.png"))});
}

game::MultiplayerStartColor::MultiplayerStartColor(sf::RenderTexture* renderTexture)
    : game::IGameSetting(renderTexture, {}), 
    _avatar(ResourceLoader::GetTexture("../Images/Avatar.png")),
    _opponentAvatar(ResourceLoader::GetTexture("../Images/Avatar.png")),
    _opponentName()
{
    init();
    Align();
}

void game::MultiplayerStartColor::Align()
{
    _avatar.setPosition(Decor.margin + _avatar.getLocalBounds().width / 2.f, _avatar.getPosition().y);
    _name.setPosition(Decor.margin + _avatar.getLocalBounds().width + Decor.stepBetweenAvatarAndName + _name.getGlobalBounds().width / 2.f, _name.getPosition().y);

    _opponentAvatar.setPosition(_renderTexture->getSize().x - Decor.margin - _opponentAvatar.getLocalBounds().width / 2.f, _opponentAvatar.getPosition().y);
    _opponentName.SetPosition(_opponentAvatar.getPosition().x - _opponentAvatar.getLocalBounds().width / 2.f - Decor.stepBetweenAvatarAndName - 
                                _opponentName.getBounds().width / 2.f, _opponentName.GetPosition().y);

    _changeButton.SetPosition(_renderTexture->getSize().x / 2.f, _changeButton.GetPosition().y);
    _color.SetPosition(_renderTexture->getSize().x / 2.f - _changeButton.getBounds().width / 2.f - Decor.sizeBetweenButtons - 
                        _color.getBounds().width / 2.f, _color.GetPosition().y);
    _opponentColor.SetPosition(_renderTexture->getSize().x / 2.f + _changeButton.getBounds().width / 2.f + Decor.sizeBetweenButtons + 
                                _opponentColor.getBounds().width / 2.f, _opponentColor.GetPosition().y);
}

void game::MultiplayerStartColor::SetPositionOnOY(float positionOnOY)
{
    _avatar.setPosition(_avatar.getPosition().x, positionOnOY);
    _name.setPosition(_name.getPosition().x, positionOnOY);

    _color.SetPosition(_color.GetPosition().x, positionOnOY);
    _changeButton.SetPosition(_changeButton.GetPosition().x, positionOnOY);
    _opponentColor.SetPosition(_opponentColor.GetPosition().x, positionOnOY);

    _opponentAvatar.setPosition(_opponentAvatar.getPosition().x, positionOnOY);
    _opponentName.SetPosition(_opponentName.GetPosition().x, positionOnOY);
}

void game::MultiplayerStartColor::Draw(sf::RenderTarget* target)
{
    target->draw(_avatar);
    target->draw(_opponentAvatar);

    target->draw(_name);
    _opponentName.Draw(target);

    _color.Draw(target);
    _opponentColor.Draw(target);
    _changeButton.Draw(target);
}

void game::MultiplayerStartColor::Update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    _changeButton.Update(mousePos, event);
    _opponentName.Update(mousePos, event);
}