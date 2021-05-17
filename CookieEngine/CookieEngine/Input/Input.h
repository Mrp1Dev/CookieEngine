#pragma once
#include <unordered_map>
#include <array>
#include "Key.h"
#include "KeyCode.h"
namespace cookie
{
	class Input
	{
	public:
		using KeyBoolMap = std::unordered_map<KeyCode, bool>;
		std::unordered_map<KeyCode, Key> keys;
		KeyBoolMap currentlyPressed;
		KeyBoolMap previousFramePressed;
		const std::array<KeyCode, 41> keyCodes = {
		KeyCode::A,
		KeyCode::B,
		KeyCode::C,
		KeyCode::D,
		KeyCode::E,
		KeyCode::F,
		KeyCode::G,
		KeyCode::H,
		KeyCode::I,
		KeyCode::J,
		KeyCode::K,
		KeyCode::L,
		KeyCode::M,
		KeyCode::N,
		KeyCode::O,
		KeyCode::P,
		KeyCode::Q,
		KeyCode::R,
		KeyCode::S,
		KeyCode::T,
		KeyCode::U,
		KeyCode::V,
		KeyCode::W,
		KeyCode::X,
		KeyCode::Y,
		KeyCode::Z,
		KeyCode::UpArrow,
		KeyCode::DownArrow,
		KeyCode::LeftArrow,
		KeyCode::RightArrow,
		KeyCode::Num0,
		KeyCode::Num1,
		KeyCode::Num2,
		KeyCode::Num3,
		KeyCode::Num4,
		KeyCode::Num5,
		KeyCode::Num6,
		KeyCode::Num7,
		KeyCode::Num8,
		KeyCode::Num9,
		KeyCode::Enter
		};
	};
}