/* General purposes */
#include <iostream>
#include <vector>

/* Reading files */
#include <fstream>
#include <sstream>

/* Building graphs */
#include <map>
#include <unordered_map>
#include <list>

/* Search */
#include <queue>
#include <stack>

using namespace std;
template <typename T, typename Y>
using Graph = map<T, list<Y>>;