#ifndef PULSE_EVENT_HPP
#define PULSE_EVENT_HPP
#include <functional>
#include <vector>
#include <memory>

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
		class EventConnection
		{
			friend Event;

			inline void connect(Event* owner, int newID)
			{
				_eventOwner = owner;
				_id = newID;
			}

			inline void disconnect()
			{
				if (_eventOwner != nullptr) {
					_eventOwner->disconnectListener(_id);
				}
			}

			int _id;
			Event* _eventOwner;
		};


		EventConnection addListener(std::function<void(Args...)> fn);
		inline void invoke(Args... args);
		inline void clear();


	private:

		bool disconnectListener(int removeID);

		std::vector <std::pair<EventConnection, std::function<void(Args...)>>> _listeners;
		int _currentID;
	};

	// IMPLEMENTATION

	/// <summary>
	/// invoke calls all methods associated with this Event.
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	template<typename ...Args>
	void Event<Args...>::invoke(Args... args) {
		for (auto fn : _listeners) {
			fn.second(std::forward<Args>(args)...);
		}
	}

	template<typename ...Args>
	pulse::Event<Args...>::EventConnection Event<Args...>::addListener(std::function<void(Args...)> fn) {
		++_currentID;
		Event<Args...>::EventConnection conn;
		conn.connect(this, _currentID);
		_listeners.push_back(std::make_pair(conn, std::move(fn)));
		return conn;
	}

	template<typename ...Args>
	void Event<Args...>::clear() {
		_listeners.clear();
		_currentID = 0;
	}

	template<typename ...Args>
	bool Event<Args...>::disconnectListener(int removeID)
	{
		auto iter = std::remove_if(_listeners.begin(), _listeners.end(), [=](auto& pair) {
			return (pair.first == removeID);
			});
		if(iter)
			_listeners.erase(iter);
	}


}
#endif