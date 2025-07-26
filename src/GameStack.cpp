#include "../include/GameStack.hpp"
#include <iostream>

game::GameStack::GameStack(sf::RenderTexture* renderTexture,  sf::RenderWindow* window)
    : _renderTexture(renderTexture), _window(window)
{}

game::GameStack::~GameStack()
{
    ClearStates();
};
void game::GameStack::Update(float dt)
{
    if (_stackOfStates.size() > 0)
        _stackOfStates.back()->Update(dt);
}

void game::GameStack::Draw(sf::RenderTarget* target)
{
    if (!_stackOfStates.empty())
        Back()->Draw(target);
}

void game::GameStack::ApplyPendingChanges()
{
    for(PendingChange change : _pendingList) {
        switch (change.action) {
            case Push:
                PushState(change.state);
                break;
            case Pop:
                PopState();
                break;
            case Clear:
                ClearStates();
                break;
        }
    }
    _pendingList.clear();
}

bool game::GameStack::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon)
{
    return Back()->HandleEvent(event, mousePositon);
}

void game::GameStack::PushState(State* state)
{
    _stackOfStates.push_back(state);
}

void game::GameStack::PopState()
{
    delete _stackOfStates.back();
    _stackOfStates.pop_back();
}

void game::GameStack::ClearStates()
{
    while (!_stackOfStates.empty()) 
        PopState();
}

game::State* game::GameStack::Back()
{
    return IsEmpty() ? nullptr : _stackOfStates.back();
}

game::State* game::GameStack::Penultimate()
{
    if (Size() < 2)
        throw std::runtime_error("Size!!!");

    return _stackOfStates[Size() - 2];
}

bool game::GameStack::IsEmpty() const
{
    return _stackOfStates.empty();
}

sf::RenderTexture* game::GameStack::GetRenderTexture()
{
    return _renderTexture;
}

void game::GameStack::AppendChange(PendingChange pendingChange)
{
    _pendingList.push_back(pendingChange);
}