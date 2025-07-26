#include "../../include/Windows/Settings.hpp"

void game::PlayerNickname::Align()
{
    _title.setPosition(0.f, 0.f);
    _textBox.SetPosition(0.f, GetHeight() - _textBox.getBounds().height / 2.f);
}

game::PlayerNickname::PlayerNickname() 
    : _title(game::TextOptions{L"Ник игрока", 40}),
    _textBox(PlayerSetup::GetName())
{
    init();
    Align();
}

void game::PlayerNickname::Draw(sf::RenderTarget* target)
{
    target->draw(_title);
    _textBox.Draw(target);
}

void game::PlayerNickname::SetOffset(float OXOffset, float OYOffset)
{
    _title.setPosition(_title.getPosition() + sf::Vector2f(OXOffset, OYOffset));
    _textBox.SetPosition(_textBox.GetPosition().x + OXOffset, _textBox.GetPosition().y + OYOffset);
}

game::ShowTips::ButtonWithAnswer::ButtonWithAnswer(const sf::FloatRect& rectangle, const float& radius, const Text &text, const std::function<void()>& function, 
                sf::Color topDefaultColor, 
                sf::Color bottomDefaultColor,
                sf::Color topHoverColor,
                sf::Color bottomHoverColor,
                sf::Color shadowColor,
                sf::Color outlineColor,
                float outlineThickness
    ) : ButtonWithText(rectangle, radius, text, function, topDefaultColor, bottomDefaultColor, topHoverColor, bottomHoverColor, shadowColor, outlineColor, outlineThickness),
    _blur(rectangle, radius, outlineThickness, Decor.blurColor, Decor.blurColor, Decor.blurColor)
{
    init();
    Align();
}

void game::ShowTips::ButtonWithAnswer::Draw(sf::RenderTarget* target) const
{
    ButtonWithText::Draw(target);
    if (!_isSelected)
        target->draw(_blur);
}

void game::ShowTips::ButtonWithAnswer::SetPosition(float x, float y)
{
    ButtonWithText::SetPosition(x, y);
    _blur.SetPosition(x, y);
}

void game::ShowTips::init()
{
    _yes.GetSelected() = BoardSetup::GetTips();
    _no.GetSelected() = !_yes.GetSelected();
}

void game::ShowTips::Align()
{
    _title.setPosition(0.f, 0.f);
    _yes.SetPosition(-_title.getGlobalBounds().width / 2.f + _yes.getBounds().width / 2.f, GetHeight() - _yes.getBounds().height / 2.f);
    _no.SetPosition(_title.getGlobalBounds().width / 2.f - _no.getBounds().width / 2.f, GetHeight() - _no.getBounds().height / 2.f);
}

game::ShowTips::ShowTips()
    : _title(game::TextOptions(L"Подсказки ходов", 40)),
    _yes(Decor.buttonSize, Decor.buttonRadius, TextOptions(L"Да", 40), 
    [&]()
    {
        BoardSetup::GetTips() = _yes.GetSelected() = true;
        _no.GetSelected() = false;
    }),

    _no(Decor.buttonSize, Decor.buttonRadius, TextOptions(L"Нет", 40), 
    [&]()
    {
        _no.GetSelected() = true;
        BoardSetup::GetTips() = _yes.GetSelected() = false;
    })
{
    init();
    Align();
}

void game::ShowTips::SetOffset(float OXOffset, float OYOffset)
{
    _title.setPosition(_title.getPosition() + sf::Vector2f(OXOffset, OYOffset));
    _yes.SetPosition(_yes.GetPosition().x + OXOffset, _yes.GetPosition().y + OYOffset);
    _no.SetPosition(_no.GetPosition().x + OXOffset, _no.GetPosition().y + OYOffset);
}

void game::ShowTips::Draw(sf::RenderTarget* target)
{
    target->draw(_title);
    _yes.Draw(target);
    _no.Draw(target);
}

void game::ShowTips::Update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    if (!_yes.GetSelected())
        _yes.Update(mousePos, event);
    
    if (!_no.GetSelected())
        _no.Update(mousePos, event);
}

