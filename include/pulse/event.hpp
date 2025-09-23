#ifndef PULSE_EVENT_HPP
#define PULSE_EVENT_HPP
#include <functional>
#include <vector>

namespace pulse
{
	/// <summary>
	/// Event class definition
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	template<typename ...Args>
	class Event
	{
	public:
		void addListener(std::function<void(Args...)> fn);

		void invoke(Args... args);
		void clear();


	private:
		std::vector <std::function<void(Args...)>> listeners;
	};

	// IMPLEMENTATION

	/// <summary>
	/// invoke calls all methods associated with this Event.
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	template<typename ...Args>
	void Event<Args...>::invoke(Args... args) {
		for (auto fn : listeners) {
			fn(std::forward<Args>(args)...);
		}
	}

	template<typename ...Args>
	void Event<Args...>::addListener(std::function<void(Args...)> fn) {
		listeners.push_back(fn);
	}

	template<typename ...Args>
	void Event<Args...>::clear() {
		listeners.clear();
	}


}
#endif