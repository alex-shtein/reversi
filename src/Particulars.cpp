#include "../include/Particulars.hpp"

game::Text::Text(const game::TextOptions& textOptions)
{
    setLetterSpacing(2);
    setFont(ResourceLoader::GetFont(textOptions.fontFile));
    setString(textOptions.message);
    setCharacterSize(textOptions.sizeFont);
    setOutlineThickness(textOptions.bord);
    setFillColor(textOptions.textColor);
    setOutlineColor(textOptions.borderColor);
    setOrigin(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.5f + getCharacterSize() / 5.f);
}

void game::Text::SetString(const sf::String& string)
{
    sf::Text::setString(string);
    setOrigin(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.5f + getCharacterSize() / 5.f);
}

game::Rectangle::Rectangle(const sf::FloatRect& rectangle, const float& radius, 
    float outlineThickness, sf::Color outlineColor, sf::Color topColor, sf::Color bottomColor)
        : _center({rectangle.width / 2.f, rectangle.height / 2.f}), _outlineColor(outlineColor), _outlineThickness(outlineThickness)
{
    setPrimitiveType(sf::PrimitiveType::TriangleFan);
    std::vector<sf::Vector2f> sin_4;
    {
        const float PREC = M_PI_2 / 15;
        for(  float f = 0.0; f < M_PI_2; f += PREC) {
            sin_4.push_back({sinf(f) * radius, cosf(f) * radius});
        }
    }

    std::vector<sf::Vector2f> sin_4_reverse(sin_4.rbegin(), sin_4.rend());

    const float width   = rectangle.width  - radius;
    const float height = rectangle.height - radius;

    for(const auto& e : sin_4_reverse) {
        append(sf::Vertex({width + e.x, height + e.y}, bottomColor));
    }

    for(const auto& e : sin_4) {
        append(sf::Vertex({radius  - e.x, height + e.y}, bottomColor));
    }

    for(const auto& e : sin_4_reverse) {
        append(sf::Vertex({ radius - e.x, radius - e.y}, topColor));
    }

    for(const auto& e : sin_4) {
        append(sf::Vertex({ width  + e.x, radius - e.y}, topColor));
    }

    _outline.setPointCount(getVertexCount());
    for (int i = 0; i < _outline.getPointCount(); ++i) {
        _outline.setPoint(i, this->operator[](i).position);
    }

    _outline.setOrigin(_outline.getGlobalBounds().width / 2.f, _outline.getGlobalBounds().height / 2.f);
    _outline.setFillColor(sf::Color(0, 0, 0, 0));
    _outline.setOutlineThickness(_outlineThickness);
    _outline.setOutlineColor(_outlineColor);

    SetPosition(rectangle.left , rectangle.top);
}

void game::Rectangle::SetPosition(const sf::Vector2f& position)
{
    _outline.setPosition(position);
    for (size_t i = 0; i < getVertexCount(); ++i) {
        this->operator[](i).position += position - _center;
    }
    _center = position;
}

void game::Rectangle::SetOutlineThickness(float thickness)
{
    _outlineThickness = thickness;
    _outline.setOutlineThickness(_outlineThickness);
}

void game::Rectangle::SetTopColor(sf::Color topColor)
{
    for (size_t i = getVertexCount() - 1; i >= getVertexCount() / 2; --i) {
        this->operator[](i).color = topColor;
    }
}

void game::Rectangle::SetBottomColor(sf::Color bottomColor)
{
    for (size_t i = 0; i < getVertexCount() / 2; ++i) {
        this->operator[](i).color = bottomColor;
    }
}

void game::Rectangle::Draw(sf::RenderTarget* target) const
{
    target->draw(*this);
    target->draw(_outline);
}

game::Shadow::Shadow(const sf::FloatRect& rectangle, const float& radius, sf::Color color, float offset)
    : Rectangle({rectangle.left, rectangle.top + offset, rectangle.width + offset * 2.f, rectangle.height}, radius * 1.2f, 0.f, color, color, color), _color(color), _offset(offset) {}

void game::Shadow::SetFillColor(sf::Color color)
{
    _color = color;
    SetBottomColor(color);
    SetTopColor(color);
}

game::Button::Button(const sf::FloatRect rectangle, const float radius, std::function<void()> function, 
        sf::Color topDefaultColor, 
        sf::Color bottomDefaultColor,
        sf::Color topHoverColor,
        sf::Color bottomHoverColor,
        sf::Color shadowColor,
        sf::Color outlineColor,
        float outlineThickness            
        )
    : Rectangle(rectangle, radius, outlineThickness, outlineColor, topDefaultColor, bottomDefaultColor), 
    _shadow(rectangle, radius, shadowColor), 
    _function(function),
    _topDefaultColor(topDefaultColor),
    _bottomDefaultColor(bottomDefaultColor),
    _topHoverColor(topHoverColor),
    _bottomHoverColor(bottomHoverColor)
{}

