#ifndef SRC_BOUNDEDBUFFER_H_
#define SRC_BOUNDEDBUFFER_H_

#include <array>
#include <algorithm>
#include <stdexcept>

template <typename T, std::size_t S>
struct BoundedBuffer {
	using BASE = std::array<T,S>;
	using value_type = T;
	using reference = value_type&;
	using const_reference = value_type const &;
	using container_type = BASE;
	using size_type = typename BASE::size_type;

	bool empty() const {
		return !counter;
	}

	bool full() const {
		if (resource.size() == 0) return true;
		return counter == resource.size();
	}

	T const & front() const {
		if (empty()) throw std::logic_error("BoundedBuffer is empty");
		return resource[frontIndex];
	}

	T& front() {
		if (empty()) throw std::logic_error("BoundedBuffer is empty");
		return resource[frontIndex];
	}

	T& back() {
		if (empty()) throw std::logic_error("BoundedBuffer is empty");
		return resource[ (frontIndex+(counter-1)) % resource.size()];
	}

	T const & back() const {
		if (empty()) throw std::logic_error("BoundedBuffer is empty");
		return resource[ (frontIndex+(counter-1)) % resource.size()];
	}

	void pop() {
		if (empty()) throw std::logic_error("BoundedBuffer is empty");
		resource[frontIndex] = T{};
		frontIndex = ++frontIndex % resource.size();
		counter--;
	}

	size_type size() const {
		return counter;
	}

	void push(T const & lvalue) {
		if (full()) throw std::logic_error("BoundedBuffer is full");
		resource[(frontIndex + counter++) % resource.size()] = lvalue;
	}

	void push(T const && rvalue) {
		if (full()) throw std::logic_error("BoundedBuffer is full");
		resource[(frontIndex + counter++) % resource.size()] = rvalue;
	}

	void swap(BoundedBuffer & other) {
//		if (other.empty()) return;
		std::swap_ranges(resource.begin(), resource.end(), other.resource.begin());
	}
private:
	std::array<T,S> resource{};
	int frontIndex{0}, counter{0};
};


#endif /* SRC_BOUNDEDBUFFER_H_ */
