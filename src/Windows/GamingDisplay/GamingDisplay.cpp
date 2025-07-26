#include "../include/Windows/GamingDisplay/GamingDisplay.hpp"

void game::Choice::init()
{
    float height = Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTitleAndButtons + _buttons.size() * Decor.stepBetweenButtons;
    for (auto &&button : _buttons)
        height += button.getBounds().height;

    float width = 2 * Decor.margin + std::max((*std::max_element(_buttons.begin(), _buttons.end(), 
    [](const ButtonWithText& first, const ButtonWithText& second) { return first.getBounds().width < second.getBounds().width; })).getBounds().width, _title.getGlobalBounds().width);

    _background = Rectangle({width / 2.f, height / 2.f, width, height}, 30.f, 0.f);
}

void game::Choice::Align()
{
    _title.setPosition(_background.getBounds().width / 2, Decor.titlePositionOnOY + _title.getGlobalBounds().height / 2.f);

    float currentHeight =  Decor.titlePositionOnOY + _title.getGlobalBounds().height + Decor.stepBetweenTitleAndButtons;
    for (auto &&button : _buttons)
    {
        currentHeight += button.getBounds().height / 2.f;
        button.SetPosition(_background.getBounds().width / 2, currentHeight);
        currentHeight += button.getBounds().height / 2.f + Decor.stepBetweenButtons;
    }
}

game::Choice::Choice(GameStack* gameStack, Text title, std::vector<ButtonWithText> buttons)
    : PopWindow(gameStack), _title(title), _buttons(buttons)
{
    init();
    Align();
}

void game::Choice::SetOffset(float OXOffset, float OYOffset)
{
    _background.SetPosition(_background.GetPosition().x + OXOffset, _background.GetPosition().y + OYOffset);
    _title.setPosition(_title.getPosition().x + OXOffset, _title.getPosition().y + OYOffset);
    for (auto &button : _buttons)
    {
        button.SetPosition(button.GetPosition().x + OXOffset, button.GetPosition().y + OYOffset);
    }
}

void game::Choice::DrawPopupWindow(sf::RenderTarget* target)
{
    target->draw(_blur);
    _background.Draw(target);
    target->draw(_title);
    for (auto &button : _buttons)
    {
        button.Draw(target);
    }
}

void game::Choice::Draw(sf::RenderTarget* target)
{
    DrawBackWindow(target);
    DrawPopupWindow(target);
}

bool game::Choice::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed)
        RequestStateClear();
            
    for (auto &&button : _buttons)
        if (button.Update(mousePositon, event))
            return true;
    
    return false;
}

void game::GamingDisplay::init()
{
    std::string sample = GameSetup::GetFieldSize() == 8 ? "../Images/Flip/60px/" : 
                        GameSetup::GetFieldSize() == 10 ? "../Images/Flip/50px/" : "../Images/Flip/40px/";
    for (size_t i = 1; i <= 5; ++i)
        _animations.push_back(sf::Sprite(ResourceLoader::GetTexture(sample + std::to_string(i) + ".png")));

    _background.append(sf::Vertex({0.f, 0.f}, sf::Color(0, 37, 74)));
    _background.append(sf::Vertex(sf::Vector2f(GetRenderTexture()->getSize().x, 0.f), sf::Color(0, 37, 74)));
    _background.append(sf::Vertex(sf::Vector2f(GetRenderTexture()->getSize()), sf::Color(0, 87, 126)));
    _background.append(sf::Vertex(sf::Vector2f(0.f, GetRenderTexture()->getSize().y), sf::Color(0, 87, 126)));

    _leftColumn.push_back
    (
        std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::GameColors())
    );

    if (GameSetup::GetNumberOfRounds() == 1)
        _rightColumn.push_back
        (
            std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::GameParameters())
        );

    else
        _leftColumn.push_back
        (
            std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::GameParameters())
        );

    if (GameSetup::GetGameTypeID() == GameTypeID::Computer)
        _leftColumn.push_back
        (
            std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::Difficulty())
        );

    if (GameSetup::GetNumberOfRounds() != 1)
    {
        _rightColumn.push_back
        (
            std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::RoundScore())
        );
        _rightColumn.push_back
        (
            std::unique_ptr<gameInformation::IGameInformation>(new gameInformation::Round(_currentRound))
        );
    }
}

