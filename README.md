# simple-thing-parser
Um parser para expressões de um tipo especifico.

A expressão que é lida é da forma "E" sendo:

E -> <string> = X
  
X -> { E* } | <string> | <int>

<string> é tudo entre aspas duplas ""
  
<int> é um número inteiro positivo
  
E* é uma repetição de 0 ou mais E's
