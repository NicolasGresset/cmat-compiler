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
make main >> $LOG 2>&1 || fail
./main < input.txt > output.txt 2>&1 || fail
test_diff output.txt outattendu.txt || fail
cd ..
coloredEcho "OK" green

exit 0