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
		int keyCode {};
		Key(int key) : keyCode { key }
		{
		};
	};
}