#include "../include/Windows/GameParameters.hpp"

void game::GameParameters::Update()
{
    for (auto &&pair : _gameParameters)
        if(pair.second == _gameParametersID)
            _gameParametersText.setString(L"Режим игры: " + pair.first);

    for (auto &&pair : _gameTypes)
        if(pair.second == _gameTypeID)
            _gameTypeText.setString(L"Тип игры: " + pair.first);

    GameSetup::GetGameTypeID() = _gameTypeID;
    if (_gameTypeID == GameTypeID::Computer){
        GameSetup::GetOpponentName() = L"Компьютер";
        GameSetup::GetOpponentAvatarID() = AvatarID::Robot;
    }
    else    
        GameSetup::GetOpponentAvatarID() = AvatarID::Player; 

    GameSetup::GetGameParametersID() = _gameParametersID;
}

game::GameParameters::GameParameters(game::GameStack* gameStack)
    : ReversiTitle(gameStack),
    _back
    ({Decor.sizeofButtonWithIcon, Decor.radiusButtonWithIcon, sf::Sprite(ResourceLoader::GetTexture("../Images/Back.png")),
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

    }}), 
    _next
    ({Decor.sizeofButtonWithIcon, Decor.radiusButtonWithIcon, sf::Sprite(ResourceLoader::GetTexture("../Images/Correct.png")),
    [&]()
    {
        Transition::Get()->SetFunction
        (
            [&]() 
            {
                GetGameStack()->PushState(new game::SettingsMenu(GetGameStack()));
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
            
        Transition::Get()->SetMode(ShaderMode::Appear);

    }}),         
    _changeButtons
    (
        ButtonWithText{Decor.buttonSize, Decor.buttonRadius, Text({L"Изменить", 40}),
        [&]()
        {
            std::vector<ButtonWithText> buttons;
            for (auto &&pair : _gameParameters)
            {
                buttons.push_back(ButtonWithText(Decor.modeButtonSize, Decor.buttonRadius, Text({pair.first, 40}), 
                [&]()
                {
                    RequestStackPop();
                    reinterpret_cast<Choice*>(GetGameStack()->Back())->TransitAnimation(Direction::Disappear);
                    _gameParametersID = pair.second;
                    Update();
                }));
            }
            
            auto state = new game::Choice(GetGameStack(), Text({L"Выбор режима игры", 70}), buttons);
            GetGameStack()->PushState(state);
            state->TransitAnimation(Direction::Appear);

        }},
        ButtonWithText{Decor.buttonSize, Decor.buttonRadius, Text({L"Изменить", 40}),
        [&]()
        {
            std::vector<ButtonWithText> buttons;
            for (auto &&pair : _gameTypes)
            {
                buttons.push_back(ButtonWithText(Decor.typeButtonSize, Decor.buttonRadius, Text({pair.first, 40}), 
                [&]()
                {
                    RequestStackPop();
                    reinterpret_cast<Choice*>(GetGameStack()->Back())->TransitAnimation(Direction::Disappear);
                    _gameTypeID = pair.second;
                    Update();
                }));
            }
            
            auto state = new game::Choice(GetGameStack(), Text({L"Выбор типа игры", 70}), buttons);
            GetGameStack()->PushState(state);
            state->TransitAnimation(Direction::Appear);

        }}
    ), 
    _gameParametersText({L"Режим игры: обычные реверси" , 40}),
    _gameTypeText({L"Тип игры: игра с компьютером", 40})
{
    init();
    Align();
}

void game::GameParameters::AlignWidth()
{
    _back.SetPosition(Decor.ButtonWithIconMargin + _back.getBounds().width / 2.f, Decor.ButtonWithIconMargin + _back.getBounds().height / 2.f);
    _next.SetPosition(GetRenderTexture()->getSize().x - Decor.ButtonWithIconMargin - _next.getBounds().width / 2.f, Decor.ButtonWithIconMargin + _next.getBounds().height / 2.f);
    
    _gameParametersText.setPosition(Decor.margin + _gameParametersText.getGlobalBounds().width / 2.f, _gameParametersText.getPosition().y);
    _gameTypeText.setPosition(Decor.margin + _gameTypeText.getGlobalBounds().width / 2.f, _gameTypeText.getPosition().y);

    _changeButtons.x.SetPosition(GetRenderTexture()->getSize().x - Decor.margin - _changeButtons.x.getBounds().width / 2.f, _changeButtons.x.GetPosition().y);
    _changeButtons.y.SetPosition(GetRenderTexture()->getSize().x - Decor.margin - _changeButtons.y.getBounds().width / 2.f, _changeButtons.y.GetPosition().y);
}

void game::GameParameters::Align()
{
    AlignWidth();

    _changeButtons.x.SetPosition(_changeButtons.x.GetPosition().x, 
                                ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.stepBetweenTitleAndButtons + _changeButtons.x.getBounds().height / 2.f);
    _gameParametersText.setPosition(_gameParametersText.getPosition().x, _changeButtons.x.GetPosition().y);
    

    _changeButtons.y.SetPosition(_changeButtons.y.GetPosition().x, 
                                _changeButtons.x.GetPosition().y + _changeButtons.x.getBounds().height / 2.f + Decor.stepBetweenButtons + _changeButtons.y.getBounds().height / 2.f);
    _gameTypeText.setPosition(_gameTypeText.getPosition().x, _changeButtons.y.GetPosition().y);
}

void game::GameParameters::Draw(sf::RenderTarget* target)
{
    _next.Draw(target);
    _back.Draw(target);

    target->draw(_gameParametersText);
    target->draw(_gameTypeText);

    _changeButtons.x.Draw(target);
    _changeButtons.y.Draw(target);

    ReversiTitle::Draw(target);
}

bool game::GameParameters::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed)
        RequestStateClear();
        
    _changeButtons.x.Update(mousePositon, event);
    _changeButtons.y.Update(mousePositon, event);

    if (_back.Update(mousePositon, event))
        return true;

    return _next.Update(mousePositon, event);
}