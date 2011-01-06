/*
 * huffman_coder.h
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
 * huffman_coder.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef HUFFMAN_CODER_H_
#define HUFFMAN_CODER_H_

#include <cstddef>

#include "../../binary_code.h"
#include "../huffman_tree.h"

namespace entropycoding {

class HuffmanCoder {

	class Map {
		BinaryCode arr_[0x80];
	public:
		void put(const char symbol, const BinaryCode& bc) {
			arr_[(int)symbol] = bc;
		}

		const BinaryCode& at(const char symbol) const {
			return arr_[(int)symbol];
		}
	} inverse_map_;

	typedef HuffmanTree::Node Node;

public:

	HuffmanCoder(const ProbabilityMap& symbol_probabilities) {
		HuffmanTree tree(symbol_probabilities);
		if (tree.root() != NULL) {
			BinaryCode prefix;
			traverseAndMap(tree.root(), prefix);
		}
	}

	const BinaryCode& code(char c) const {
		return inverse_map_.at(c);
	}

private:
	void traverseAndMap(const Node* node, BinaryCode& prefix) {
		if (node->isLeaf()) {
			fprintf(stderr, "Huffman(%c) = %s\n", node->symbol(),
					prefix.toString().c_str());
			inverse_map_.put(node->symbol(), prefix);
			return ;
		}
		bool bit = false;
		do {
			const Node* child = node->child(bit);
			if (child != NULL) {
				prefix.append(bit);
				traverseAndMap(child, prefix);
				prefix.pop();
			}
			bit ^= true;
		} while (bit);
	}

};

}

#endif /* HUFFMAN_CODER_H_ */
