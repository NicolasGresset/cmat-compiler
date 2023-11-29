#!/bin/bash

TARGET=tests

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

exit 0