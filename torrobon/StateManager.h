#pragma once
#ifndef STATE_MANAGER
#define STATE_MANAGER
#include "GameState.h"
#include "Context.h"
#include <functional>

enum class StateType {
	Menu,
	Game,
	Paused,
	GameOver
};

using StateStack = std::vector<std::pair<StateType, GameState*>>;
using StateFactory = std::unordered_map<StateType, std::function<GameState*(void)>>;

class StateManager {

public:
	StateManager(Context* context);
	~StateManager();

	void Update(float dt);
	void Draw();
	void SetState(const StateType& state);

	Context* GetContext();

private:
	void CreateState(const StateType& state);

	template<class T>
	void RegisterState(const StateType& type) {
		m_stateFactory[type] = [this]() -> GameState*
		{
			return new T(this);
		};
	}

	Context* m_context;
	StateStack m_states;
	StateFactory m_stateFactory;
};

#endif // !STATE_MANAGER