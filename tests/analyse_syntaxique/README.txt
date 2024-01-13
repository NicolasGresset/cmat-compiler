Plusieurs points doivent être modifiés dans le parser

- Il y a actuellement 21 shift/reduce conflits ainsi que 2
reduce/reduce conflits. Qui doivent être réglés au plus vite ! Pour
cela rajouter l'option -Wcounterexamples dans la commande bison du
Makefile.

- J'ai apporté une modification importante du parser. Il était
impossible de réaliser l'opération suivante :
a + b;

Ainsi, j'ai ajouté la règle affectation -> expression fin_aff
(l.40). Je pense que c'est le mieux. En effet chose surprenante, il
est possible de faire les opérations :

a+b, b=a+b;
