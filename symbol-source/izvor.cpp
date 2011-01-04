/*
 * izvor.cpp
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
 * izvor.cpp
 *
 *  Created on: Jan 3, 2011
 *      Author: Leo Osvald
 */

#include <cstdio>

#include "../source_properties.h"
#include "symbol_source.h"

void print_usage() {
	fprintf(stderr, "Koristenje: izvor.exe izlazna-datoteka\n");
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		print_usage();
		return 1;
	}

	printf("HELLO WORLD4");
	FILE* output_file = fopen(argv[1], "w");
	source::SymbolSource ss(output_file, source::symbol_frequencies());
	ss.generate(10000);
	fclose(output_file);

	return 0;
}

