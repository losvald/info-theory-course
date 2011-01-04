/*
 * channel.h
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
 * channel.h
 *
 *  Created on: Dec 25, 2010
 *      Author: Leo Osvald
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <cstdlib>

#include "../base.h"
#include "../bit_iterator.h"
#include "channel_properties.h"

namespace channel {

class Channel {
	FILE* out_;
	FILE* in_;
	FILE* error_vector_in_;
public:
	Channel(FILE* out, FILE* in, FILE* error_vector_in)
	: out_(out), in_(in), error_vector_in_(error_vector_in) {
	}

	void scramble() {
		FileBitIterator in_it(in_);
		FileBitIterator error_vec_it(error_vector_in_);
		while (in_it.hasNextBit()) {
			bool bit = in_it.nextBit();
			if (error_vector_in_ == NULL)
				scrambleBit(bit);
			else if (error_vec_it.hasNextBit())
				bit ^= error_vec_it.nextBit();
			fprintf(out_, "%c", fromBit(bit));
		}
	}

	void scrambleBit(bool& bit) {
		if ((double)rand() / RAND_MAX < errorProbability)
			bit ^= true;
	}

};

}

#endif /* CHANNEL_H_ */
