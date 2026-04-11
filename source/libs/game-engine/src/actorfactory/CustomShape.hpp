#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

namespace CShape
{

	enum class CustomShapeTypeEnum : int {
		NONE = 0,
		RECTANGLE,
		SQUARE,
		CIRCLE
	};

	struct CustomShapeData {

		std::string label;

		float posX, posY;
		float velX, velY;

		uint8_t r, g, b;

		float scale;
	};
	
	class CustomShape
	{
	private:

		bool enabled = false;

		CustomShapeTypeEnum shapeType = CustomShapeTypeEnum::NONE;

		CustomShapeData initialData{ "", 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 1.0f };
		CustomShapeData currentData{ "", 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 1.0f };

		sf::Text shapeLabel;

		std::shared_ptr<sf::Shape> shape;

	public:

		CustomShape() = default;
		virtual ~CustomShape() = default;

		CustomShape(std::vector<std::string>& initData, sf::Font& font);

		void init(std::vector<std::string>& initData);

		void enable(bool enable);
		bool isEnabled();

		void setFont(sf::Font& font);

		void setPosition(const sf::Vector2f pos);
		void setVelocity(const sf::Vector2f vel);
		void setLabel(const std::string& label);
		void setColor(const uint8_t r, const uint8_t g, const uint8_t b);
		void setScale(const float scale);

		std::string getLabel();
		float getScale();
		sf::Vector2f getVelocity();
		sf::Color getColor();

		void reset();

		void update();

		void checkCollisionWindow(const sf::RenderWindow& window);

		void draw(sf::RenderWindow& window);

	};
}
