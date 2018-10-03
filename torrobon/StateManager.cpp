#include "StateManager.h"

StateManager::StateManager(Context* context) :
	m_context(context)
{
	// register states here
}

StateManager::~StateManager() {
	for (auto &itr : m_states) {
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Draw() {
	if (m_states.empty()) { return; }
	if (m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin()) {
			if (itr != m_states.end()) {
				if (!itr->second->IsTransparent()) {
					break;
				}
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr) {
			itr->second->Draw();
		}
	}
	else {
		m_states.back().second->Draw();
	}
}

void StateManager::Update(float dt) {
	if (m_states.empty()) { return; }
	if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin()) {
			if (itr != m_states.end()) {
				if (!itr->second->IsTranscendent()) {
					break;
				}
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr) {
			itr->second->Update(dt);
		}
	}
	else {
		m_states.back().second->Update(dt);
	}
}

void StateManager::SetState(const StateType& state) {
	// search for existing state, move to top of stack, enable
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) {
		if (itr->first == state) {
			m_states.back().second->OnDisable();
			StateType tmpType = itr->first;
			GameState* tmpState = itr->second;
			m_states.erase(itr);
			m_states.emplace_back(tmpType, tmpState);
			tmpState->OnEnable();
			return;
		}
	}
	// state wasn't found, create new
	if (!m_states.empty()) { m_states.back().second->OnDisable(); }
	CreateState(state);
	m_states.back().second->OnEnable();
}

void StateManager::CreateState(const StateType& type) {
	auto stateBuilder = m_stateFactory.find(type);
	if (stateBuilder == m_stateFactory.end()) { return; }
	GameState* state = stateBuilder->second();
	m_states.emplace_back(type, state);
	state->OnCreate();
}

Context* StateManager::GetContext() { return m_context; }