#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std::literals::string_literals;

inline std::string printBar(unsigned int length, bool escape_flag = true)
{
	return "#"s + std::string(length - 2, '-') + "#"s + (escape_flag ? "\n"s : ""s);
}

static std::string printDescription(std::vector<std::string> descriptions, bool escape_flag = false)
{
	const std::string editor = "T.Kobayashi";
	const time_t now = std::time(nullptr);
	const tm* tm_now = localtime(&now);
	const std::string date = std::to_string(tm_now->tm_year + 1900) + "."s
		+ std::to_string(tm_now->tm_mon + 1) + "."s
		+ std::to_string(tm_now->tm_mday);

	std::string description_str = "";

//	descriptions.push_back(editor + " "s + date);

	for (std::string str : descriptions)
		if (str.length() < 80 - 3)
			description_str += "# "s + str + std::string(80 - 3 - str.length(), ' ') + "#\n";
		else
			description_str += "# "s + str + "\n";

	return printBar(80)
		+ description_str
		+ printBar(80, escape_flag);
}

static std::string printDescription(std::string const description, bool escape_flag = false)
{
	return printDescription({ description }, escape_flag);
}

static void replaceAll(std::string& str, std::string const find_word, std::string const replace_word)
{
	std::string::size_type pos = str.find(find_word);
	while (pos != std::string::npos) {
		str.replace(pos, find_word.length(), replace_word);
		pos = str.find(find_word, pos + find_word.length());
	}
}

static std::string printSingleArgumentNumericalFunction(std::string const& a_char, std::string const& suffix,
	std::string function_base_name = "")
{
	std::string str = R"(SANF(T) = exp(b0 + b1 * log(T)**1 + b2 * log(T)**2 \
 + b3 * log(T)**3 + b4 * log(T)**4 + b5 * log(T)**5 \
 + b6 * log(T)**6 + b7 * log(T)**7 + b8 * log(T)**8))"s;

	str.replace(str.find("SANF"), 4, [&]() {
		if (function_base_name == "")
			return "SANF"s + suffix;
		else
			return function_base_name + suffix;
	}());

	std::string::size_type pos = 0;
	while (true) {
		pos = str.find("b"s, pos + 2);
		if (pos == std::string::npos)
			break;
		str.insert(pos + 2, suffix);
		str.replace(pos, 1, a_char);
	}

	return str;
}

static std::string printDoubleArgumentNumericalFunction(std::string const& a_char, std::string const& suffix,
	std::string function_base_name = "")
{
	std::string str = R"(DANF(E, T) = exp((a00 * log(E)**0 + a01 * log(E)**1 + a02 * log(E)**2 \
 + a03 * log(E)**3 + a04 * log(E)**4 + a05 * log(E)**5 \
 + a06 * log(E)**6 + a07 * log(E)**7 + a08 * log(E)**8) * log(T)**0 \
 + (a10 * log(E)**0 + a11 * log(E)**1 + a12 * log(E)**2 \
 + a13 * log(E)**3 + a14 * log(E)**4 + a15 * log(E)**5 \
 + a16 * log(E)**6 + a17 * log(E)**7 + a18 * log(E)**8) * log(T)**1 \
 + (a20 * log(E)**0 + a21 * log(E)**1 + a22 * log(E)**2 \
 + a23 * log(E)**3 + a24 * log(E)**4 + a25 * log(E)**5 \
 + a26 * log(E)**6 + a27 * log(E)**7 + a28 * log(E)**8) * log(T)**2 \
 + (a30 * log(E)**0 + a31 * log(E)**1 + a32 * log(E)**2 \
 + a33 * log(E)**3 + a34 * log(E)**4 + a35 * log(E)**5 \
 + a36 * log(E)**6 + a37 * log(E)**7 + a38 * log(E)**8) * log(T)**3 \
 + (a40 * log(E)**0 + a41 * log(E)**1 + a42 * log(E)**2 \
 + a43 * log(E)**3 + a44 * log(E)**4 + a45 * log(E)**5 \
 + a46 * log(E)**6 + a47 * log(E)**7 + a48 * log(E)**8) * log(T)**4 \
 + (a50 * log(E)**0 + a51 * log(E)**1 + a52 * log(E)**2 \ 
 + a53 * log(E)**3 + a54 * log(E)**4 + a55 * log(E)**5 \
 + a56 * log(E)**6 + a57 * log(E)**7 + a58 * log(E)**8) * log(T)**5 \
 + (a60 * log(E)**0 + a61 * log(E)**1 + a62 * log(E)**2 \
 + a63 * log(E)**3 + a64 * log(E)**4 + a65 * log(E)**5 \
 + a66 * log(E)**6 + a67 * log(E)**7 + a68 * log(E)**8) * log(T)**6 \
 + (a70 * log(E)**0 + a71 * log(E)**1 + a72 * log(E)**2 \
 + a73 * log(E)**3 + a74 * log(E)**4 + a75 * log(E)**5 \
 + a76 * log(E)**6 + a77 * log(E)**7 + a78 * log(E)**8) * log(T)**7 \
 + (a80 * log(E)**0 + a81 * log(E)**1 + a82 * log(E)**2 \
 + a83 * log(E)**3 + a84 * log(E)**4 + a85 * log(E)**5 \
 + a86 * log(E)**6 + a87 * log(E)**7 + a88 * log(E)**8) * log(T)**8)
)"s;

	str.replace(str.find("DANF"), 4, [&]() {
		if (function_base_name == "")
			return "DANF"s + suffix;
		else
			return function_base_name + suffix;
	}());

	std::string::size_type pos = 0;
	while (true) {
		pos = str.find("a"s, pos + 3 + suffix.length());
		if (pos == std::string::npos)
			break;
		str.insert(pos + 3, suffix);
	}

	return str;
}

