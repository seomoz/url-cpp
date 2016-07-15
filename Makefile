CPP          = g++
CPPOPTS      = -Wall -Werror -std=c++11 -Iinclude/
DEBUG_OPTS   = -fprofile-arcs -ftest-coverage -O0 -g -fPIC
RELEASE_OPTS = -O3
DEBUG_LIBS   = debug/url.o
RELEASE_LIBS = release/url.o

release: $(RELEASE_LIBS)

release/%.o: src/%.cpp include/%.h
	mkdir -p release
	$(CPP) $(CPPOPTS) $(RELEASE_OPTS) -o $@ -c $<

debug: $(DEBUG_LIBS)

debug/%.o: src/%.cpp include/%.h
	mkdir -p debug
	$(CPP) $(CPPOPTS) $(DEBUG_OPTS) -o $@ -c $<

bench: bench.cpp release
	$(CPP) $(CPPOPTS) $(RELEASE_OPTS) -o $@ $< $(RELEASE_LIBS)

test/%.o: test/%.cpp
	$(CPP) $(CPPOPTS) $(DEBUG_OPTS) -o $@ -c $<

run-tests: test/test-all.o test/test-url.o $(DEBUG_LIBS)
	$(CPP) $(CPPOPTS) $(DEBUG_OPTS) -o $@ $^ -lgtest -lpthread

.PHONY: test
test: run-tests
	./run-tests
	./scripts/check-coverage.sh $(PWD)

clean:
	find . -name '*.o' -o -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \
		| xargs --no-run-if-empty rm
	rm -f run-tests bench