void game::Button::SetPosition(float x, float y) 
{
    _shadow.SetPosition(x, y);
    Rectangle::SetPosition(x, y);
}

void game::Button::Draw(sf::RenderTarget* target) const 
{
    target->draw(_shadow);
    Rectangle::Draw(target);
}

bool game::Button::IsPressed(const sf::Event& event, const sf::Vector2f& position) const {
    if (!IsMouseOver(position))
        return false;
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        return true;

    return false;
}

bool game::Button::Update(const sf::Vector2f& mousePos)
{
    GetPointed() = getBounds().contains(mousePos);

    if (!GetPointed()) {
        SetTopColor(GetTopDefaultColor());
        SetBottomColor(GetBottomDefaultColor());

        return false;
    }
        
    SetTopColor(GetTopHoverColor());
    SetBottomColor(GetBottomHoverColor());

    return true;
}

bool game::Button::Update(const sf::Vector2f& mousePos, const sf::Event& event) 
{
    if (!Update(mousePos))
        return false;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)  {
        SetTopColor(GetTopDefaultColor());
        SetBottomColor(GetBottomDefaultColor());

        GetFunction()();

        return true;
    }

    return false;
}

game::Title::Title(Text title, sf::Sprite chips)
    : _title(title), _chips(chips)
{
    init();
}

void game::Title::init()
{
    for (size_t i = 0; i < 2; ++i) {
        _lines.push_back(sf::RectangleShape({Decor.lineWidth, Decor.lineHeight}));
        _lines.back().setFillColor(Decor.linesColor);
    }

    _lines.push_back(sf::RectangleShape({_title.getGlobalBounds().width, Decor.lineHeight}));
    _lines.back().setFillColor(Decor.linesColor);

    _chips.setOrigin(_chips.getGlobalBounds().width / 2.f, _chips.getGlobalBounds().height / 1.5f);

    Align();
}

void game::Title::Align()
{
    _lines[0].setPosition(0.f, 0.f);
    _lines[1].setPosition(_title.getGlobalBounds().width - _lines[1].getSize().x, 0.f);

    _chips.setPosition(_title.getGlobalBounds().width / 2.f, _lines[0].getSize().y);

    _title.setPosition(_title.getGlobalBounds().width / 2.f, _lines[0].getSize().y + Decor.stepBetweenLinesAndTitle + _title.getGlobalBounds().height / 2.f);

    _lines[2].setPosition(0.f, _title.getPosition().y + _title.getGlobalBounds().height / 2.f + Decor.stepBetweenLinesAndTitle);
}

void game::Title::SetOffset(sf::Vector2f offset)
{
    for (auto &line : _lines) {
        line.setPosition(line.getPosition() + offset);
    }

    _title.setPosition(_title.getPosition() + offset);
    _chips.setPosition(_chips.getPosition() + offset);
}

void game::Title::Draw(sf::RenderTarget* target)
{
    target->draw(_title);
    target->draw(_chips);

    for (auto &line : _lines)
        target->draw(line);
}

game::ButtonWithText::ButtonWithText(const sf::FloatRect& rectangle, const float& radius, const game::Text& text, const std::function<void()>& function, 
            sf::Color topDefaultColor, 
            sf::Color bottomDefaultColor,
            sf::Color topHoverColor,
            sf::Color bottomHoverColor,
            sf::Color shadowColor,
            sf::Color outlineColor,
            float outlineThickness
          )
		: Button(rectangle, radius, function, 
                topDefaultColor, bottomDefaultColor, topHoverColor, bottomHoverColor, shadowColor, outlineColor, outlineThickness),
            _text(text)
{
    _text.setPosition(Button::GetPosition());
}

void game::ButtonWithText::Draw(sf::RenderTarget* target) const
{
    Button::Draw(target);
    target->draw(_text);
}

void game::ButtonWithText::SetPosition(float x, float y) 
{
    Button::SetPosition(x, y);
    _text.setPosition(x, y);
}

game::ButtonWithIcon::ButtonWithIcon(const sf::FloatRect& rectangle, const float& radius, const sf::Sprite& icon, const std::function<void()>& function, 
        sf::Color topDefaultColor, 
        sf::Color bottomDefaultColor,
        sf::Color topHoverColor,
        sf::Color bottomHoverColor,
        sf::Color shadowColor,
        sf::Color outlineColor,
        float outlineThickness
        )
    : Button(rectangle, radius, function, 
            topDefaultColor, bottomDefaultColor, topHoverColor, bottomHoverColor, shadowColor, outlineColor, outlineThickness),
        _icon(icon)
{
    _icon.setOrigin(_icon.getGlobalBounds().width / 2.f, _icon.getGlobalBounds().height / 2.f);
    _icon.setPosition(Button::GetPosition());
}

void game::ButtonWithIcon::Draw(sf::RenderTarget* target) const 
{
    Button::Draw(target);
    target->draw(_icon);
}

void game::ButtonWithIcon::SetPosition(float x, float y) 
{
    Button::SetPosition(x, y);
    _icon.setPosition(x, y);
}