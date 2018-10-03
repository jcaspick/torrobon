#pragma once
#ifndef GAME_STATE
#define GAME_STATE

class StateManager;

class GameState {
	friend class StateManager;

public:
	GameState(StateManager* stateMgr) :
		m_stateMgr(stateMgr),
		m_transparent(false),
		m_transcendent(false)
	{}
	virtual ~GameState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	bool IsTransparent() const { return m_transparent; }
	bool IsTranscendent() const { return m_transcendent; }
	StateManager* GetStateManager() { return m_stateMgr; }

protected:
	StateManager* m_stateMgr;
	bool m_transparent;
	bool m_transcendent;
};

#endif // !GAME_STATE
