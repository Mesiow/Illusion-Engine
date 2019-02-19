#pragma once
#include <vector>
#include "Message.h"

namespace Illusion
{
	class Subject
	{
	public:
		Subject()
		{
			
		}
		~Subject()
		{
			for (std::size_t i = 0; i < messages_.size(); ++i)
				delete messages_[i];
		}

		void addMesssager(Message *msger)
		{
			messages_.push_back(msger);
		}

		void removeMessager(Message *msger)
		{
			
		}

	protected:
		void send(const Entity &entity, event_type type)
		{
			for (std::size_t i = 0; i < messages_.size(); ++i)
			{
				messages_[i]->onSend(entity, type);
			}
		}

	private:
		std::vector<Message*> messages_;
	};
}