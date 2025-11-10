#include "CustomShape.hpp"

namespace CShape
{
	CustomShape::CustomShape(std::vector<std::string>& initData, sf::Font& font) : shapeLabel(font)
	{
		init(initData);
	}

	void CustomShape::init(std::vector<std::string>& initData)
	{
		initialData.label = initData[1];
		initialData.posX = std::stof(initData[2]);
		initialData.posY = std::stof(initData[3]);
		initialData.velX = std::stof(initData[4]);
		initialData.velY = std::stof(initData[5]);
		initialData.r	 = std::stoi(initData[6]);
		initialData.g	 = std::stoi(initData[7]);
		initialData.b	 = std::stoi(initData[8]);

		// Data tokens:
		// Type Labe PosX PosY VelX VelY R G B (Widht Height)/(Radius)
		if (initData[0].compare("Rectangle") == 0)
		{
			shape = std::make_shared<sf::RectangleShape>();
			shapeType = CustomShapeTypeEnum::RECTANGLE;

			std::dynamic_pointer_cast<sf::RectangleShape>(shape)->setSize({ std::stof(initData[9]) , std::stof(initData[10]) });			
		}
		else if (initData[0].compare("Circle") == 0)
		{
			shape = std::make_shared<sf::CircleShape>();
			shapeType = CustomShapeTypeEnum::CIRCLE;

			std::dynamic_pointer_cast<sf::CircleShape>(shape)->setRadius({ std::stof(initData[9]) });
		}

		setLabel(currentData.label);
		// set the character size in pixels
		shapeLabel.setCharacterSize(24);

		setPosition({ currentData.posX, currentData.posY });
		setVelocity(sf::Vector2(currentData.velX, currentData.velX));
		setColor(currentData.r, currentData.g, currentData.b);

		enable(true);
	}

	void CustomShape::enable(bool enable)
	{
		enabled = enable;
	}

	bool CustomShape::isEnabled()
	{
		return enabled;
	}

	void CustomShape::setFont(sf::Font& font)
	{
		shapeLabel.setFont(font);
	}

	void CustomShape::setPosition(const sf::Vector2f pos)
	{
		currentData.posX = pos.x;
		currentData.posY = pos.y;
	}

	void CustomShape::setVelocity(const sf::Vector2f vel)
	{
		currentData.velX = vel.x;
		currentData.velY = vel.y;
	}

	void CustomShape::setLabel(const std::string& label)
	{
		currentData.label = label;		
	}

	void CustomShape::setColor(const uint8_t r, const uint8_t g, const uint8_t b)
	{
		currentData.r = r;
		currentData.g = g;
		currentData.b = b;
	}

	void CustomShape::setScale(const float scale)
	{
		currentData.scale = scale;
	}

	void CustomShape::reset()
	{
		setLabel(initialData.label);

		setPosition({ initialData.posX, initialData.posY });
		// Update position only here, so it doesn't collide with move in update
		shape->setPosition({ initialData.posX, initialData.posY });

		setVelocity(sf::Vector2(initialData.velX, initialData.velX));
		setColor(initialData.r, initialData.g, initialData.b);
		setScale(initialData.scale);
	}

	void CustomShape::update()
	{
		//----SCALE----//
		shape->setScale({currentData.scale, currentData.scale});

		//----COLOR----//
		sf::Color shapeColor;
		shapeColor.r = currentData.r;
		shapeColor.g = currentData.g;
		shapeColor.b = currentData.b;
		shape->setFillColor(shapeColor);

		//-----MOVE-----//
		shape->move(sf::Vector2f{ currentData.velX, currentData.velY });

		//-----LABEL----//
		// set the string to display
		shapeLabel.setString(currentData.label);
		//Set origin point to center of label
		shapeLabel.setOrigin(shapeLabel.getLocalBounds().getCenter());
		// Update position according to shape position
		shapeLabel.setPosition(shape->getGlobalBounds().getCenter());
	}

	void CustomShape::checkCollisionWindow(const sf::RenderWindow& window)
	{
		auto shapeBounds = shape->getGlobalBounds();
		auto shapeBoundSize = shapeBounds.size;

		auto newPos = shape->getPosition();
		if ((newPos.x + shapeBoundSize.x) > window.getSize().x || newPos.x < 0.0f)
			currentData.velX *= -1;
		if ((newPos.y + shapeBoundSize.y) > window.getSize().y || newPos.y < 0.0f)
			currentData.velY *= -1;
	}

	void CustomShape::draw(sf::RenderWindow& window)
	{
		switch (shapeType)
		{
		case CustomShapeTypeEnum::RECTANGLE:
			window.draw(*(std::dynamic_pointer_cast<sf::RectangleShape>(shape).get()));
			break;
		case CustomShapeTypeEnum::CIRCLE:
			window.draw(*(std::dynamic_pointer_cast<sf::CircleShape>(shape).get()));
			break;
		}
	}
}