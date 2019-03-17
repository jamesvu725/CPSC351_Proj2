clean:
	rm -f jvu.log jvuproj2
compile:  jvuproj2.cpp
	g++ -pthread -o jvuproj2 jvuproj2.cpp
	./jvuproj2
all: jvuproj2.cpp
	make clean
	make compile
