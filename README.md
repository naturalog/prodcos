To build the solver:
	make
to build the generator:
	make gen
run "gen <size>" (e.g. "gen 10") to generate inputs with <size> numbers, each <size> bits. you can of course do:
	./gen 10 | ./de
and see the result right away. make sure that <size> isn't too high, because it is read as unsigned long, and only afterwards the multiprecision environment gets into action.
