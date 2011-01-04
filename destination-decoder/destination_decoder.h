/*
 * destination_decoder.h
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
 * destination_decoder.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef DESTINATION_DECODER_H_
#define DESTINATION_DECODER_H_

#include <cstdio>

#include "../bit_iterator.h"
#include "huffman_decoder.h"

namespace entropycoding {

class DestinationDecoder {

	FILE* in_;
	FILE* out_;
	HuffmanDecoder decoder_;

public:
	DestinationDecoder(FILE* out, FILE* in, SymbolMap symbol_map)
	: in_(in), out_(out), decoder_(symbol_map) {
	}

	int decodeAll() const {
		FileBitIterator it(in_);
		int ret = 0;
		while (it.hasNextBit()) {
			BinaryCode bc;
			for (int n = 1; ; n *= 2) {
				int k;
				for (k = 0; bc.size() < n && it.hasNextBit(); ++k)
					bc.append(it.nextBit());
				printf("Trying: %s\n", bc.toString().c_str());
				int decoded_bit_count;
				char decoded = decoder_.decode(bc, decoded_bit_count);
				ret += decoded_bit_count;
				if (decoded_bit_count > 0) {
					printf("Success");
					fscanf(out_, "%c", decoded);
					bc = bc.suffix(decoded_bit_count);
					break;
				}
				if (k == 0)
					break;
			}
		}
		return ret;
	}

};

}


#endif /* DESTINATION_DECODER_H_ */
