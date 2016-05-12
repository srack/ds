all: test_prog2 topwords cosine

test_prog2: test_prog2.cxx map.h queue.h
	$(CXX) $< -o $@

topwords: topwords.cxx map.h queue.h
	$(CXX) $< -o $@

cosine: cosine.cxx map.h queue.h 
	$(CXX) $< -o $@

clean:
	rm -rf test_prog2 topwords cosine *.exe *.o *.dSYM *~
