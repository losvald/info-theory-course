/*
 * symbol_source.h
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
 * symbol_source.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef SYMBOL_SOURCE_H_
#define SYMBOL_SOURCE_H_

#include <cstdio>

#include "../base.h"
#include "symbol_generator.h"

namespace source {

class SymbolSource {

	FILE* out_;
	SymbolGenerator gen_;

public:

	SymbolSource(FILE* output_file, SymbolMap symbol_map)
	: out_(output_file), gen_(symbol_frequencies()) {
	}

	void generate(int n) const {
		while (n-- > 0)
			fprintf(out_, "%c", gen_.get());
	}

};

}


#endif /* SYMBOL_SOURCE_H_ */
