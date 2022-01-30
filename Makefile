ifdef devmode
	DEV_OPTS=-DANG_MORE_WARNINGS=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
endif
ifndef toolchain
	TOOLCHAIN_OPT=
endif
ifeq ($(toolchain),x86_64-w64-mingw32)
	TOOLCHAIN_OPT=-DCMAKE_TOOLCHAIN_FILE=./cmake/toolchains/x86_64-w64-mingw32.cmake
endif


all: build_debug

cmake_build:
	mkdir cmake_build

refresh_release: cmake_build
	cd cmake_build; cmake .. $(TOOLCHAIN_OPT) -DCMAKE_BUILD_TYPE=Release \
	 $(DEV_OPTS)

refresh_debug: cmake_build
	cd cmake_build; cmake .. $(TOOLCHAIN_OPT) -DCMAKE_BUILD_TYPE=Debug \
	 -DANG_MORE_WARNINGS=ON -DANG_WERROR=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

build:
	cmake --build cmake_build -- -j`nproc --all`

build_release: refresh_release build

build_debug: refresh_debug build

clean:
	-rm -r -f ./cmake_build

lint:
	make clean
	mkdir cmake_build
	cd cmake_build; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	clang-tidy -header-filter=.* \
	 `find . -type f \( -name "*.cpp" -or -name "*.hpp" \)` \
	 -- -I./src -std=c++20

CMAKELINT_FILTER = "-convention/filename, \
	+linelength, \
	-package/consistency, \
	+readability/logic, \
	+readability/mixedcase, \
	+readability/wonkycase, \
	+syntax, \
	+whitespace/eol, \
	-whitespace/extra, \
	+whitespace/indent, \
	+whitespace/mismatch, \
	+whitespace/newline, \
	+whitespace/tabs" \

lint_build:
	make clean
	cmakelint --filter=$(CMAKELINT_FILTER) \
	 `find . -type f \( -name "CMakeLists.txt" -or -name "*.cmake" \)`
