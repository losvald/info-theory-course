/*
 * huffman_tree.h
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
 * huffman_tree.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <set>

#include "foreach.h"
#include "binary_code.h"

namespace entropycoding {

class HuffmanTree {

public:
	class Node;
private:
	struct Comparator;
	Node* root_;

	void destroy(const Node *node) {
		if (node == NULL)
			return ;
		if (node->left_child() != NULL)
			destroy(node->left_child());
		if (node->right_child() != NULL)
			destroy(node->right_child());
		delete node;
	}

public:

	static Node* extractMin(std::multiset<Node*, Comparator>& min_queue) {
		std::multiset<Node*, Comparator>::iterator it = min_queue.begin();
		Node* ret = *it;
		min_queue.erase(it);
		return ret;
	}

	HuffmanTree(const SymbolMap& symbol_frequencies) {
		using namespace std;

		multiset<Node*, Comparator> min_queue;
		FOREACH (it, symbol_frequencies) {
			min_queue.insert(new Node(it->first, it->second));
		}

		root_ = NULL;
		while ((int)min_queue.size() > 1) {
			Node* min1 = extractMin(min_queue);
			printf("Min1: (%lf %c)\n", min1->probability(), min1->symbol());
			Node* min2 = extractMin(min_queue);
			printf("Min2: (%lf %c)\n", min2->probability(), min2->symbol());
			root_ = new Node(min1, min2);
			printf("New: (%lf %c)\n", root_->probability(), root_->symbol());
			min_queue.insert(root_);
		}
		min_queue.clear();

		printInorder(root());
	}

	const Node* root() const {
		return root_;
	}

	virtual ~HuffmanTree() {
		destroy(root_);
	}

	class Node {
		const Node* children_[2];
		const char symbol_;
		const double frequency_;

	public:

		Node(char symbol, double frequency)
		: symbol_(symbol), frequency_(frequency) {
			children_[0] = children_[1] = NULL;
		}

		Node(const Node* child1, const Node* child2)
		: symbol_(0), frequency_(child1->frequency_ + child2->frequency_) {
			children_[0] = child1;
			children_[1] = child2;
		}

		char symbol() const {
			return symbol_;
		}

		double probability() const {
			return frequency_;
		}

		const Node* left_child() const {
			return children_[0];
		}

		const Node* right_child() const {
			return children_[1];
		}

		const Node* child(bool right) const {
			return children_[right];
		}

		bool isLeaf() const {
			return left_child() == NULL && right_child() == NULL;
		}

		friend bool operator==(const Node& a, const Node& b) {
			return a.frequency_ == b.frequency_ && a.symbol_ == b.symbol_;
		}

		friend bool operator<(const Node& a, const Node& b) {
			if (a.frequency_ != b.frequency_)
				return a.frequency_ < b.frequency_;
			return a.symbol_ < b.symbol_;
		}

		friend class Comparator;
	};

	void printInorder(const Node* node) {
		if (node == NULL)
			return ;
		printNode(node);
		if (!node->isLeaf()) {
			printf("( ");
			printInorder(node->left_child());
			printf(" ");
			printInorder(node->right_child());
			printf(" )");
		}
	}

	void printNode(const Node* node) {
		if (!node->isLeaf())
			printf("%.2lf", node->probability());
		else printf("%c", node->symbol());
	}

private:

	struct Comparator {
			bool operator()(const Node* a, const Node* b) {
				if (a->frequency_ != b->frequency_)
					return a->frequency_ < b->frequency_;
				return a->symbol_ < b->symbol_;
			}
		};

};

}

#endif /* HUFFMAN_TREE_H_ */
