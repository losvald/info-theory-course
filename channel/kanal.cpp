/*
 * kanal.cpp
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
 * kanal.cpp
 *
 *  Created on: Jan 4, 2011
 *      Author: Leo Osvald
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>

#include "../bit_iterator.h"

void print_usage() {
	fprintf(stderr, "Koristenje: kanal.exe ulazna-datoteka pogreske-datoteka [izlazna-datoteka]\n");
}

int main(int argc, char **argv) {
	if (argc <= 2) {
		print_usage();
		return 1;
	}

	FILE* input_file = (strcmp(argv[1], "-") ? fopen(argv[1], "r") : stdin);
	FILE* error_vec_file = (strcmp(argv[2], "-") ? fopen(argv[2], "r") : NULL);
	FILE* output_file = (argc <= 3 ? fopen("45.txt", "w") // XXX hardkodirano
			: (strcmp(argv[3], "-") ? fopen(argv[3], "w") : stdout));

	FileBitIterator in_it(input_file);
	FileBitIterator error_vec_it(error_vec_file);
	while (in_it.hasNextBit()) {
		bool bit = in_it.nextBit();
		if (error_vec_it.hasNextBit())
			bit ^= error_vec_it.nextBit();
		putc(fromBit(bit), output_file);
	}

	fclose(input_file);
	fclose(output_file);
	if (error_vec_file != NULL)
		fclose(error_vec_file);

	return 0;
}
