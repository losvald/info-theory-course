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
#include <cstring>

#include "../../source_properties.h"
#include "symbol_generator.h"

void print_usage() {
	fprintf(stderr, "Koristenje: izvor.exe [izlazna-datoteka]\n");
}

int main(int argc, char **argv) {

	FILE* output_file = (argc <= 1 ? fopen("12.txt", "w")
			: (strcmp(argv[1], "-") ? fopen(argv[1], "w") : stdout));
	source::SymbolGenerator gen(source::symbol_probabilities());
	int n = 10000; // XXX hardkodirano
	while (n-- > 0)
		putc(gen.get(), output_file);
	fclose(output_file);

	return 0;
}

