#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <type_traits>
#include <ctime>

std::string reflect(std::string a) {
	std::string toSearch = std::string(a) + "{";
	toSearch.erase(remove(toSearch.begin(), toSearch.end(), ' '), toSearch.end());

	std::string result;

	std::fstream file;
	file >> std::noskipws;
	file.open(__FILE__, std::ios::in);

	char ch;
	int counter = 0;
	bool found = false;
	bool add = true;

	do {
		file >> ch;
		if (!found) {
			if (ch == ' ' || ch == '\t') continue;
			else if (toSearch[counter] == ch) ++counter;
			else counter = 0;

			if (counter == toSearch.size()) {
				found = true;
			}
		}
		else {
			if (add && ch == ' ') add = false;
			else if (!add && ch == ';') add = true;
			else if (ch == '\t') continue;
			else if (ch == '}') break;
			else if (add) result += ch;
		}

	} while (!file.eof());

	return result;
}

template<class FirstType, class SecondType>
SecondType copycat(void* firstValue){
	if (reflect(typeid(FirstType).name()) == reflect(typeid(SecondType).name())) {
		return *reinterpret_cast<SecondType*>(reinterpret_cast<FirstType*>(firstValue));
	}
	else assert(false && "Structs are not the same");
}

struct AM {
	int a;
	int b;
	int c;
};

struct PM {
	int x;
	int y;
	int z;
};

int main() {
	AM a;
	PM b;
	a.a = 1;
	a.b = 3;
	a.c = 4;
	b.x = 0;
	b.y = 0;
	b.z = 0;

	b = copycat<AM, PM>(&a);
	std::cout << a.a << '\n';
	std::cout << a.b << '\n';
	std::cout << a.c << '\n';
	std::cout << b.x << '\n';
	std::cout << b.y << '\n';
	std::cout << b.z << '\n';
}


                                              