inline auto& loadNextLine(std::ifstream& ifs, std::string& line_buf, unsigned int& line)
{
	++line;
	return std::getline(ifs, line_buf);
}

int main(int argc, char* argv[])
{
	std::string note_string = "";
	std::string function_base_name = "";

	switch (argc) {
	case 1:
	default:
		std::cerr << "TK Janev Fitting Data Loader" << std::endl;
		std::cerr << "syntax: " << std::endl;
		std::cerr << "\targument1: tex source file" << std::endl;
		std::cerr << "\targument2: note string" << std::endl;
		std::cerr << "\targument3: function base name" << std::endl;
		return 0;
	case 4:
		function_base_name = std::string(argv[3]);
	case 3:
		note_string = std::string(argv[2]);
	case 2:
		;
	}

	std::ifstream ifs(static_cast<std::string>(argv[1]));
	std::string line_buf;

	//load lines
	unsigned int line = 1;
	unsigned int output_cnt = 1;
	for (; std::getline(ifs, line_buf); ++line) {
		static std::string current_reaction_str = "";

		auto description = [&]() -> std::vector<std::string> {
			return { current_reaction_str,
				"Function #"s + std::to_string(output_cnt),
				"source line: "s + std::to_string(line),
				note_string };
		};

		//Reaction Comment
		if (line_buf.find("Reaction ") != std::string::npos) {
			line_buf.replace(0, line_buf.find("Reaction "), "");
			std::string::size_type pos = line_buf.rfind("}");
			if (pos != std::string::npos)
				line_buf.replace(pos, 1, "");
			current_reaction_str = line_buf;
			continue;
		}

		//Double Argument Numerical Function
		if ((line_buf.find("E-Index") != std::string::npos || line_buf.find("E Index") != std::string::npos)
			&& (line_buf.find("0") != std::string::npos && line_buf.find("1") != std::string::npos
				&& line_buf.find("2") != std::string::npos)) {
			for (unsigned int k = 2; k; --k)
				loadNextLine(ifs, line_buf, line);

			const std::string suffix = "_"s + std::to_string(output_cnt);

			//exclude AMJUEL Reaction 3.1.8L
			if (line_buf.find("h0") == std::string::npos) {
				std::cout << std::endl;
				std::cout << printDescription(description()) << std::endl;
				for (unsigned int i = 0; i < 27; ++i) {
					line_buf.replace(0, line_buf.find(std::to_string(i % 9)) + 1, "");

					std::stringstream ss(line_buf);
					std::string var[3];
					ss >> var[0] >> var[1] >> var[2];
					line_buf.clear();
					for (unsigned int j = 0; j < 3; ++j)
						line_buf += "; b"s + std::to_string(i % 9) + std::to_string((i / 9) * 3 + j)
						+ suffix + " = "s + var[j];
					line_buf.replace(0, line_buf.find("b"s), "");
					replaceAll(line_buf, "D", "E");

					std::cout << line_buf << std::endl;
					for (unsigned int k = (i + 1) % 9 ? 1 : 4; k; --k)
						loadNextLine(ifs, line_buf, line);
				}
				std::cout << printDoubleArgumentNumericalFunction("b", suffix, function_base_name) << std::endl;
				++output_cnt;
			}
		}

		//Single Argument Numerical Function
		for (const std::string a_char : {"a", "b", "h"}) {
			if (line_buf.find(a_char + "0"s) == std::string::npos
				|| line_buf.find(a_char + "1"s) == std::string::npos
				|| line_buf.find(a_char + "2"s) == std::string::npos)
				continue;

			std::cout << std::endl;
			std::cout << printDescription(description()) << std::endl;
			const std::string suffix = "_"s + std::to_string(output_cnt);
			for (unsigned int i = 0; i < 3; ++i) {
				for (unsigned int j = 0; j < 3; ++j)
					line_buf.replace(line_buf.find(a_char + std::to_string(i * 3 + j)), 2,
						"; "s + a_char + std::to_string(i * 3 + j) + suffix + " ="s);
				line_buf.replace(0, line_buf.find(a_char + std::to_string(i * 3)), "");
				replaceAll(line_buf, "D", "E");

				std::cout << line_buf << std::endl;
				loadNextLine(ifs, line_buf, line);
			}
			std::cout << printSingleArgumentNumericalFunction(a_char, suffix, function_base_name) << std::endl;
			++output_cnt;
			break;
		}
	}

	if (output_cnt == 1) {
		std::cout << R"(This is the output "There is no output.")" << std::endl;
		std::cout << "note: "s << line << " lines were successfully read." << std::endl;
	}

	return 0;
}




