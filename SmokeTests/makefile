CC       = gcc
LFLAGS   = -g -I headers/ -o smoke -Wall -pedantic
CFLAGS   = -g -I headers/ -c -Wall -pedantic

clean:
ifneq ($(findstring ./smoke, $(shell find . -maxdepth 1 -perm -111 -type f)),)
	rm smoke
endif

testa_lista: ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o
	$(CC) $(LFLAGS) testa_lista.c ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o

testa_fila:	../obj/informacoes_uso_geral.o ../obj/fila.o ../obj/lista_dupla.o
	$(CC) $(LFLAGS) testa_fila.c ../obj/informacoes_uso_geral.o ../obj/fila.o ../obj/lista_dupla.o

testa_arvore: ../obj/arvore.o
	$(CC) $(LFLAGS) testa_arvore.c ../obj/arvore.o -lm

testa_character: ../obj/character.o ../obj/lista_dupla.o
	$(CC) $(LFLAGS) testa_character.c ../obj/character.o ../obj/lista_dupla.o

../obj/arvore.o: ../src/arvore.c
	$(CC) $(CFLAGS) $< -o $@ -lm

../obj/%.o:	../src/%.c
	$(CC) $(CFLAGS) $< -o $@
