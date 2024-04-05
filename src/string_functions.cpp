#include "deps.h"
#include "string_functions.h"
#include <sstream>
#include <fstream>

Path& Path::operator>>(std::string child) {
	this->childs.push_back(child);
	return *this;
}

std::string Path::Get() {
	std::string temp;
	for (auto it : this->childs) {
		temp.append(it);
		temp.append(PATH_SEP);
	}
	temp.resize(temp.size() - sizeof(PATH_SEP) + 1);
	return temp;
}

std::string Path::GetData(std::string p) {
	std::ifstream t(p);
	std::stringstream sbuffer;
	sbuffer << t.rdbuf();
	return sbuffer.str();
}