/*
 * symbol_generator.h
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
 * symbol_generator.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef SYMBOL_GENERATOR_H_
#define SYMBOL_GENERATOR_H_

#include "../random_utils.h"
#include "../source_properties.h"

namespace source {

	class SymbolGenerator {
	private:
		RandomUtils::DiscreteRandomVariable<char> var_;
	public:

		SymbolGenerator(const SymbolMap& symbol_map) : var_(0) {
			FOREACH (it, symbol_map) {
				var_.add(it->first, it->second);
			}
		}

		char get() const {
			return var_.get();
		}

	};

}

#endif /* SYMBOL_GENERATOR_H_ */
