/*
 * binary_code.h
 * 
 * Copyright (C) 2010-2011 Leo Osvald <leo.osvald@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License.
 *  
 * You may obtain a copy of the License at 
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *  
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License. 
 */
/*
 * binary_code.h
 *
 *  Created on: Dec 26, 2010
 *      Author: Leo Osvald
 */

#ifndef BINARY_CODE
#define BINARY_CODE

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "base.h"
#include "bit_iterator.h"

class BinaryCode {
	std::vector<bool> v_;

	BinaryCode(int length) {
		v_.resize(length);
	}

public:

	BinaryCode() {
	}

	BinaryCode(const BinaryCode& clone) {
		v_ = clone.v_;
	}

	BinaryCode(const std::string& s) {
		for (int i = 0; i < (int)s.size(); ++i)
			v_.push_back(toBit(s[i]));
	}

	bool isSet(int pos) const {
		return v_[pos];
	}

	int empty() const {
		return v_.empty();
	}

	int size() const {
		return v_.size();
	}

	bool flip(int pos) {
		return v_[pos] = !v_[pos];
	}

	bool set(int pos, bool val) {
		bool prev = v_[pos];
		v_[pos] = val;
		return prev;
	}

	BinaryCode* append(const BinaryCode& bc) {
		v_.reserve(v_.size() + bc.size());
		for (int i = 0; i < (int) bc.size(); ++i) {
			v_.push_back(bc.isSet(i));
		}
		return this;
	}

	BinaryCode* append(bool bit) {
		v_.push_back(bit);
		return this;
	}

	BinaryCode* append(char bit) {
		v_.push_back(toBit(bit));
		return this;
	}

	BinaryCode* pop() {
		if (v_.empty())
			throw new std::exception();
		v_.pop_back();
		return this;
	}

	BinaryCode suffix(int fromIndex) const {
		BinaryCode ret;
		ret.v_.reserve(size() - fromIndex + 1);
		for (int i = fromIndex; i < size(); ++i)
			ret.v_.push_back(v_[i]);
		return ret;
	}

	std::string toString() {
		std::string s;
		s.reserve(v_.size());
		for (int i = 0; i < (int) v_.size(); ++i)
			s.push_back('0' + v_[i]);
		return s;
	}

	friend BinaryCode operator|(const BinaryCode& a, const BinaryCode& b) {
		int min_size = std::min(a.size(), b.size());
		int max_size = std::max(a.size(), b.size());
		BinaryCode ret(max_size);

		std::transform(a.v_.begin(), a.v_.begin() + min_size,
				b.v_.begin(),
				ret.v_.begin(),
				std::logical_or<bool>());

		if (a.size() >= b.size()) {
			for (int i = min_size; i < max_size; ++i)
				ret.v_[i] = a.v_[i];
		} else {
			for (int i = min_size; i < max_size; ++i)
				ret.v_[i] = b.v_[i];
		}

		return ret;
	}

	friend BinaryCode operator&(const BinaryCode& a, const BinaryCode& b) {
		int min_size = std::min(a.size(), b.size());
		int max_size = std::max(a.size(), b.size());
		BinaryCode ret(max_size);

		std::transform(a.v_.begin(), a.v_.begin() + min_size,
				b.v_.begin(),
				ret.v_.begin(),
				std::logical_and<bool>());

		for (int i = min_size; i < max_size; ++i)
			ret.v_[i] = false;

		return ret;
	}

	friend BinaryCode operator^(const BinaryCode& a, const BinaryCode& b) {
		int min_size = std::min(a.size(), b.size());
		int max_size = std::max(a.size(), b.size());
		BinaryCode ret(max_size);

		for (int i = 0; i < min_size; ++i)
			ret.v_[i] = a.v_[i] ^ b.v_[i];

		if (a.size() >= b.size()) {
			for (int i = min_size; i < max_size; ++i)
				ret.v_[i] = a.v_[i];
		} else {
			for (int i = min_size; i < max_size; ++i)
				ret.v_[i] = b.v_[i];
		}

		return ret;
	}

	friend bool operator==(const BinaryCode& a, const BinaryCode& b) {
		return a.v_ == b.v_;
	}

	friend bool operator<(const BinaryCode& a, const BinaryCode& b) {
		return a.v_ < b.v_;
	}

	friend std::ostream& operator<<(std::ostream& os, const BinaryCode& bc) {
		for (int i = 0; i < (int) bc.v_.size(); ++i)
			os << (bc.v_[i] ? '1' : '0');
		return os;
	}

};

class BinaryCodeIterator : public BitIterator {
	BinaryCode bc_;
	int index;
public:
	BinaryCodeIterator(const BinaryCode bc) : bc_(bc) { }
	bool hasNextBit() {
		return index < bc_.size();
	}
	bool nextBit() {
		return bc_.isSet(index++);
	}
};

// class InvalidBinaryException : public std::exception {
// }

#endif
