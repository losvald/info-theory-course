#include <cstdio>
#include <iostream>
#include <string>

#include "binary_code.h"

#include "source_properties.h"

#include "symbol-source/symbol_source.h"

//#define RUN_SOURCE
//#define RUN_SOURCE_CODER
#define RUN_CHANNEL_CODER
//#define RUN_CHANNEL_SCRAMBLER
//#define RUN_CHANNEL_DECODER
//#define RUN_DESTINATION_DECODER


#ifdef RUN_SOURCE
#include "symbol-source/symbol_generator.h"
#endif

#ifdef RUN_SOURCE_CODER
#include "source-coder/source_coder.h"
#endif

#ifdef RUN_CHANNEL_SCRAMBLER
#include "channel/channel.h"
#endif

#ifdef RUN_CHANNEL_CODER
#include "channel-coder/channel_coder.h"
#endif

#ifdef RUN_DESTINATION_DECODER
#include "destination-decoder/destination_decoder.h"
#endif


int main(int argc, char** argv) {
	//  BinaryCode bc(std::string("101"));
	//  std::cout << bc;
	//  std::cout << source::generate();

#ifdef RUN_SOURCE
	source::SymbolSource ss(stdout, source::symbol_frequencies());
	ss.generate(10000);
#endif
#ifdef RUN_SOURCE_CODER
	entropycoding::SourceCoder sourceCoder(stdout, stdin,
			source::symbol_frequencies());
	sourceCoder.codeAll();
#endif
#ifdef RUN_CHANNEL_SCRAMBLER
	channel::Channel ch(stdout, stdin, NULL);
	ch.scramble();
#endif
#ifdef RUN_CHANNEL_CODER
	paritycoding::ChannelCoder hammingCoder(stdout, stdin, 15, 11);
#endif
#ifdef RUN_DESTINATION_DECODER
	entropycoding::DestinationDecoder destinationDecoder(stdout, stdin,
			source::symbol_frequencies());
	destinationDecoder.decodeAll();
#endif
#ifdef RUN_TEST
	std::cout << "\ntest";
#endif
	std::cout << "END OF MAIN";
	return 0;
}
