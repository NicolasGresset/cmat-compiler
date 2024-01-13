# Projet Compilation

Au moins le git est créé.

// note : ints = nombre ou variable de type int

/** ce qui marche
 * addition, soustraction de deux ints
 * division avec résultat entier de deux ints
 * if avec condition égalité/inégalite de deux ints
 * a++, a-- avec a int
 * while avec condition comparaison de deux ints
 * for avec i = i+1 à la place de i++
 */

/** ce qui marche pas
 * erreur de syntaxe sur les print et return
 * multiplication de deux int => mult $t0, $t0, $t1 devrait être mult $t1,$t2
 * d'après le simulateur
 * "int a, b;" erreur de syntaxe
 * symboles (jsp si on comptait les prendre ou pas) +=, -=
 * if(a) condition vérifiée que a soit 0 ou non
 * i++ dans le for
 *
 */

/** trucs bizarres (jsp si c'est normal)
 * division de 1/2 dans un int => résultat 0, pas d'erreur
 * division de deux entiers => quotient de la division euclidienne dans le
 * résultat
 * variables int non déclarées, valeur mise à 0
 */
    

// pour les float

/** ce qui marche
 * addition, soustraction de deux float
 * division de deux float
 * multiplication de deux float
 * float b = a + * - / int avec a float
 * () autour d'une expression pour la priorité
 * priorité des opérations
 */

/** ce qui marche pas
 * float a, b; erreur de syntaxe
 * float a = int => code assembleur mais pb de type dans le simulateur
 * == entre deux floats, simulateur aime pas beq $f0, $f2 type incorrect
 * pareil pour != et bne $f0, $f2, < et >
 */

/** trucs bizarres (jsp si c'est normal)
 * float a = 5; pb dans le simulateur de type => est-ce qu'on détecte l'erreur
 * avant ?
 * int a = 5.5; pas de pb, valeur 5 stockée dans a
 * if (a == b ) avec a et b types différents, pas de code assembleur
 * if (a) si a est un float donne une erreur, pas de code assembleur
 *
 */
