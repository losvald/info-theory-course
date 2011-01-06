/*
 * source_properties.h
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
 * source_properties.h
 *
 *  Created on: Dec 24, 2010
 *      Author: Leo Osvald
 */

#ifndef SOURCE_PROPERTIES_H_
#define SOURCE_PROPERTIES_H_

#include <map>

#include "base.h"

namespace source {

class SourceProperties {

	ProbabilityMap symbol_frequencies_;

  public:
	SourceProperties() {
		// p(a) = 0.4, p(b) = 0.1, p(c) = 0.1, p(d) = 0.2, p(e) = 0.2
		symbol_frequencies_['a'] = 0.4;
		symbol_frequencies_['b'] = 0.1;
		symbol_frequencies_['c'] = 0.1;
		symbol_frequencies_['d'] = 0.2;
		symbol_frequencies_['e'] = 0.2;
	}

	const ProbabilityMap& symbol_probabilities() const {
		return symbol_frequencies_;
	}

	static SourceProperties INSTANCE;

};

const ProbabilityMap& symbol_probabilities();

}

#endif /* SOURCE_PROPERTIES_H_ */
