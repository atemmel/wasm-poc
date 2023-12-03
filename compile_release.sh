#!/bin/sh
#
em++ -o build/wasm-poc.js \
	main.cpp \
	-sUSE_SDL=2 \
	-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	-sFORCE_FILESYSTEM=1 \
	-sALLOW_MEMORY_GROWTH=1 \
	-sASYNCIFY \
	-sDEMANGLE_SUPPORT=1 \
	-O2 \
