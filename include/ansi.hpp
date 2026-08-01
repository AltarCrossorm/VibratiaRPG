#pragma once
/**
 * @file ansi.hpp
 * @date 2026/07/15
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include <string_view>
#include <string>

namespace ansi
{

	struct background {std::string_view content;};
	struct text {std::string_view content;};
	struct format {std::string_view content;};


	constexpr std::string_view INIT = "";
	constexpr std::string_view FULL_RESET = "[0m";
	namespace fmt
	{
		constexpr format RESET = { "0" };
		constexpr format BOLD = { "1" };
		constexpr format ITALIC = { "3" };
		constexpr format UNDERLINE = { "4" };
		constexpr format INVISIBLE = { "8" };
		constexpr format STROKED = { "9" };
		constexpr format RESET_BOLD = { "22" }; // Counters ITALIC and BOLD, but not UNDERLINE and STROKED
		constexpr format RESET_ITALIC = { "23" };
		constexpr format RESET_UNDERLINE = { "24" };
		constexpr format RESET_INVISIBLE = { "28" };
		constexpr format RESET_STROKE = { "29" };
	}
	

	namespace txtColor
	{
		constexpr text BLACK = { "30" };
		constexpr text CORAL = { "31" };
		constexpr text EMERALD = { "32" };
		constexpr text GOLD = { "33" };
		constexpr text CYAN = { "34" };
		constexpr text PINK = { "35" };
		constexpr text TURQUOISE = { "36" };
		constexpr text LIGHTGREY = { "37" };
		constexpr text GREY = { "90" };
		constexpr text RED = { "91" };
		constexpr text GREEN = { "92" };
		constexpr text YELLOW = { "93" };
		constexpr text BLUE = { "94" };
		constexpr text MAGENTA = { "95" };
		constexpr text TAN = { "96" };		
		constexpr text WHITE = { "97" };

		constexpr text txtTab[16] = {
			BLACK,
			CORAL,
			EMERALD,
			GOLD,
			CYAN,
			PINK,
			TURQUOISE,
			LIGHTGREY,
			GREY,
			RED,
			GREEN,
			YELLOW,
			BLUE,
			MAGENTA,
			TAN,
			WHITE
		};
	}

	namespace bgColor
	{
		constexpr background BLACK = { "40" };
		constexpr background CORAL = { "41" };
		constexpr background EMERALD = { "42" };
		constexpr background GOLD = { "43" };
		constexpr background CYAN = { "44" };
		constexpr background PINK = { "45" };
		constexpr background TURQUOISE = { "46" };
		constexpr background LIGHTGREY = { "47" };
		constexpr background GREY = { "100" };
		constexpr background RED = { "101" };
		constexpr background GREEN = { "102" };
		constexpr background YELLOW = { "103" };
		constexpr background BLUE = { "104" };
		constexpr background MAGENTA = { "105" };
		constexpr background TAN = { "106" };		
		constexpr background WHITE = { "107" };

		constexpr background bgTab[16] = {
			BLACK,
			CORAL,
			EMERALD,
			GOLD,
			CYAN,
			PINK,
			TURQUOISE,
			LIGHTGREY,
			GREY,
			RED,
			GREEN,
			YELLOW,
			BLUE,
			MAGENTA,
			TAN,
			WHITE
		};
	}

	inline std::string set(std::string text, ansi::text textColor, ansi::background bgColor, ansi::format format) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += format.content; res += ";";
		res += textColor.content; res += ";";
		res += bgColor.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

	inline std::string set(std::string text, ansi::background bgColor) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += bgColor.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

	inline std::string set(std::string text, ansi::text textColor) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += textColor.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

	inline std::string set(std::string text, ansi::format format) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += format.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

	inline std::string set(std::string text, ansi::text textColor, ansi::format format) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += format.content; res += ";";
		res += textColor.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

	inline std::string set(std::string text, ansi::text textColor, ansi::background bgColor) {
		std::string res = "";
		res += ansi::INIT; res += "[";
		res += textColor.content; res += ";";
		res += bgColor.content; res += "m";
		res += text;
		res += ansi::FULL_RESET;
		return res;
	}

}
