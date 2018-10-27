#pragma once
#include <functional>

class Repeater {

public:
	Repeater(float interval, std::function<void(void)>* callback, bool active = true);
	~Repeater();

	void Update(float dt);
	void SetActive(bool active);
	void SetInterval(float interval);
	void SetCallback(std::function<void(void)>* callback);

private:
	float m_interval;
	float m_elapsed;
	std::function<void(void)>* m_callback;
	bool m_active;
};