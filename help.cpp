#include <iostream>
#include <string>
#include <cstdlib>

bool chance(int value) {
	int check = rand() % 1000;
	if (check > value) return false;
	else return true;
}

int random(int a, int b) {
	return (rand() % (b - a + 1)) + a;
}