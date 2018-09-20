mssh:	cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./commands/myCommands.o ./linkedlist/listUtils.o ./words/word.o
	gcc -g cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./commands/myCommands.o linkedlist/listUtils.o ./words/word.o -o mssh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc  -g -c ./linkedlist/listUtils.c

linkedList.o:	./linkedlist/linkedList.c ./linkedlist/linkedList.h
	gcc -g -c ./linkedlist/linkedList.c

word.o:		./words/word.c ./words/word.h
	gcc -g -c ./words/word.c

myCommands.o:	./commands/myCommands.c ./commands/myCommands.h
	gcc -g -c ./commands/myCommands.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./linkedlist/linkedList.o
	rm ./commands/myCommands.o
	rm ./words/word.o
	rm ./linkedlist/listUtils.o
	rm lab8

