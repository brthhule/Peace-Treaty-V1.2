#ifndef BUILDINGS_H
#define BUILDINGS_H

#include BUILDINGS_BASE_HEADER

class Buildings {
public:
	Farm farm;
	Infirmary infirmary;
	Library library;
	Residences residences;
	Wall wall;

	Church church;
	Farm farm;
	Mill mill;
	Mine mine;
	Quarry quarry;

	Buildings();


	/*
	struct Iterator {
		//Tags
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = BuildingsBASE;
		using pointer = BuildingsBASE*;  // or also value_type*
		using reference = BuildingsBASE&;  // or also value_type&

		//Constructor
		Iterator(pointer ptr) : m_ptr(ptr) {}

		//Operations
		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() { m_ptr++; return *this; }

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};

	Iterator begin() { return Iterator(&m_data[0]); }
	Iterator end() { return Iterator(&m_data[10]); } // 10 is out of bounds

	

	*/

	BuildingsBASE* at(int index) {
		return m_data.at(index);
	}

private:

	std::array <BuildingsBASE*, 10> m_data; 
};

#endif