#pragma once
#include "Context.h"

class EntityDebugView {

public:
	EntityDebugView(Context* context) : 
		m_context(context)
	{
		m_overlay.setFillColor(sf::Color(255, 0, 0, 90));
		m_overlay.setOutlineColor(sf::Color::Red);
	}
	~EntityDebugView() {}

	void Draw() {
		std::vector<Entity*> entities = 
			*m_context->m_entityManager->GetEntities();
		for (auto itr : entities) {
			sf::FloatRect rect = itr->GetRect();
			m_overlay.setPosition({ rect.left, rect.top });
			m_overlay.setSize({ rect.width, rect.height });
			m_context->m_window->draw(m_overlay);
		}
	}

private:
	Context* m_context;
	sf::RectangleShape m_overlay;
};