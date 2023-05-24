CXX=clang++

objects=matrices.o

matrix: ${objects}
	${CXX} -o matrix ${objects}

${objects}: matrices.cpp matrices.h

.PHONY=clean

clean:
	rm -f *.o matrix