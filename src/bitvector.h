#include <iostream>
#include <stdexcept>

class BitVector {

public:
	explicit BitVector(int size);
	BitVector():m_arr {nullptr}, m_bitSize {0}{}
	BitVector(const BitVector& bitvec); 
	BitVector(BitVector&& bitvec);
	~BitVector();

	void set(int index);
	void reset(int index);
	friend std::ostream& operator<<(std::ostream& stream, const BitVector& bitvec);
	BitVector& operator=(const BitVector& bitvec);
	BitVector& operator=(BitVector&& bitvec); 
private:
	int* m_arr;
	int m_bitSize;
};