void game::GamingDisplay::Align()
{
    _pause.SetPosition(GetRenderTexture()->getSize().x - Decor.buttonMargin - _pause.getBounds().width / 2.f, Decor.buttonMargin + _pause.getBounds().height / 2.f);

    _timeAndScore.SetPostion(GetRenderTexture()->getSize().x / 2.f, 0.f);

    float totalHeight = 0.f;

    for (auto &&info : _leftColumn)
        totalHeight += info->GetHeight() + Decor.stepBetweenGameInformationFileds;

    totalHeight -= Decor.stepBetweenGameInformationFileds;

    float center = GetRenderTexture()->getSize().x / 4.f - GetGameField().GetSize().x / 4.f;
    float currentHeight = GetRenderTexture()->getSize().y / 2.f - totalHeight / 2.f;

    for (auto &info : _leftColumn)
    {
        currentHeight += info->GetHeight() / 2.f;
        info->SetPosition(center, currentHeight);
        currentHeight += info->GetHeight() / 2.f + Decor.stepBetweenGameInformationFileds;
    }

    totalHeight = 0.f;

    for (auto &&info : _rightColumn)
        totalHeight += info->GetHeight() + Decor.stepBetweenGameInformationFileds;

    totalHeight -= Decor.stepBetweenGameInformationFileds;

    center = GetRenderTexture()->getSize().x - center;
    currentHeight = GetRenderTexture()->getSize().y / 2.f - totalHeight / 2.f;

    for (auto &info : _rightColumn) {
        currentHeight += info->GetHeight() / 2.f;
        info->SetPosition(center, currentHeight);
        currentHeight += info->GetHeight() / 2.f + Decor.stepBetweenGameInformationFileds;
    }

    _gameField.SetPosition(GetRenderTexture()->getSize().x / 2, GetRenderTexture()->getSize().y / 2);
}

game::GamingDisplay::GamingDisplay(game::GameStack* gameStack)
    : game::State(gameStack), _gameField(_playerColor, _opponentColor, _moveColor),
    _timeAndScore(_gameField),
    _pause
    (
        Decor.buttonSize, Decor.buttonRadius, sf::Sprite(ResourceLoader::GetTexture("../Images/Menu.png")),
        [&]()
        {
            GetGameField().GetComputerRunThread().terminate();
            std::vector<ButtonWithText> buttons
            ({
                ButtonWithText(Decor.sizeOfButtonsInPause, Decor.buttonRadius, Text({L"Продолжить", 40}), 
                [&]()
                {
                    RequestStackPop();
                    reinterpret_cast<Choice*>(GetGameStack()->Back())->TransitAnimation(Direction::Disappear);
                    if (GameSetup::GetGameTypeID() == GameTypeID::Computer && _moveColor == _opponentColor && _gameField.GetComputerRunning())
                        GetGameField().GetComputerRunThread().launch();
                }),
                ButtonWithText(Decor.sizeOfButtonsInPause, Decor.buttonRadius, Text({L"Рестарт", 40}), 
                [&]()
                {
                    Transition::Get()->SetFunction
                    (
                        [&]() 
                        {
                            GetGameStack()->PopState();
                            RestartRound();
                            Transition::Get()->SetMode(ShaderMode::Disappear);
                        }
                    );
				
			        Transition::Get()->SetMode(ShaderMode::Appear);
                }),
                ButtonWithText(Decor.sizeOfButtonsInPause, Decor.buttonRadius, Text({L"Вернуться в главное меню", 40}), 
                [&]()
                {
                    Transition::Get()->SetFunction
                    (
                        [&]() 
                        {
                            auto ptr = GetGameStack();
                            for (; ptr->Size() != 1; ptr->PopState());
                            Transition::Get()->SetMode(ShaderMode::Disappear);
                        }
                    );
				
			        Transition::Get()->SetMode(ShaderMode::Appear);
                })
            });

            auto state = new game::Choice(GetGameStack(), Text({L"Пауза", 70}), buttons);
            GetGameStack()->PushState(state);
            state->TransitAnimation(Direction::Appear);

        }
    )
{
    init();
    Align();
}

int game::GamingDisplay::GetPlayerRoundScore() const
{
    if (GameSetup::GetNumberOfRounds() == 1)
        return 0;
    
    return (reinterpret_cast<gameInformation::RoundScore*>(_rightColumn[0].get()))->GetPlayerScore();
}

int game::GamingDisplay::GetOpponenRoundScore() const
{
    if (GameSetup::GetNumberOfRounds() == 1)
        return 0;
    
    return (reinterpret_cast<gameInformation::RoundScore*>(_rightColumn[0].get()))->GetOpponentScore();
}

void game::GamingDisplay::Flip(bool flag)
{
    sf::Clock clock;
    int count = 0;
    while (count < 5)
    {
        float time = clock.getElapsedTime().asSeconds();
        if (time < 1.f / 20)
            continue;

        for (auto &cell : _gameField.GetCellsWithFlippedChips())
            cell->SetChipSprite(_animations[flag ? count : 4 - count]);

        GetWindow()->clear();
        GetWindow()->draw(_background);
        DrawWithoutAnimation(GetWindow());
        GetWindow()->display();

        clock.restart();
        ++count;
    }
}

 void game::GamingDisplay::FlipAnimation()
{
    Flip(_moveColor == CellDefinitions::White);
    for (auto &cell : _gameField.GetCellsWithFlippedChips())
        cell->SetCellItem(_moveColor);

    UpdateGameField();
    _timeAndScore.Update();
 }

game::GameField& game::GamingDisplay::GetGameField()
{
    return _gameField;
}

game::CellDefinitions& game::GamingDisplay::GetMoveColor()
{
    return _moveColor;
}

game::CellDefinitions& game::GamingDisplay::GetOpponentColor()
{
    return _opponentColor;
}

game::CellDefinitions& game::GamingDisplay::GetPlayerColor()
{
    return _playerColor;
}

