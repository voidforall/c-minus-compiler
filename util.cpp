#include "util.h"

Node * find_tail(Node * node) {
    if (node != nullptr) {
        while (node.next != nullptr_t) {
            node = node.next;
        }
    }

    return node;
}
