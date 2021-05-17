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
		KeyCode keyCode {};
		Key(KeyCode key) : keyCode { key }
		{
		};
	};
}