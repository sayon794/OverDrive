#pragma once

namespace Overdrive {
	namespace Net {
		class Context;

		class State {
		public:
			virtual void doAction(Context &context) = 0;
			virtual bool status() = 0;
		};

		class Context {
		private:
			bool state = false;

		public:
			Context() { state = 0; }
			void setState(State &s) { state = (&s)->status();  }
			bool getState() { return state; }

		};

		class logged_in : State {
		public:
			void doAction(Context &context) { context.setState(*this); }
			bool status() { return true; }
		};

		class not_logged_in : State {
		public:
			void doAction(Context &context) { context.setState(*this); }
			bool status() { return false; }
		};
	}
}