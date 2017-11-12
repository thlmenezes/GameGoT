##############################################################
###########Variáveis
#	SOURCES has a string with the address of all source files (*.c)
#	OBJECTS has a string with the address of all object files (*.o)
#	HEADERS has a string with the address of all header files (*.h)
#	CC equals compiler
#	CFLAGS equals compiling flags
#	LFLAGS equals linking flags
#	':=' is the non-recursive way of initializing a variable
##############################################################
SOURCES := $(shell ls src/*.c)
SUBST1	:= $(subst src/,obj/,$(SOURCES))
OBJECTS := $(subst .c,.o,$(SUBST1))
HEADERS := $(shell ls headers/*.h)
CC = gcc
LFLAGS   = -g -I headers/ -o programa -Wall -pedantic
CFLAGS   = -g -I headers/ -c -Wall -pedantic

##############################################################
###########Compilação
# All objects 'n all headers are include in this process
##############################################################
programa:    $(OBJECTS) $(HEADERS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm

#  Every "*.c" in the folder "src" must compile in to an
#	"*.o" in the "obj" and has a dependecy only to it's matching
#	source file ... except main.c, that it's dependent of all
#	headers
obj/arvore.o:	src/arvore.c
	$(CC) $(CFLAGS) -lm $< -o $@

obj/main.o: $(HEADERS)


##############################################################
###########Padrão/Regra de Montagem
# Used when compiling an object for COMPILE
#	'$<' means to use the string that's to the right of the ':'
#	'$@' means to use the string that's to the left of the ':'
##############################################################
obj/%.o:	src/%.c
	$(CC) $(CFLAGS) $< -o $@

##############################################################
########### Organizando e limpando
# Use organize in case you have unorganized files in
#the root directory
# Use clean to remove all compilated files
##############################################################
organize:
ifneq ($(shell ls *.h),)			#if shell ls *.h not equal void
	mv $(shell ls *.h) headers/
endif

ifneq ($(shell ls *.c),) 			#if shell ls *.c not equal void
	mv $(shell ls *.c) src/
endif

ifneq ($(shell ls *.o),) 			#if shell ls *.o not equal void
	mv $(shell ls *.o) obj/
endif

ifneq ($(shell ls Documentação/*.h),)
	mv $(shell ls Documentação/*.h) headers/
endif

ifneq ($(shell ls Documentação/*.c),)
	mv $(shell ls Documentação/*.c) src/
endif

ifneq ($(shell ls Documentação/*.o),)
	mv $(shell ls Documentação/*.o) obj/
endif

ifneq ($(shell ls headers/*.c),)
	mv $(shell ls headers/*.c) src/
endif

ifneq ($(shell ls headers/*.o),)
	mv $(shell ls headers/*.o) obj/
endif

ifneq ($(shell ls obj/*.h),)
	mv $(shell ls obj/*.h) headers/
endif

ifneq ($(shell ls obj/*.c),)
	mv $(shell ls obj/*.c) src/
endif

ifneq ($(shell ls src/*.h),)
	mv $(shell ls src/*.h) headers/
endif

ifneq ($(shell ls src/*.o),)
	mv $(shell ls src/*.o) obj/
endif

clean:

ifneq ($(shell ls obj/*.o),)
	rm obj/*.o
endif

ifneq ($(findstring ./programa, $(shell find . -maxdepth 1 -perm -111 -type f)),)
	rm programa
endif

##############################################################
.PHONY = programa organize clean