void game::Options::GameField::Cell::Chip::SetCellItem(CellDefinitions cellItem)
{
    _cellItem = cellItem;
    switch (_cellItem)
    {
    case CellDefinitions::Black:
        setTexture(ResourceLoader::GetTexture("../Images/BlackChip/50px.png"));
        break;
    case CellDefinitions::White:
        setTexture(ResourceLoader::GetTexture("../Images/WhiteChip/50px.png"));
        break;
    default:
        break;
    }

    setOrigin(getGlobalBounds().width / 2.f, getGlobalBounds().height / 2.f);
}

void game::Options::GameField::Cell::init()
{
    _tip.setRadius(_background.getGlobalBounds().width / 3.f);
    _tip.setFillColor(sf::Color(0, 0, 0, 0));
    _tip.setOutlineColor(sf::Color::Black);
    _tip.setOrigin(_tip.getGlobalBounds().width / 2.f, _tip.getGlobalBounds().height / 2.f);
}

game::Options::GameField::Cell::Cell(game::Cell::CellOptions cellOptions, sf::Vector2i coordinates, std::vector<std::vector<Cell>>& cells)
    : _background(cellOptions._size), 
    _chip(cellOptions._cellItem), _coordinates(coordinates), _cells(cells)
{
    _background.setOrigin(cellOptions._size.x / 2, cellOptions._size.y / 2);
    _background.setFillColor(cellOptions._backgroundColor);
    
    init();
}

void game::Options::GameField::Cell::SetPosition(float x, float y)
{
    _background.setPosition(x, y);
    _chip.setPosition(x, y);
    _tip.setPosition(x, y);
}

void game::Options::GameField::Cell::Draw(sf::RenderTarget* target)
{
    target->draw(_background);
    target->draw(_chip);

    if (BoardSetup::GetTips())
        target->draw(_tip);
}

void game::Options::GameField::init()
{
    float paddingWidth = (_backgroundField.getBounds().width - Decor.cellSize * 8 - 7 * Decor.stepBetweenCells) / 2.f;
    float paddingHeight = (_backgroundField.getBounds().height - Decor.cellSize * 8 - 7 * Decor.stepBetweenCells) / 2.f;
    for (int i = 0; i < 8; i++) {
        _cells.push_back(std::vector<Cell>{});
        for (int j = 0; j < 8; j++) {
            _cells[i].push_back(Cell
            (
                game::Cell::CellOptions((i + j) % 2 == 0 ? BoardSetup::GetColors().at(_theme).y : BoardSetup::GetColors().at(_theme).z, 
                {Decor.cellSize, Decor.cellSize}, CellDefinitions::Empty),
                sf::Vector2i({i, j}),
                _cells
            ));
            _cells[i][j].SetPosition(-_backgroundField.getBounds().width / 2.f + (2 * j + 1) * Decor.cellSize / 2.f + paddingWidth + j * Decor.stepBetweenCells, 
            -_backgroundField.getBounds().height / 2.f + (2 * i + 1) * Decor.cellSize / 2.f + paddingHeight + i * Decor.stepBetweenCells);
        }
    }
    
    _cells[4][3].SetCellItem(CellDefinitions::Black);
    _cells[3][3].SetCellItem(CellDefinitions::White);
    _cells[3][4].SetCellItem(CellDefinitions::Black);
    _cells[4][4].SetCellItem(CellDefinitions::White);

    _cells[2][3].SetTip();
    _cells[3][2].SetTip();
    _cells[4][5].SetTip();
    _cells[5][4].SetTip();
}

game::Options::GameField::GameField(BoardSetup::Theme theme, std::function<void()> function,
            float outlineThickness, sf::Color outlineColor)
            
    : _backgroundField(Decor.backgroundSize, Decor.backgroundRadius, 
    outlineThickness, outlineColor, BoardSetup::GetColors().at(theme).x, BoardSetup::GetColors().at(theme).x), 
    _theme(theme), _function(function),
    _blur(Decor.backgroundSize, Decor.backgroundRadius, outlineThickness, Decor.blurColor, Decor.blurColor, Decor.blurColor), 
    _hoverBlur(Decor.backgroundSize, Decor.backgroundRadius, outlineThickness, Decor.hoverBlurColor, Decor.hoverBlurColor, Decor.hoverBlurColor)
{
    init();
    Align();
}

void game::Options::GameField::Draw(sf::RenderTarget* target)
{
    _backgroundField.Draw(target);
    
    for (auto &row : _cells)
        for (auto &cell : row)
            cell.Draw(target);

    if (_isHover)
        _hoverBlur.Draw(target);

    if (!_isActive)
        _blur.Draw(target);
}

