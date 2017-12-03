//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   informacoes_uso_geral.h
 * @author Thales Lima Menezes
 * @date   16/10/2017
 * @brief  Contém informações utilizadas em
 * múltiplos arquivos.
 */

#ifndef __INFORMACOES_USO_GERAL_H__
#define __INFORMACOES_USO_GERAL_H__

typedef enum { false,	true } bool;

enum codigos { INT, CHAR, FLOAT };

enum lista_defines
{INICIO,
 FINAL,
 DADO_HEAP,
 VAR_ELEMENTO};

enum print_defines
{FULL,
 NERFED,
 NAME_ONLY,
 ONE_LINE};

enum codigo_busca_lista
{ POSICAO,
  INFORMACAO_MODS,
  INFORMACAO_ROUND,
  SEARCH};

enum acoes_update_nerfs
{ TIRED,
  DEAD};

void  limpa_buffer(void);

void  print_file  (char* file);

#endif
