/*class State;
class Context {
private:
	State *state;

public:
	Context() { state = 0; }
	void setState(State s) { state = &s; }
	bool getState() { return state->status(); }

};

class State {
public:
	virtual void doAction(Context context);
	virtual bool status();
};

class logged_in : State {
public:
	void doAction(Context context) { context.setState(*this); }
	bool status() { return true; }
};

class not_logged_in : State {
public:
	void doAction(Context context) { context.setState(*this); }
	bool status() { return false; }
};*/