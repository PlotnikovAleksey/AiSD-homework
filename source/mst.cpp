﻿#include <iostream>
#include <mst.hpp>


int main() {
	matrix a = { {0,7,100,5,100,100,100}, {7,0,8,9,7,100,100}, {100,8,0,100,5,100,100}, {5,9,100,0,15,6,100}, {100,7,5,15,0,8,9}, {100,100,100,6,8,0,11}, {110,117,100,100,9,11,0} };
	Graph g;
	g.set(a);
	g.find_mst();
	return 0;
}
