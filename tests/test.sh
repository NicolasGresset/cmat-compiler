#!/bin/bash

CMAT=./../../bin/cmat

#
# Se placer dans le répertoire courant
#
TESTDIR="$(cd "$(dirname "$0}")" && pwd)"
cd "$TESTDIR"

#
# Conserver une trace de toutes les actions
#
LOG="test.log"
rm -f "$LOG"
touch "$LOG"

#
# Importer les fonctions communes à tous les tests
#
. ./fonctions.sh

#
# Test analyseur lexical
#

annoncer "Test analyseur lexical"
cd analyse_lex
make clean
make >> $LOG 2>&1 || fail
./lexer test.txt > monresultat.txt 2>&1 || fail
diff attendu.txt monresultat.txt || fail
make clean
cd ..
coloredEcho "OK" green


#
# Test fonctions vecteurs et matrices
#

annoncer "Test fonctions vecteurs et matrices"
cd fonction_mat
make clean
make >> $LOG 2>&1 || fail
./exec > monresultat.txt 2>&1 || fail
diff attendu.txt monresultat.txt || fail
coloredEcho "Les fonctions sont OK pour des matrices compatibles" green

test_segfault "./exemple1" || fail
test_segfault "./exemple2" || fail
test_segfault "./exemple3" || fail
coloredEcho "Les fonctions sont OK pour des matrices incompatibles" green

make clean
cd ..
coloredEcho "OK" green

#
# Test programmes CMat
#


cd ..
make clean
make 
cd tests/programmes_cmat

annoncer "Test programmes CMat"
# pour chaque fichier .c, on fait CMAT -o nom_fichier.asm < nom_fichier.c
for fichier in *.c
do
    nom_fichier=$(basename "$fichier" .c)
    $CMAT -o "$nom_fichier.asm" < "$fichier" 
done

exit 0