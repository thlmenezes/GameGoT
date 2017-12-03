CC       = gcc
LFLAGS   = -g -I headers/ -o smoke -Wall -pedantic
CFLAGS   = -g -I headers/ -c -Wall -pedantic

clean:
ifneq ($(findstring ./smoke, $(shell find . -maxdepth 1 -perm -111 -type f)),)
	rm smoke
endif

testa_lista: ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o
	$(CC) $(LFLAGS) testa_lista.c ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o

testa_fila:	../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/fila.o
	$(CC) $(LFLAGS) testa_fila.c ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/fila.o

testa_arvore: ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/character.o ../obj/fila.o ../obj/arvore.o 
	$(CC) $(LFLAGS) testa_arvore.c ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/character.o ../obj/fila.o ../obj/arvore.o -lm

testa_loadFromFile: ../obj/informacoes_uso_geral.o ../obj/character.o ../obj/lista_dupla.o ../obj/fila.o ../obj/arvore.o 
	$(CC) $(LFLAGS) testa_loadFromFile.c ../obj/informacoes_uso_geral.o ../obj/character.o ../obj/lista_dupla.o ../obj/fila.o ../obj/arvore.o -lm

testa_round1: ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/fila.o ../obj/character.o ../obj/arvore.o
	$(CC) $(LFLAGS) testa_round1.c ../obj/informacoes_uso_geral.o ../obj/lista_dupla.o ../obj/character.o ../obj/arvore.o ../obj/fila.o -lm

../obj/arvore.o: ../src/arvore.c
	$(CC) $(CFLAGS) $< -o $@ -lm

../obj/%.o:	../src/%.c
	$(CC) $(CFLAGS) $< -o $@
