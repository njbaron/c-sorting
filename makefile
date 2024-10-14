
build:
	gcc sorting.c -g

run: build
	./a.out

clean:
	rm *.out