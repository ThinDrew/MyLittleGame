#include <iostream>
#include <string>
#include <cstdlib>

bool chance(int value) {
	int check = rand() % 1000;
	if (check > value) return false;
	else return true;
}