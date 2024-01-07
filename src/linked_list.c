#include "linked_list.h"

/**
 * Correspond at the function creelist
 *
 *
 */
struct  ListLabel * creerListe(unsigned int address)
{
    struct ListLabel * liste = malloc(sizeof(struct ListLabel));
    if (liste == NULL)
    {
        fprintf(stderr, "Allocation error creerListe\n");
        exit(1);
    }

    liste->addr = address;
    liste->next = NULL;

    return liste;
}

void ListLabel_print(struct ListLabel * l)
{
    if( l == NULL )
    {
        printf("empty list");
        return;
    }

    printf("%d --> ", l->addr);
    struct ListLabel * current = l->next;
    while(current != NULL)
    {
        printf("%d -->", current->addr);
        current = current->next;
    }
    printf("\n");
}

void ListLabel_free(struct ListLabel * l)
{
    if (l == NULL)
        return;
    ListLabel_free(l->next);
    free(l);
}

struct ListLabel * concat(struct ListLabel * l1,
                          struct ListLabel * l2)
{
    if(l1 == NULL)
        return l2;
    struct ListLabel * current = l1;

    while(current->next != NULL) {
        current = current->next;
    }
    current->next = l2;
    return l1;
}
