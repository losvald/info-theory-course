/*
 * base.h
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
 * base.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef BASE_H_
#define BASE_H_

#include <map>

typedef std::map<char, double> SymbolMap;

static bool toBit(char bit) {
	if (bit < '0' || bit > '1')
		throw std::exception();
	return bit - '0';
}

static char fromBit(bool bit) {
	return bit + '0';
}

static bool isEndline(char c) {
	return c == '\n' || c == '\r';
}

#endif /* BASE_H_ */
