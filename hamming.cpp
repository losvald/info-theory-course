/*
 * hamming.cpp
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
 * hamming.cpp
 *
 *  Created on: Nov 16, 2010
 *      Author: Leo Osvald
 */

#include <cstdio>
#include <vector>
#include <iostream>

class BinaryCode {
private:
	std::vector<bool> bits_;
	int size_;
public:
	BinaryCode() : bits_(4), size_(0) { }

	virtual bool get(int index) {
		return bits_[index];
	}

	virtual int set(bool val, int index) {
		while (bits_.size() <= index)
			bits_.resize(2 * bits_.size());
		if (index >= size_)
			size_ = index + 1;
		bits_[index] = val;
	}
	virtual int size() {
		return size_;
	}

	friend std::ostream& operator<<(std::ostream& os,
			BinaryCode bc) {
		for (int i = 0; i < bc.size(); ++i) {
			os << (bc.get(i) ? 1 : 0);
		}
		return os;
	}
};

class HuffmanCode : public BinaryCode {
private:
	typedef BinaryCode super;
	std::vector<bool> parity_bits_;
public:
	int size() {
		return super::size() + parity_bits_.size();
	}
};

//int main() {
//	using namespace std;
//	string s;
//	cin >> s;
//	BinaryCode bc;
//	for (int i = 0; i < (int) s.size(); ++i) {
//		bc.set(s[i]-'0', i);
//	}
//	cout << bc << endl;
//
//	return 0;
//}
