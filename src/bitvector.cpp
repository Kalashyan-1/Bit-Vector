#include "bitvector.h"

BitVector::BitVector(int bitsize)
	:m_bitSize {bitsize}, m_arr {nullptr} 
{
	if (m_bitSize > 0) {
		int size = m_bitSize / sizeof(int);
		if (m_bitSize % sizeof(int)) {
			++size;
		}
		m_arr = new int[size]{};

	}
}

BitVector::~BitVector() 
{
	if (m_arr) {
		delete [] m_arr;
	}
}


BitVector::BitVector(const BitVector& bitvec) 
{

	int size = sizeof(m_arr) / sizeof(m_arr[0]);
	this->m_arr = new int[size]{};
	this->m_bitSize = bitvec.m_bitSize;
	for (int i = 0; i < size; ++i) {
		this->m_arr[i] = bitvec.m_arr[i];
	}

}
BitVector::BitVector(BitVector&& bitvec) 
{	
	int size = sizeof(m_arr) / sizeof(m_arr[0]);
	this->m_arr = new int[size]{};
	this->m_bitSize = bitvec.m_bitSize;
	this->m_arr = bitvec.m_arr;
	bitvec.m_arr = nullptr;
}

void BitVector::set(int index) 
{
	try {
	if (index < 0 || index >= m_bitSize) {
		throw std::invalid_argument("Invalid argument for set");
	}
	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	int elem = index / sizeof(int);
	int k;
	if (index < sizeof(int)) {
		k = index;
	} else {
		k = (index - elem * sizeof(int)) + elem;
	}
	int set = 1;
	m_arr[elem] |= set << k; 
}


void BitVector::reset(int index)
{
	try {
	if (index < 0 || index >= m_bitSize) {
		throw std::invalid_argument("Invalid argument for reset");
	}
	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	
	int elem = index / sizeof(int);
	int k;
	if (index < sizeof(int)) {
		k = index;
	} else {
		k = (index - elem * sizeof(int)) + elem;
	}
	unsigned int reset = -1;
	int set = 1;
	set <<= k;
	reset ^= set;
	m_arr[elem] &= reset;
}

std::ostream& operator<<(std::ostream& stream, const BitVector& bitvec) {
	if (bitvec.m_arr) {
	int k = 0;
    int b = sizeof(int) * 8;
//	k <<= sizeof(int) * 8 - 1;
	int tmp = bitvec.m_arr[k];
	for (int i = 0; i < bitvec.m_bitSize; ++i) {
		if ((i >= sizeof(int) * 8) && (b == 0)) {
			tmp = bitvec.m_arr[++k];
			b = sizeof(int) * 8;
		}
		stream << (tmp & 1);
		tmp >>= 1; 
		--b;
	}
	} else {
		stream << "";
	}
	return stream;
}

BitVector& BitVector::operator=(const BitVector& bitvec) {
	if (this == &bitvec) {
		return *this;
	}
	if (this->m_arr) {
		delete [] m_arr;
	}
	int size = sizeof(m_arr) / sizeof(m_arr[0]);
	this->m_arr = new int[size]{};
	this->m_bitSize = bitvec.m_bitSize;
	for (int i = 0; i < size; ++i) {
		this->m_arr[i] = bitvec.m_arr[i];
	}
	return *this;
}

BitVector& BitVector::operator=(BitVector&& bitvec) 
{
	if (this->m_arr) {
		delete [] m_arr;
	}
	this->m_bitSize = bitvec.m_bitSize;
	this->m_arr = bitvec.m_arr;
	bitvec.m_arr = nullptr;
	return *this;
}