void game::Options::GameField::SetOffset(float OXOffset, float OYOffset)
{
    _backgroundField.SetPosition(_backgroundField.GetPosition().x + OXOffset, _backgroundField.GetPosition().y + OYOffset);
    _blur.SetPosition(_blur.GetPosition().x + OXOffset, _blur.GetPosition().y + OYOffset);
    _hoverBlur.SetPosition(_hoverBlur.GetPosition().x + OXOffset, _hoverBlur.GetPosition().y + OYOffset);
    for (auto &row : _cells)
        for (auto &cell : row)
            cell.SetPosition(cell.GetPosition().x + OXOffset, cell.GetPosition().y + OYOffset);
}

void game::Options::GameField::Update(const sf::Vector2f& mousePos, const sf::Event& event) 
{
    if (_isActive || !(_isHover = _backgroundField.getBounds().contains(mousePos)))
        return;


    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        _isActive = true;
        _function();
    }
}

void game::Options::init()
{
    _solidGameField.GetActive() = BoardSetup::GetTheme() == BoardSetup::Theme::Solid;
    _colorfulGameField.GetActive() = BoardSetup::GetTheme() == BoardSetup::Theme::Сolorful;
}

void game::Options::Align()
{
    _back.SetPosition(Decor.backButtonMargin + _back.getBounds().width / 2.f, Decor.backButtonMargin + _back.getBounds().height / 2.f);

    _solidGameField.SetPosition(Decor.margin + _solidGameField.GetGlobalBounds().width / 2.f, GetRenderTexture()->getSize().y / 2.f);
    _colorfulGameField.SetPosition( GetRenderTexture()->getSize().x - Decor.margin - _colorfulGameField.GetGlobalBounds().width / 2.f, 
                                    GetRenderTexture()->getSize().y / 2.f);

    _playerNickname.SetPostion(GetRenderTexture()->getSize().x / 2.f, 
                ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.step + _playerNickname.GetHeight() / 2.f);
    _showTips.SetPosition(GetRenderTexture()->getSize().x / 2.f, 
            ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.step + _playerNickname.GetHeight() + Decor.step + _showTips.GetHeight() / 2.f);
}

void game::Options::SaveConfigurations() const
{
    BoardSetup::GetTheme() = _solidGameField.GetActive() ? BoardSetup::Theme::Solid : BoardSetup::Theme::Сolorful;
    PlayerSetup::GetName() = _playerNickname.GetName();
    BoardSetup::GetTips() = _showTips.IsShowed();
}

game::Options::Options(game::GameStack* gameStack)
    : ReversiTitle(gameStack),
    _back({Decor.buttonSize, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/Back.png")),
    [&]()
    {
        SaveConfigurations();
        Transition::Get()->SetFunction
        (
            [&]() 
            {
                GetGameStack()->PopState();
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
            
        Transition::Get()->SetMode(ShaderMode::Appear);
    }}),
    _solidGameField(BoardSetup::Theme::Solid,
    [&]()
    {
        _solidGameField.GetActive() = true;
        _solidGameField.GetHover() = false;

        _colorfulGameField.GetActive() = false;
    }), 
    _colorfulGameField(BoardSetup::Theme::Сolorful,
    [&]()
    {
        _solidGameField.GetActive() = false;

        _colorfulGameField.GetHover() = false;
        _colorfulGameField.GetActive() = true;
    })
{
    init();
    Align();
}

void game::Options::Draw(sf::RenderTarget* target)
{
    if (_playerNickname.IsFill())
        _back.Draw(target);       

    _solidGameField.Draw(target);
    _colorfulGameField.Draw(target);
    
    _playerNickname.Draw(target);
    _showTips.Draw(target);

    ReversiTitle::Draw(target); 
}

bool game::Options::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePosition)
{
    if (event.type == sf::Event::Closed) 
        RequestStateClear();

    if (_playerNickname.IsFill())
        if (_back.Update(mousePosition, event))
            return true;

    _colorfulGameField.Update(mousePosition, event);
    _solidGameField.Update(mousePosition, event);

    _playerNickname.Update(mousePosition, event);
    _showTips.Update(mousePosition, event);

    return false;
}
