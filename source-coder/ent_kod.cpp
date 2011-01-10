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
#include <cstring>

#include "../source_properties.h"
#include "huffman_coder.h"

void print_usage() {
	fprintf(stderr, "Koristenje: ent_kod.exe ulazna-datoteka [izlazna-datoteka]\n");
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		print_usage();
		return 1;
	}

	FILE* input_file = (strcmp(argv[1], "-") ? fopen(argv[1], "r") : stdin);
	FILE* output_file = (argc <= 2 ? fopen("23.txt", "w")
			: (strcmp(argv[2], "-") ? fopen(argv[2], "w") : stdout));

	entropycoding::HuffmanCoder coder(source::symbol_frequencies());
	for (char c; (c = getc(input_file)) != EOF && !isEndline(c); )
		fputs(coder.code(c).toString().c_str(), output_file);

	fclose(input_file);
	fclose(output_file);

	return 0;
}

