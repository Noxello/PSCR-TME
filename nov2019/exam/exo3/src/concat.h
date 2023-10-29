#pragma once

#include <vector>
#include <string>

namespace pr {

class concat {
	// TODO : attributs stockant ref ou pointeurs vers les constituants v1,v2
	std::vector<std::string> & v1;
	std::vector<std::string> & v2;
public:
	concat(std::vector<std::string> & v1, std::vector<std::string> & v2): v1(v1), v2(v2) {}

	class iterator {
		std::vector<std::string> & v1;
		std::vector<std::string> & v2;
		std::vector<std::string>::iterator i;
	public:
		// TODO : signature du constructeur
		iterator(std::vector<std::string> & v1, std::vector<std::string> & v2): v1(v1), v2(v2), i(v1.begin()) {}
		iterator(std::vector<std::string> & v1, std::vector<std::string> & v2, std::vector<std::string>::iterator i):
			v1(v1), v2(v2), i(i) {}
		// TODO : contrat itérateur

		std::string & operator*(){
			return *i;
		}
		iterator & operator++(){
			i++;
			if(i == v1.end())
				i = v2.begin();
			return *this;

		};
		bool operator!=(const iterator & other) const{
			return this->i != other.i;
		}
	};

	iterator begin(){
		auto res = iterator(v1,v2);
		return res;
	}
	iterator end(){
		auto res = iterator(v1,v2, v2.end());
		return res;
	}
};

}
