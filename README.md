Agulha de Buffon
================


Calcula o valor de PI usando a técnica de Buffon.


----

Compilação
----------

Efetuar a compilação do código-fonte:


        $ gcc buffon.c -o buffon -lm


----

Uso 
---
Executar com a opção help:


        $ ./buffon -h


----

Exemplos
--------

Lança uma agulha de tamanho 1 1000 vezes: 


        $ buffon -n 1000 -l 1


Lança uma agulha de tamanho 1 1000 vezes com modo verbose:


        $ buffon -n 1000 -l 1 -v


Lança uma agulha de tamanho 1 1000 vezes com modo verbose exibindo a saida em csv:


        $ buffon -n 1000 -l 1 -v -s


Lança uma agulha de tamanho 1 1000 vezes com modo verbose com blocos de 100 (default = 1):


        $ buffon -n 1000 -l 1 -v -b 100 
