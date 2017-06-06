// Compile: g++ -oargs args.example.cc -std=c++11
// Useage:  ./args -ab --intval 123 --type vb foo bar

#include "args.h"

#include <iostream>
#include <vector>
#include <string>

enum SomeEnum { A, B, C, NONE };
struct Conf {
	bool boolval1, boolval2;
	int intval;
	SomeEnum enumval;
	std::vector<std::string> strs;

	inline Conf(int argc, char **argv) : boolval1(false), boolval2(false), intval(-1), enumval(NONE)
	{
// 		using namespace std::string_literals;
		args::parser args(argc, argv, "A short description"/*, std::cout*/);
		const int ARG_IN  = args.add_nonopt("INPUT"); args.range(1); // range(MIN, MAX): MIN and MAX are the minimun and maximum number of non-optional arguments
		const int ARG_BV1 = args.add_opt('a', "boolval1",  "Set bool value 1");
		const int ARG_BV2 = args.add_opt('b', "boolval2",  "Set bool value 2");
		const int ARG_IV  = args.add_opt(     "intval",    "Set integer value");
		const int ARG_EV  = args.add_opt(     "type",      "Set enum value (va|vb|vc)");

		for (int arg = args.next(); arg != args::parser::end; arg = args.next()) {
			// NOTE: switch/case won't work here
			if      (arg == ARG_BV1) boolval1  = true;
			else if (arg == ARG_BV2) boolval2  = true;
			else if (arg == ARG_IV)  intval    = args.val<int>();
			else if (arg == ARG_EV)  enumval   = args.map(std::string("va"), A, std::string("vb"), B, std::string("vc"), C); // use s literal here if you have c++14 support
			else if (arg == ARG_IN)  strs.push_back(args.val<std::string>());
		}
	}
};

int main(int argc, char **argv)
{
	Conf conf(argc, argv);

	std::cout << "Bool value 1:  " << conf.boolval1 << std::endl;
	std::cout << "Bool value 2:  " << conf.boolval2 << std::endl;
	std::cout << "Int value:     " << conf.intval << std::endl;
	std::cout << "Enum value:    " << (conf.enumval == A ? "A" : conf.enumval == B ? "B" : conf.enumval == C ? "C" : "NONE") << std::endl;
	std::cout << "String values:";
	for (const std::string &val : conf.strs) {
		std::cout << " " << val;
	}
	std::cout << std::endl;
}
