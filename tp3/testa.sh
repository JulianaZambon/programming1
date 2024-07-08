#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "numero incorreto de parâmetros"
    echo "Uso: $0 <opcao>"
    echo "   -- opcao = 1 : testa o programa sem se preocupar com vazamentos de memoria"
    echo "   -- opcao = 2 : teste completo do programa"
    exit;
fi

TIPO_TESTE=$1
echo ${TIPO_TESTE}

if [ ${TIPO_TESTE} == 1 ]; then
    COMANDO="./tp3"
elif [ ${TIPO_TESTE} == 2 ]; then
    COMANDO="valgrind --leak-check=full ./tp3"
else
    echo "opcao incorreta"
    echo "   -- opcao = 1 : testa o programa sem se preocupar com vazamentos de memoria"
    echo "   -- opcao = 2 : teste completo do programa"
    exit
fi

for i in 1 2 3 4 5
do
    eval "${COMANDO}" < ./casos_de_teste/entrada_$i.txt | diff - ./casos_de_teste/saida_$i.txt
done
