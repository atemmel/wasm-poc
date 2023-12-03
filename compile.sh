#!/bin/sh

#-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap'] \
#-sEXPORT_NAME='Main' \
#-sMODULARIZE=1 \
#-sEXPORTED_FUNCTIONS=['_main'] \
#-sINVOKE_RUN=0 \
#-gsource-map \

em++ -o build/wasm-poc.js \
	main.cpp \
	-sUSE_SDL=2 \
	-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	-sFORCE_FILESYSTEM=1 \
	-sALLOW_MEMORY_GROWTH=1 \
	-sASYNCIFY \
	-sDEMANGLE_SUPPORT=1 \
	-g \
