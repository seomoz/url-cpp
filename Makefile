CPP          = g++
CPPOPTS      = -Wall -Werror -std=c++11 -Iinclude/
DEBUG_OPTS   = -fprofile-arcs -ftest-coverage -O0 -g -fPIC
RELEASE_OPTS = -O3

release: release/url.o

release/url.o: src/url.cpp include/url.h
	mkdir -p release
	$(CPP) $(CPPOPTS) $(RELEASE_OPTS) -o $@ -c $<

debug: debug/url.o

debug/url.o: src/url.cpp include/url.h
	mkdir -p debug
	$(CPP) $(CPPOPTS) $(DEBUG_OPTS) -o $@ -c $<

bench: bench.cpp release
	$(CPP) $(CPPOPTS) $(RELEASE_OPTS) -o $@ $< release/url.o

run-tests: test.cpp debug
	$(CPP) $(CPPOPTS) $(DEBUG_OPTS) -o $@ $< debug/url.o -lgtest -lpthread

.PHONY: test
test: run-tests
	./run-tests
	./scripts/check-coverage.sh $(PWD)

clean:
	find . -name '*.o' -o -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \
		| xargs --no-run-if-empty rm
	rm -f run-tests bench
