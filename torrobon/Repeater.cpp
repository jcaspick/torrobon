#include "Repeater.h"

Repeater::Repeater(float interval, std::function<void(void)>* callback, bool active) :
	m_interval(interval),
	m_callback(callback),
	m_active(active)
{}

Repeater::~Repeater() {}

void Repeater::Update(float dt) {
	m_elapsed = std::fmin(m_elapsed + dt, m_interval);
	if (m_active && m_elapsed >= m_interval) {
		m_elapsed -= m_interval;
		(*m_callback)();
	}
}

// setters

void Repeater::SetActive(bool active) { m_active = active; }
void Repeater::SetInterval(float interval) { m_interval = interval; }
void Repeater::SetCallback(std::function<void(void)>* callback) { m_callback = callback; }