/*
 * hamming_code.h
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
 * hamming_code.h
 *
 *  Created on: Dec 26, 2010
 *      Author: Leo Osvald
 */

#ifndef HAMMING_CODE_H_
#define HAMMING_CODE_H_

#include <vector>

#include "base.h"
#include "binary_code.h"

namespace paritycoding {

class HammingCode : public BinaryCode {
	static bool isPowerOfTwo(int x) {
		return (x & -x) == x;
	}

public:
	HammingCode(BinaryCode binary_code) {
		int data_index = 0;
		for (int i = 0; i < binary_code.size(); ++i) {
			append(isPowerOfTwo(i+1) ? false
					: binary_code.isSet(data_index++));
		}
	}

	bool getDataBit(int index) {
		// TODO
		return false;
	}

	bool getParityBit(int index) {
		return isSet(1 << index);
	}

};

}

#endif /* HAMMING_CODE_H_ */