void game::GamingDisplay::DrawWithoutAnimation(sf::RenderTarget* target)
{   
    _pause.Draw(target);
    _gameField.Draw(target);

    _timeAndScore.Draw(target);

    for (auto &&info : _leftColumn)
        info->Draw(target);

    for (auto &&info : _rightColumn)
        info->Draw(target);  
}

void game::GamingDisplay::Draw(sf::RenderTarget* target)
{
    if ((GameSetup::GetGameTypeID() != GameTypeID::Computer || _moveColor != _opponentColor) && GetGameStack()->Back() == this)
        sf::Vector2f mousePosition = GetWindow()->mapPixelToCoords(sf::Mouse::getPosition(*GetWindow()));
       
    if (_gameField.GetCellsWithFlippedChips().size() == 0) {
        _gameField.ShowPossibleMoves();
        DrawWithoutAnimation(target);

        return;
    }
        
    FlipAnimation();
}

void game::GamingDisplay::Restart()
{
    _isRoundOver = false;

    _timeAndScore.Reset();
    
    if (_currentRound % 2 == 0) {
        if (GameSetup::GetOpponentMoveColor() == MoveColor::Black) {
            GameSetup::GetOpponentMoveColor() = MoveColor::White;
            _opponentColor =  CellDefinitions::White;
            _playerColor = CellDefinitions::Black;
        }

        else {
            GameSetup::GetOpponentMoveColor() = MoveColor::Black;
            _opponentColor =  CellDefinitions::Black;
            _playerColor = CellDefinitions::White;
        }
    }
    
    (reinterpret_cast<gameInformation::GameColors*>(_leftColumn[0].get()))->Update();
    _gameField.SetStartPosition();
    _currentRound = 1;
    if (GameSetup::GetNumberOfRounds() > 1) {
        (reinterpret_cast<gameInformation::RoundScore*>(_rightColumn[0].get()))->Reset();
        (reinterpret_cast<gameInformation::Round*>(_rightColumn[1].get()))->Update();
    }

    DrawWithoutAnimation(GetRenderTexture()); 
}

void game::GamingDisplay::RestartRound()
{
    _isRoundOver = false;
    _gameField.SetStartPosition();

    _timeAndScore.Reset();

    DrawWithoutAnimation(GetRenderTexture());
}

void game::GamingDisplay::StartNextRound()
{
    _isRoundOver = false;
    ++_currentRound;

    if (GameSetup::GetOpponentMoveColor() == MoveColor::Black) {
        GameSetup::GetOpponentMoveColor() = MoveColor::White;
        _opponentColor =  CellDefinitions::White;
        _playerColor = CellDefinitions::Black;
    }

    else {
        GameSetup::GetOpponentMoveColor() = MoveColor::Black;
        _opponentColor =  CellDefinitions::Black;
        _playerColor = CellDefinitions::White;
    }

    _gameField.SetStartPosition();
    _timeAndScore.Reset();
    (reinterpret_cast<gameInformation::GameColors*>(_leftColumn[0].get()))->Update();
    (reinterpret_cast<gameInformation::Round*>(_rightColumn[1].get()))->Update();
    DrawWithoutAnimation(GetRenderTexture());
}


void game::GamingDisplay::UpdateGameField()
{
    _gameField.GetCellsWithFlippedChips().clear();
    if (!_gameField.ChangeMoveColor()) {
        _timeAndScore.Update();

        if (GameSetup::GetNumberOfRounds() == 1) {
            auto state = new EndQuickGame(GetGameStack(), this);
            GetGameStack()->PushState(state);
            state->TransitAnimation(Direction::Appear);

            return;
        }

        (reinterpret_cast<gameInformation::RoundScore*>(_rightColumn[0].get()))->Update(GetPlayerScore(), GetOpponentScore());
        
        PopWindow* state;
        if (GameSetup::GetNumberOfRounds() != _currentRound)
        {
            state = new EndRound(GetGameStack(), this);
            GetGameStack()->PushState(state);
            state->TransitAnimation(Direction::Appear);

            return;
        }

        state = new EndGame(GetGameStack(), this);
        GetGameStack()->PushState(state);
        state->TransitAnimation(Direction::Appear);

        return;
    }

    _gameField.SetComputerRunning(GameSetup::GetGameTypeID() == GameTypeID::Computer && _moveColor != _opponentColor);
    _gameField.ShowPossibleMoves();
}

void game::GamingDisplay::Update(float dt)
{
    if (_isRoundOver)
        return;

    _timeAndScore.Update(dt);
    if (GameSetup::GetGameTypeID() == GameTypeID::Computer && _moveColor == _opponentColor && !_gameField.GetComputerRunning()) // && !_isRoundOver)
    {
        _gameField.SetComputerRunning(true);
        _gameField.GetComputerRunThread().launch();
    }
}

bool game::GamingDisplay::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed) 
        RequestStateClear();
    
    if (event.key.code == sf::Keyboard::Escape)
    {
        _pause.GetFunction()();
        return true;
    }

    if (!_isRoundOver)
        _gameField.Update(mousePositon, event);

    return _pause.Update(mousePositon, event);
}