/*
 * z_dekod.cpp
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
 * z_dekod.cpp
 *
 *  Created on: Jan 4, 2011
 *      Author: Leo Osvald
 */

#include <cstdio>
#include <cstring>

#include "../../bit_iterator.h"
#include "../../binary_code.h"
#include "../hamming_code.h"

void print_usage() {
	fprintf(stderr, "Koristenje: z_dekod.exe ulazna-datoteka [izlazna-datoteka]\n");
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		print_usage();
		return 1;
	}

	FILE* input_file = (strcmp(argv[1], "-") ? fopen(argv[1], "r") : stdin);
	FILE* output_file = (argc <= 2 ? fopen("56.txt", "w")
			: (strcmp(argv[2], "-") ? fopen(argv[2], "w") : stdout));

	static const int n = 15; // XXX hardkodirano

	BinaryCode bc;
	FileBitIterator it(input_file);
	for (int block = 0; it.hasNextBit(); ++block) {
		int i;
		for (i = 0; i < n && it.hasNextBit(); ++i) {
			bc.append(it.nextBit());
		}
		// ako fali jos bitova, nadopuni nulama
		for (; i < n; ++i)
			bc.append(false);

		// izvuci podatkovne bitove
		paritycoding::HammingCode hammingCode(bc, true);

		int error_syndrome = hammingCode.fix();
		if (error_syndrome > 0) {
//			int bit_index = block * n + error_syndrome - 1;
//			fprintf(stderr, "[Z_KOD] Ispravio bit %d iz %c u %c\n",
//					bit_index,
//					fromBit(!hammingCode.isSet(bit_index)),
//					fromBit(hammingCode.isSet(bit_index)));
		} else if (error_syndrome < 0) {
			int from = block * n + -error_syndrome - 1;
			fprintf(stderr, "[Z_KOD] Detektirana greska izmedju bitova %d i %d\n",
								from, from + n);
		}

		for (int i = 0; i < hammingCode.dataBitCount(); ++i)
			putc(fromBit(hammingCode.getDataBit(i)), output_file);

		bc.clear();
	}

	fclose(input_file);
	fclose(output_file);

	return 0;
}
