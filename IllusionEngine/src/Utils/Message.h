#pragma once
#include <iostream>

namespace Illusion
{
	class Entity;

	using event_type = unsigned short;
	class Message
	{

	public:
		Message(){}
		virtual ~Message() {}

		virtual void onSend(const Entity &entity, event_type type) = 0;
	};
}