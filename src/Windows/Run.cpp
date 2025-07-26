#include "../include/Windows/Run.hpp"
#include <iostream>

void game::Run::init()
{
    _renderTexture->create(_window->getSize().x, _window->getSize().y, settings);
    //Transition::Get()->GetShader().loadFromFile("../Shaders/transitionVertex.shader", "../Shaders/transitionFragment.shader");
    _gameStack->PushState(new game::MainMenu(_gameStack));

    _background.append(sf::Vertex({0.f, 0.f}, sf::Color(0, 37, 74)));
    _background.append(sf::Vertex(sf::Vector2f(_renderTexture->getSize().x, 0.f), sf::Color(0, 37, 74)));
    _background.append(sf::Vertex(sf::Vector2f(_renderTexture->getSize()), sf::Color(0, 87, 126)));
    _background.append(sf::Vertex(sf::Vector2f(0.f, _renderTexture->getSize().y), sf::Color(0, 87, 126)));
}

void game::Run::Update(float dt)
{
    _gameStack->Update(dt);
    Transition::Get()->Update(dt);
}

void game::Run::Draw() 
{
    _renderTexture->clear();
    _renderTexture->draw(_background);
    _gameStack->Draw(_renderTexture);
    _renderTexture->display();

    _textureSprite.setTexture(_renderTexture->getTexture());

    _window->clear();
    _window->draw(_background);
    _window->draw(_textureSprite, &Transition::Get()->GetShader());
    _window->display();
}

void game::Run::ProcessEvents()
{
    for (sf::Event event; _window->pollEvent(event); ) {
        sf::Vector2f mousePosition = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

        if (_gameStack->HandleEvent(event, mousePosition)) {
            break;
        }
    }
    _gameStack->ApplyPendingChanges(); 
}

game::Run::Run()
    : _resourceLoader(ResourceLoader()), _transitionShader(), _window(new sf::RenderWindow{sf::VideoMode::getDesktopMode(), "Reversi", sf::Style::Fullscreen, settings}),
    _renderTexture(new sf::RenderTexture()), _textureSprite(),
    _gameStack(new game::GameStack(_renderTexture, _window))
{
    init();
    
    sf::Clock clock;
    float dt{};
    while (!_gameStack->IsEmpty()) {
        ProcessEvents();
        dt = clock.restart().asSeconds();
        Update(dt);
        Draw();
    }
}

game::Run::~Run()
{
    BoardSetup::Save();
    PlayerSetup::Save();
    ResultsSetup::Save();

    delete _window;
    delete _renderTexture;
    delete _gameStack;
}
