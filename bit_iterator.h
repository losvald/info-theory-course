/*
 * bit_iterator.h
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
 * bit_iterator.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef BIT_ITERATOR_H_
#define BIT_ITERATOR_H_

#include <cstdio>

#include "base.h"

class BitIterator {
public:
	virtual bool hasNextBit() = 0;
	virtual bool nextBit() = 0;
};

class FileBitIterator : public BitIterator {
	FILE* file_;
	bool look_ahead_;
	bool has_next_;
	bool next_bit_;
public:
	FileBitIterator(FILE* file) : file_(file), look_ahead_(false) { }
	bool hasNextBit() {
		if (!look_ahead_) {
			look_ahead_ = true;
			return has_next_ = readBit(file_, next_bit_);
		}
		return has_next_;
	}
	bool nextBit() {
		if (look_ahead_) {
			look_ahead_ = false;
			return next_bit_;
		}
		bool ret;
		if (!readBit(file_, ret))
			throw std::exception();
		return ret;
	}
	virtual bool readBit(FILE* file, bool& read_bit) {
		char c = getc(file);
		if (c == EOF || isEndline(c)) {
			read_bit = false;
			return false;
		}
		read_bit = toBit(c);
		return true;
	}
};

#endif /* BIT_ITERATOR_H_ */
