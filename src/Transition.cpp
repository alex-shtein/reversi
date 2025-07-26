#include "../include/Transition.hpp"

game::Transition::Transition() 
	: _shader(new sf::Shader())
{
	if (_sInstance)
		throw std::runtime_error("Trying to create an already existing class Transition");

	_sInstance = this;
}

game::Transition* game::Transition::Get() 
{
	return _sInstance;
}

void game::Transition::SetFunction(std::function<void()> function) 
{ 
	_function = function; 
}

void game::Transition::Update(const float& dt) 
{
	_elapsedTime += dt;
	while (_elapsedTime >= _updateTime) 
	{
		_elapsedTime -= _updateTime;
		UpdateTransition((_mode == ShaderMode::Appear ? -1 : 1));
	}
}

void game::Transition::SetMode(game::ShaderMode mode) 
{
	_mode = mode;
}

sf::Shader& game::Transition::GetShader()
{ 
	return *_shader; 
}


void game::Transition::UpdateTransition(int step) 
{
	_shader->setUniform("progress", _progress);

	_progress += 1.f * step;

	if (step > 0) {
		if (_progress > 1.0f) {
			_progress = 1.0f;
			if (_function) {
				_function();
				_function = 0;
			}
		}
	}

	else {
		if (_progress < 0.0f) {
			_progress = 0.0f;
			if (_function) {
				_function();
				_function = 0;
			}
		}
	}
}

game::Transition* game::Transition::_sInstance = nullptr;