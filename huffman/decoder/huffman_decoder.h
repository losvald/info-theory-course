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

#include "../../base.h"
#include "../../binary_code.h"
#include "../../bit_iterator.h"
#include "../huffman_tree.h"

namespace entropycoding {

class HuffmanDecoder {

	const HuffmanTree tree_;
	typedef HuffmanTree::Node Node;

public:

	HuffmanDecoder(const ProbabilityMap& symbol_probabilities)
	: tree_(symbol_probabilities) {
	}

	/**
	 * Iterira bit po bit dok god ne uspije dekodirati niz znakova.
	 * Ako je dekodiranje uspjesno vraca znak razlicit od '\0' (0).
	 * a u decoded_bits se nalaze dekodirani bitovi.
	 * U slucaju da niz nije moguce dekodirati na temelju procitanih znakova,
	 * u decoded_bits ce biti procitani znakovi.
	 */
	char decode(BitIterator& bit_iterator, BinaryCode& decoded_bits) const {
		const Node* node = tree_.root();
		decoded_bits.clear();
		while (bit_iterator.hasNextBit()) {
			bool b = bit_iterator.nextBit();
			decoded_bits.append(b);
			node = node->child(b);
			if (node->isLeaf())
				return node->symbol();
		}
		return 0;
	}

};

}

#endif /* HUFFMAN_DECODER_H_ */
