#pragma once

#include <map>
#include <string>

namespace Tools
{
	namespace General
	{
		template <class T>
		class SmartEnum
		{
		protected:

			T mValue;

		public:

			SmartEnum() = default;
			SmartEnum(T pValue) : mValue(mValue) {};
			virtual ~SmartEnum() = default;

			void setEnum(T value)
			{
				mValue = value;
			}
			T getEnum()
			{
				return mValue;
			}
			virtual std::string toString() = 0;
		};
	}
	
}