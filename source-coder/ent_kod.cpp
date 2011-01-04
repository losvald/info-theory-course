/*
 * ent_kod.cpp
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
 * ent_kod.cpp
 *
 *  Created on: Jan 4, 2011
 *      Author: Leo Osvald
 */

#include <cstdio>

#include "../source_properties.h"
#include "source_coder.h"

void print_usage() {
	fprintf(stderr, "Koristenje: ent_kod.exe ulazna-datoteka izlazna-datoteka\n");
}

int main(int argc, char **argv) {
	if (argc <= 2) {
		print_usage();
		return 1;
	}

	FILE* input_file = fopen(argv[1], "r");
	FILE* output_file = fopen(argv[2], "w");
	entropycoding::SourceCoder coder(output_file, input_file,
			source::symbol_frequencies());
	coder.codeAll();
	fclose(input_file);
	fclose(output_file);

	return 0;
}

