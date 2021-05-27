#pragma once
#include "KeyCode.h"
namespace cookie
{
	class Key
	{
	public:
		bool justPressed {};
		bool pressed {};
		bool justUnpressed {};
		i32 keyCode {};
		Key(i32 key) : keyCode { key }
		{
		};
	};
}