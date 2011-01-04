/*
 * source_coder.h
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
 * source_coder.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef SOURCE_CODER_H_
#define SOURCE_CODER_H_

#include <cstdio>

#include "../base.h"
#include "huffman_coder.h"

namespace entropycoding {

class SourceCoder {

	FILE* in_;
	FILE* out_;
	HuffmanCoder coder_;

public:
	SourceCoder(FILE* out, FILE* in, SymbolMap symbol_map)
	: in_(in), out_(out), coder_(symbol_map) {

	}

	/**
	 * Kodira sve znakove (tj. najvise 0x7FFFFFFF njih), te vraca broj
	 * kodiranih znakova.
	 */
	int codeAll() const {
		return code(0x7FFFFFFF);
	}

	/**
	 * Kodira najvise n znakova, te vraca broj kodiranih znakova.
	 */
	int code(int n) const {
		for (int i = 0; i < n; ++i) {
			char c;
			if (fscanf(in_, "%c", &c) != 1 || isEndline(c))
				return i;
			fprintf(out_, "%s", coder_.code(c).toString().c_str());
		}
		return 0;
	}

};

}

#endif /* SOURCE_CODER_H_ */
