#pragma once

//Included dependencies
#include <deque>
#include <SFML\System.hpp> /* sf::Vector2 */

//Forward declared dependencies
	//None

//The class

template<class T> class PositionTracker {
public:
	PositionTracker(sf::Vector2<T> startPos = sf::Vector2<T>(0, 0), bool limited = false, int limit = ALWAYS_KEEP_COUNT);
	virtual ~PositionTracker();

	void addPos(sf::Vector2<T> pos);	//Inserts a new position.
	void addPos(T x, T y);

	bool clearAmount(int am);			//Returns success. Clears elements from last onwards. Is "Safe", see below.
	void clearAll();					//Unsafe, avoid using unless you know what you are doing.
	void safeClearAll();				//Keeps the first two, necessary for derivate-definition movement, thus "Safe".

	inline sf::Vector2<T> getCurrentPos()	const {	return (this->at(0));	}		//Returns the latest inserted position with addPos(...)
	inline sf::Vector2<T> getLastPos()		const {	return (this->at(1));	}		//Returns the one that came before that
	inline sf::Vector2<T> operator[](int i)	const {	return (this->at(i));	}		//Used to retrieve position [n]. [0] is the last inserted position, and it goes onwards from there.
	inline sf::Vector2<T> at(int i)			const {	return this->queue_.at(i);	}	//Same as the operator overload above, just a more standard method call. Useful for pointers.
	inline int getSize()					const {	return this->queue_.size();	}	//Returns the number of positions tracked

	void disableLimit();				//Prevents old elements from being deleted. Old elements will automatically be if limit is enabled.
	void enableLimit();					//Enables the limit. If no custom arguments are given to the constructor, a limit is disabled by default.
	void setLimit(int limit);			//If the number of elements is greater than the set limit upon addPos(...), the oldest element will be deleted. Also calls enableLimit().

	inline bool isLimited()	const {	return this->limited_;	}	//Check if limit is enforced. True if it is.
	inline int getLimit()	const {	return this->limit_;	}	//Returns the number of elements the tracker can currently hold as a maximum.
																	//Note: The limit still has a value even if it is disabled via disableLimit() or the default constructor. It is just not used.
protected:
	static const int ALWAYS_KEEP_COUNT = 2;

private:
	inline void push_front(sf::Vector2<T> pos);
	inline void pop_back();

	int limit_;
	bool limited_;

	std::deque<sf::Vector2<T>> queue_;
};

#include "PositionTracker.hpp"