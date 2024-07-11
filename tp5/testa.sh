#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "numero incorreto de parâmetros"
    echo "Uso: $0 <opcao>"
    echo "   -- opcao = 1 : testa o programa sem se preocupar com vazamentos de memoria"
    echo "   -- opcao = 2 : teste completo do programa"
    exit;
fi

TIPO_TESTE=$1

if [ ${TIPO_TESTE} == 1 ]; then
    COMANDO="./tp5"
elif [ ${TIPO_TESTE} == 2 ]; then
    COMANDO="valgrind --leak-check=full ./tp5"
else
    echo "opcao incorreta"
    echo "   -- opcao = 1 : testa o programa sem se preocupar com vazamentos de memoria"
    echo "   -- opcao = 2 : teste completo do programa"
    exit
fi

eval "${COMANDO}" | diff - saida_esperada.txt
