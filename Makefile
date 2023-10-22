interpreters:
	g++ fractran/fractran-interpreter.cc -o fractran/fractran
	g++ game-of-life/life-interpreter.cc -o game-of-life/life
	g++ brainfuck/codeExtractor.cc -o brainfuck/bf-extract 
	g++ brainfuck/completer.cc -o brainfuck/bf-copy 
	g++ brainfuck/debugger.cc -o brainfuck/bf-debug 
	g++ brainfuck/interpreter.cc -o brainfuck/bf 
