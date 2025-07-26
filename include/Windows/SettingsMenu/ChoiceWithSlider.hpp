#ifndef CHOICE_WITH_SLIDER_HPP
#define CHOICE_WITH_SLIDER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Slider.hpp"
#include "./IGameSetting.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/GameSetup.hpp"

namespace game
{
	/**
	 * @brief Класс ChoiceWithSlider, представляющий настройку с выбором с помощью ползунка
	 * 
	 * @details Унаследован от интерфейса IGameSetting
	 */
	class ChoiceWithSlider : public IGameSetting 
	{
	private:
		/**
		 * @brief Структура Decor для хранения декоративных параметров
		 */
		struct Decor
		{
			float margin = 280.f;                  ///< Отступ
			float stepBetweenTitleAndValue = 20.f; ///< Расстояние между заголовком и значением
		} Decor;

		Slider _slider;          ///< Объект ползунка
		unsigned _currentValue;  ///< Текущее значение
		game::Text _currentText; ///< Текст значения

		/**
		 * @brief Обновление состояния настройки
		 */
		void Update();

		void init() {} ///< Инициализация
	public:
		ChoiceWithSlider() = default;

		/**
		 * @brief Конструктор класса ChoiceWithSlider
		 * 
		 * @param renderTexture Указатель на RenderTexture
		 * @param title         Заголовок типа Text
		 * @param slider        Ползунок типа Slider
		 */
		ChoiceWithSlider(sf::RenderTexture* renderTexture, Text title, Slider slider);

		~ChoiceWithSlider() {};

		/**
		 * @brief Выравнивание элементов
		 */
		void Align();

		/**
		 * @brief Получить высоту настройки
		 * 
		 * @return Высота настройки
		 */
		float GetHeight() const override
		{
			return std::max(_settingName.getGlobalBounds().height, _slider.GetSize().y);
		}

		/**
		 * @brief Установить позицию на OY
		 * 
		 * @param positionOnOY Положение по OY
		 */
		void SetPositionOnOY(float positionOnOY) override;

		/**
		 * @brief Отрисовать настройку
		 * 
		 * @param target Цель отрисовки
		 */
		void Draw(sf::RenderTarget* target);

		/**
		 * @brief Обновить состояние настройки
		 * 
		 * @param mousePos Позиция мыши
		 * @param event Событие
		 */
		void Update(const sf::Vector2f& mousePos, const sf::Event& event) override;

		/**
		 * @brief Получить значение
		 * 
		 * @return Текущее значение
		 */
		unsigned GetValue() const { return  _currentValue; }
	};
}

#endif