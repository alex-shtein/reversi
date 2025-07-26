#include "../include/Windows/PopWindow.hpp"

game::PopWindow::PopWindow(game::GameStack* gameStack)
    : game::State(gameStack)
{
    _blur.setSize({(float)GetRenderTexture()->getSize().x, (float)GetRenderTexture()->getSize().y});
    _blur.setFillColor(sf::Color(0, 0, 0, 150));
};

void game::PopWindow::TransitAnimation(Direction direction)
{
    SetPosition({GetRenderTexture()->getSize().x / 2.f, GetRenderTexture()->getSize().y / 2.f});

    sf::Clock clock;
    sf::RenderTexture texture;
    texture.create(GetRenderTexture()->getSize().x, GetRenderTexture()->getSize().y, GetWindow()->getSettings());
    sf::Sprite textureSprite;
    float progress = direction == Direction::Appear ? 0.f : 1.f;

    sf::VertexArray background = sf::VertexArray(sf::PrimitiveType::TriangleFan);
    background.append(sf::Vertex({0.f, 0.f}, sf::Color(0, 37, 74)));
    background.append(sf::Vertex(sf::Vector2f(GetRenderTexture()->getSize().x, 0.f), sf::Color(0, 37, 74)));
    background.append(sf::Vertex(sf::Vector2f(GetRenderTexture()->getSize()), sf::Color(0, 87, 126)));
    background.append(sf::Vertex(sf::Vector2f(0.f, GetRenderTexture()->getSize().y), sf::Color(0, 87, 126)));

    while((direction == Direction::Appear && progress < 1.f) || (direction == Direction::Disappear && progress > 0.f))
    {
        float time = clock.getElapsedTime().asSeconds();
        if (time < 1.f / 60)
            continue;

        Transition::Get()->GetShader().setUniform("progress", progress);
        progress -= (float)direction * 0.05f;

        texture.clear(sf::Color(0, 0, 0, 0));
        DrawPopupWindow(&texture);
        texture.display();
        textureSprite.setTexture(texture.getTexture());

        GetWindow()->clear(sf::Color(0, 0, 0, 0));
        GetWindow()->draw(background);
        DrawBackWindow(GetWindow());
        GetWindow()->draw(textureSprite, &Transition::Get()->GetShader());
        

        GetWindow()->display();

        clock.restart();
    }
}