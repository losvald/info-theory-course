/*
 * huffman_decoder.h
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
 * huffman_decoder.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef HUFFMAN_DECODER_H_
#define HUFFMAN_DECODER_H_

#include "../base.h"
#include "../binary_code.h"
#include "../huffman_tree.h"

namespace entropycoding {

class HuffmanDecoder {

	const HuffmanTree tree_;
	typedef HuffmanTree::Node Node;

public:

	HuffmanDecoder(const SymbolMap& symbol_frequencies)
	: tree_(symbol_frequencies) {
	}

	char decode(const BinaryCode& bc, int& decoded_bit_count) const {
		const Node* node = tree_.root();
		decoded_bit_count = 0;
		for (int i = 0; i < bc.size(); ++i) {
			node = node->child(bc.isSet(i));
			++decoded_bit_count;
			if (node->isLeaf())
				return node->symbol();
		}
		decoded_bit_count = 0;
		return 0;
	}


	char decode(BitIterator& bit_iterator, int& decoded_bit_count) {
		const Node* node = tree_.root();
		decoded_bit_count = 0;
		while (bit_iterator.hasNextBit()) {
			node = node->child(bit_iterator.nextBit());
			++decoded_bit_count;
			if (node->isLeaf())
				return node->symbol();
		}
		decoded_bit_count = 0;
		return 0;

	}

};

}

#endif /* HUFFMAN_DECODER_H_ */
