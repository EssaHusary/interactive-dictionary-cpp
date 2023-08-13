

#pragma once

#ifndef DataSource_hpp
#define DataSource_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

namespace Source {
	class DataSource {

	public:
		int numberOfDefinitions;
		map<string, vector<vector<string>>> addWordsToDatabase();
		

	};
}



#endif
