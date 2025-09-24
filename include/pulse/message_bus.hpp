#ifndef PULSE_MESSAGE_BUS_HPP
#define PULSE_MESSAGE_BUS_HPP
#include <iostream>
#include <format>

namespace pulse
{
	template<typename TopicT, typename MessageT>
	class Message
	{
	public:
		Message(TopicT topic, MessageT message) : _topic(std::move(topic)), _message(std::move(message)) {}
		~Message() {}

		const TopicT& topic() const { return _topic; }
		const MessageT& message() const { return _message; }

	private:
		TopicT _topic;
		MessageT _message;
	};


	// override template for Message operator<<
	template<typename TopicT, typename MessageT>
	std::ostream& operator<<(std::ostream& os, const Message<TopicT, MessageT>& obj) {
		os << std::format("Topic: {} | Message: {}", obj.topic(), obj.message());
		return os;
	}

	/// <summary>
	/// Publisher creates messages for the subscribers and sends them to the Broker
	/// </summary>
	class Publisher
	{
	public: 
		Publisher() {}
		~Publisher() {}


	private:

	};

	/// <summary>
	/// Takes published messages from Publishers and sends them to Subscribers who are interested in that topic.
	/// </summary>
	class MessageBroker
	{

	};

	/// <summary>
	/// Can subscribe to topics and receive messages from those topics when available.
	/// </summary>
	class Subscriber
	{

	};


}

#endif