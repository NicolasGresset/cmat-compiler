#pragma once
/* TABLE DES SYMBOLES */
#define TAILLE_MAX_TOKEN 32
#define TAILLE_MAX_STRING 64

typedef char name_t[TAILLE_MAX_TOKEN];
typedef enum { ENTIER, REEL, MATRIX_TYPE, STRING } type_t;
typedef union {
    int int_value;
    float float_value;
} value_t;
struct id_t {
    type_t type;
    name_t name;
    union
    { /// Connaître la taille de MATRIX
        struct
        {
            int row; // Nombre de lignes
            int col; // Nombre de colonnes
        };
    };
}; // Structure de l'identificateur

struct symbol {
    enum {
        NAME, // Pour les identificateurs
        INT_CONSTANT,
        FLOAT_CONSTANT,
        STRING_CONSTANT,
        LABEL /// Pour les addresses
    } kind;   /// To know the kind of symbol
    union {
        struct id_t id;    // un identificateur
        int int_value;     // CONSTANTE ENTIERE
        float float_value; // CONSTANTE REELLE
        unsigned int addr; // ADRESSE
        char string[TAILLE_MAX_STRING];
    } u;
};

struct symtable {
    unsigned int capacity;
    unsigned int temporary;
    unsigned int size;
    struct symbol *symbols;
};

// Pour le parser
struct exprval
{
    struct symbol * ptr;
    type_t type;
    int num;
};

struct symbol *symbol_id(const struct id_t id);

struct symbol *symbol_const_int(int intval);

struct symbol *symbol_const_float(float floatval);

struct symbol * symbol_declare(const struct id_t id);

struct symbol * symbol_declare_tab(const struct id_t id);

struct symtable *symtable_new();

struct symbol *symtable_const_int(struct symtable *t, int e);

struct symbol *symtable_const_float(struct symtable *t, float v);

struct symbol *symtable_get(struct symtable *t, const char *s);

struct symbol *symtable_put(struct symtable *t, const char *s, type_t type);

void symtable_dump(struct symtable *t);
void symtable_assemble(struct symtable *t);

void symtable_free(struct symtable *t);

/* QUADRUPLETS ET CODE */

// représente un quadruplet : représentation 3 adresses
struct quad {
    enum quad_kind {
        Q_DECLARE,
        Q_DECLARE_MAT,
        Q_DECLARE_STRING, // sym1 : id, sym2 : string, NULL
        // Q_SET, = COPY
        Q_SET_MAT,

        BOP_PLUS,
        BOP_MOINS,
        BOP_MULT,
        BOP_DIVISE,
        UOP_PLUS,    // faire a = +b  (idem copy...)
        UOP_MOINS,   // faire a = -b (en dur multipler par -1 avant ?)

        // Operation entre 2 matrices
        MATOP_PLUS,
        MATOP_MOINS,
        MATOP_MULT,
        MATOP_DIVISE,
        UMATOP_PLUS,
        UMATOP_MOINS,
        UMATOP_TRANSPOSE,

        // Operation entre 1 matrice et 1 float ou entier
        MAT_BIN_PLUS,
        MAT_BIN_MOINS,
        MAT_BIN_MULT,
        MAT_BIN_DIVISE,

        COPY,

        ADRESSE,

        Q_IF_EQ,
        Q_IF_NEQ,
        Q_IF_LT,
        Q_IF_LE,
        Q_IF_GE,
        Q_IF_GT,

        Q_GOTO,
        Q_GOTO_UNKNOWN,
        CALL_PRINT, // sym1 : id à afficher, NULL, NULL 
        CALL_PRINT_MAT, // sym1 : id de la matrice à afficher, NULL, NULL
        CALL_PRINTF, // sym1 : id de la chaine de caractère à afficher, NULL, NULL

        ARRAY_AFFECT, // équivaut à id[i] = a : sym1 est l'id, sym2 l'indice, sym3
                      // la valeur

    } kind;
    struct symbol *sym1;
    struct symbol *sym2;
    struct symbol *sym3;
};

/**
 * Création d'un symbol de type LABEL
 */
struct symbol *quad_label(void);

struct code {
    char *filename;
    unsigned int capacity;
    unsigned int nextquad;
    struct quad *quads;
};

struct code *code_new();

void gencode(struct code *c, enum quad_kind k, struct symbol *s1,
             struct symbol *s2, struct symbol *s3);

// struct symbol *newtemp(struct symtable * t);

void code_dump(struct code *c);
void code_free(struct code *c);
