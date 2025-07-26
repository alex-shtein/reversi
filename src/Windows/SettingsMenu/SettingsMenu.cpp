#include "../include/Windows/SettingsMenu/SettingsMenu.hpp"

void game::SettingsMenu::init()
{
    _gameSettings.push_back(new ChoiceWithSlider(GetRenderTexture(), Text({L"Размер поля: ", Decor.settingsFontSize, Decor.settingsColor}), Slider(8, 2, 3, 250.f)));
    _gameSettings.push_back(new ChoiceWithSlider(GetRenderTexture(), Text({L"Количество раундов: ", Decor.settingsFontSize, Decor.settingsColor}), Slider(1, 1, 9, 62.5f, 2)));

    if (GameSetup::GetGameTypeID() == GameTypeID::Computer)
    {
        _gameSettings.push_back(new ChoiceWithSlider(GetRenderTexture(), Text({L"Сложность игры: ", Decor.settingsFontSize, Decor.settingsColor}), Slider(1, 1, 3, 250.f, 1)));
        _gameSettings.push_back(new ComputerStartColor(GetRenderTexture()));
    }
    else
    {
        _gameSettings.push_back(new MultiplayerStartColor(GetRenderTexture()));
        Decor.stepBetweenTitleAndSettings = 90.f;
        Decor.stepBetweenSettings = 80.f;
    }   
}

void game::SettingsMenu::Align()
{
    _back.SetPosition(Decor.buttonWithIconMargin + _back.getBounds().width / 2.f, 
                        Decor.buttonWithIconMargin + _back.getBounds().height / 2.f);
    _play.SetPosition(GetRenderTexture()->getSize().x - Decor.buttonWithIconMargin - _play.getBounds().width / 2.f, 
                        Decor.buttonWithIconMargin + _play.getBounds().height / 2.f);

    float currentHeight = ReversiTitle::GetTitlePosition().y + ReversiTitle::GetTitleHeight() / 2.f + Decor.stepBetweenTitleAndSettings;
    for (auto &&setting : _gameSettings)
    {
        currentHeight += setting->GetHeight() / 2.f;
        setting->SetPositionOnOY(currentHeight);
        currentHeight += setting->GetHeight() / 2.f + Decor.stepBetweenSettings;
    }        
}

sf::Vector2i game::SettingsMenu::GetBlackHolePosition() const
{
    std::vector<sf::Vector2u> invalidPositions
    {
        {GameSetup::GetFieldSize() / 2,     GameSetup::GetFieldSize() / 2}, 
        {GameSetup::GetFieldSize() / 2 - 1, GameSetup::GetFieldSize() / 2},
        {GameSetup::GetFieldSize() / 2,     GameSetup::GetFieldSize() / 2 - 1},
        {GameSetup::GetFieldSize() / 2 - 1, GameSetup::GetFieldSize() / 2 - 1}
    };

    int x, y;
    do
    {
        x = rand() % GameSetup::GetFieldSize();
        y = rand() % GameSetup::GetFieldSize();
    } while (std::find(invalidPositions.begin(), invalidPositions.end(), sf::Vector2u(x, y)) != invalidPositions.end());
    
    return {x, y};
}

void game::SettingsMenu::SaveConfigurations() const
{
    GameSetup::GetFieldSize() = reinterpret_cast<ChoiceWithSlider*>(_gameSettings[0])->GetValue();
    GameSetup::GetNumberOfRounds() = reinterpret_cast<ChoiceWithSlider*>(_gameSettings[1])->GetValue();

    if (GameSetup::GetGameParametersID() == GameParametersID::ReversiWithBlackHole)
        GameSetup::GetBlackHolePosition() = GetBlackHolePosition();

    if (GameSetup::GetGameTypeID() == GameTypeID::Computer)
    {
        GameSetup::GetComputerDifficulty() = reinterpret_cast<ChoiceWithSlider*>(_gameSettings[2])->GetValue();
        GameSetup::GetOpponentMoveColor() = reinterpret_cast<ComputerStartColor*>(_gameSettings[3])->GetOpponentMoveColor();
        
        return;
    }
    GameSetup::GetOpponentMoveColor() = reinterpret_cast<MultiplayerStartColor*>(_gameSettings[2])->GetOpponentMoveColor();
    GameSetup::GetOpponentName() = reinterpret_cast<MultiplayerStartColor*>(_gameSettings[2])->GetOpponentName();
}

game::SettingsMenu::SettingsMenu(game::GameStack* gameStack)
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
    _play
    ({Decor.sizeofButtonWithIcon, Decor.radiusButtonWithIcon, sf::Sprite(ResourceLoader::GetTexture("../Images/Correct.png")),
    [&]()
    {
        SaveConfigurations();
        Transition::Get()->SetFunction
        (
            [&]() 
            {
                GetGameStack()->PushState(new GamingDisplay(GetGameStack()));
                Transition::Get()->SetMode(ShaderMode::Disappear);
            }
        );
            
        Transition::Get()->SetMode(ShaderMode::Appear);
    }})
{
    init();
    Align();
}

game::SettingsMenu::~SettingsMenu() 
{
    for (auto &&setting : _gameSettings)
        delete setting; 
}

void game::SettingsMenu::Draw(sf::RenderTarget* target)
{
    _back.Draw(target);
    if (GameSetup::GetGameTypeID() != GameTypeID::Multiplayer || reinterpret_cast<MultiplayerStartColor*>(_gameSettings.back())->GetOpponentName().getSize() > 0)
        _play.Draw(target);
    
    for (auto &&setting : _gameSettings)
        setting->Draw(target);

    ReversiTitle::Draw(target);
}

void game::SettingsMenu::Update(float dt)
{
    if (GameSetup::GetGameTypeID() == GameTypeID::Multiplayer)
        (reinterpret_cast<MultiplayerStartColor*>(_gameSettings.back()))->Update(dt);
}

bool game::SettingsMenu::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    if (event.type == sf::Event::Closed)
        RequestStateClear();
    
    for (auto &&setting : _gameSettings)
        setting->Update(mousePositon, event);

    if (_back.Update(mousePositon, event))
        return true;

    if (GameSetup::GetGameTypeID() != GameTypeID::Multiplayer || reinterpret_cast<MultiplayerStartColor*>(_gameSettings.back())->GetOpponentName().getSize() > 0)
        return _play.Update(mousePositon, event);

    return false;
}