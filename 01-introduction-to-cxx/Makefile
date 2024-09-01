# ==============================================================================
# @file: Makefile
# @note: should set SHU_CXX_2024_ROOT_DIR to the root directory of the project
# ==============================================================================

01_INTRODUCTION_TO_CXX_DIR="${SHU_CXX_2024_ROOT_DIR}/01-introduction-to-cxx"
CXX="clang++"
CXX_FLAGS="-std=c++23"

.PONEY: all
all: 
	@echo "Building 01-introduction-to-cxx"
	mkdir -p ${SHU_CXX_2024_ROOT_DIR}/build/01-introduction-to-cxx
	
	# comment the following line if you don't have bear installed
	bear --output "${01_INTRODUCTION_TO_CXX_DIR}/compile_commands.json" -- \
		${CXX} ${CXX_FLAGS} \
	    -o ${SHU_CXX_2024_ROOT_DIR}/build/01-introduction-to-cxx/main \
	    -I ${01_INTRODUCTION_TO_CXX_DIR}/include \
	    -D YEAR=\"2024\" \
	    ${01_INTRODUCTION_TO_CXX_DIR}/src/*.cpp

.PONEY: clean
clean:
	@echo "Cleaning 01-introduction-to-cxx"
	rm -rf ${SHU_CXX_2024_ROOT_DIR}/build/01-introduction-to-cxx

.PONEY: run
run:
	@echo "Running 01-introduction-to-cxx"
	@${SHU_CXX_2024_ROOT_DIR}/build/01-introduction-to-cxx/main
