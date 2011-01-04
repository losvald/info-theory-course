/*
 * channel_coder.h
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
 * channel_coder.h
 *
 *  Created on: Dec 26, 2010
 *      Author: Leo Osvald
 */

#ifndef CHANNEL_CODER_H_
#define CHANNEL_CODER_H_

#include "../base.h"
#include "../bit_iterator.h"
#include "../binary_code.h"
#include "../hamming_code.h"

namespace paritycoding {

class ChannelCoder {
	FILE* in_;
	FILE* out_;
	const int n_;
	const int k_;
	BinaryCode buffer_;
public:
	ChannelCoder(FILE* out, FILE* in, int n, int k)
	: in_(in), out_(out), n_(n), k_(k) {
	}

	void codeAll() {
		BinaryCode bc;
		FileBitIterator it(in_);
		for (; it.hasNextBit(); ) {
			int k;
			for (k = 0; k < k_ && it.hasNextBit(); ++k) {
				bc.append(it.nextBit());
			}
			// ako nije djeljivo nadopuni nulama
			for (; k < k_; ++k)
				bc.append(false);

			// kodiraj
			HammingCode hammingCode(bc);
			fprintf(out_, "%s", hammingCode.toString().c_str());
		}
	}

private:
	void code(BinaryCode bc) {

	}

};

}

#endif /* CHANNEL_CODER_H_ */
