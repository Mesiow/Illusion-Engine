#pragma once

namespace Illusion
{
	using Engine = std::mt19937;
	using device = std::random_device;

	class Random
	{
	public:
		Random(){}
		~Random(){}

	public:
		static int intInRange(int low, int high)
		{
			device d;
			Engine engine(d());
			std::uniform_int_distribution<int> dist(low, high);
		}

		static float floatInRange(float low, float high)
		{
			device d;
			Engine engine(d());
			std::uniform_real_distribution<float> dist(low, high);

			return dist(engine);
		}
	};
}