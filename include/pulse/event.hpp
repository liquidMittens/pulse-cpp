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
		using Func = std::function<void(Args...)>;

	public:
		class EventConnection
		{
		public:
			friend Event;

			inline void connect(Event* owner, std::size_t newID)
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

			std::size_t _id = 0;
			Event* _eventOwner = nullptr;
		};

		template<typename ...Args>
		EventConnection addListener(Func fn) {
			++_currentID;
			EventConnection conn;
			conn.connect(this, _currentID);
			_listeners.emplace_back(_currentID, std::move(fn));
			return conn;
		}

		template<class F>
		EventConnection addListener(F&& f) {
			const std::size_t id = ++_currentID;
			EventConnection c; c.connect(this, id);
			_listeners.emplace_back(id, Func(std::forward<F>(f)));
			return c;
		}

		inline void invoke(const Args&... args);
		inline void clear();


	private:

		bool disconnectListener(std::size_t removeID);

		std::vector <std::pair<std::size_t, Func>> _listeners;
		std::size_t _currentID = 0;
	};

	// IMPLEMENTATION

	/// <summary>
	/// invoke calls all methods associated with this Event.
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	template<typename ...Args>
	void Event<Args...>::invoke(const Args&... args) {
		for (auto fn : _listeners) {
			fn.second(args...);
		}
	}

	template<typename ...Args>
	void Event<Args...>::clear() {
		_listeners.clear();
		_currentID = 0;
	}

	template<typename ...Args>
	bool Event<Args...>::disconnectListener(std::size_t removeID)
	{
		auto iter = std::remove_if(_listeners.begin(), _listeners.end(), [&](auto& pair) {
			return (pair.first == removeID);
			});

		_listeners.erase(iter);
		return true;
	}


}
#endif