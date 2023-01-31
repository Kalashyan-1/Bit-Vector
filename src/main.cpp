#include "bitvector.h"


int main() {
	BitVector b(27);
	b.set(2);
	b.set(3);
	b.set(1);
	std::cout << b << "\n";
	b.reset(3);
	std::cout << b << "\n";
	BitVector b1(b);
	b1.reset(1);
	BitVector b2;
	b2 = b1;
	std::cout << b2 << "\n";	
}
