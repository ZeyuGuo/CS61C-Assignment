#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if(head == NULL) return 0;

    node *tortoise = head;
    node *hare = head;

    while(hare != tortoise){
        hare = hare->next;
        if(hare == NULL) return 0;
        hare = hare->next;
        if(hare == NULL) return 0;
        tortoise = tortoise->next;
    }

    return 1;
}