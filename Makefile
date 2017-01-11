CXX          ?= g++
CXXOPTS      ?= -Wall -Werror -std=c++11 -Iinclude/
DEBUG_OPTS   ?= -fprofile-arcs -ftest-coverage -O0 -g -fPIC
RELEASE_OPTS ?= -O3

# Release libraries
release:
	mkdir -p release

release/liburl.o: release/url.o release/utf8.o release/punycode.o release/psl.o
	ld -r -o $@ $^

release/%.o: src/%.cpp include/%.h
	mkdir -p release
	$(CXX) $(CXXOPTS) $(RELEASE_OPTS) -o $@ -c $<

# Debug libraries
debug:
	mkdir -p debug

debug/liburl.o: debug/url.o debug/utf8.o debug/punycode.o debug/psl.o
	ld -r -o $@ $^

debug/%.o: src/%.cpp include/%.h
	mkdir -p debug
	$(CXX) $(CXXOPTS) $(DEBUG_OPTS) -o $@ -c $<

# Tests
test/%.o: test/%.cpp
	$(CXX) $(CXXOPTS) $(DEBUG_OPTS) -o $@ -c $<

test-all: test/test-all.o test/test-url.o test/test-utf8.o test/test-punycode.o test/test-psl.o debug/liburl.o
	$(CXX) $(CXXOPTS) $(DEBUG_OPTS) -o $@ $^ -lgtest -lpthread

.PHONY: test
test: test-all
	./test-all
	./scripts/check-coverage.sh $(PWD)

bench: bench.cpp release
	$(CXX) $(CXXOPTS) $(RELEASE_OPTS) -o $@ $< release/liburl.o

clean:
	find . -name '*.o' -o -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \
		| xargs --no-run-if-empty rm
	rm -f test-all bench
