// list/list.c
// 
// Implementation for linked list.
//
// Prasun Dhungana

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  node_t *curr;
  node_t *temp;
  curr = l->head;

  while (curr!=NULL) {
    temp = curr->next;
    free(curr);
    curr = temp;
  }

  free(l);
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_print(list_t *l) {
  node_t* cur = l->head;
  while(cur != NULL) {
    printf("%d->", cur->value);
    cur = cur->next;
  }
  printf("NULL\n");    
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  node_t *curr;
  curr = l->head;
  int length = 0;

  while (curr != NULL) {
    length += 1;
    curr = curr->next;
  };

  return length;
 }

void list_add_to_back(list_t *l, elem value) {
  node_t *last = (node_t *) getNode(value);
  if (l->head == NULL) {
    l->head = last;
    return;
  }

  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = last;
}

void list_add_to_front(list_t *l, elem value) {
     node_t *cur_node = (node_t *) getNode(value);

     /* Insert to front */
     node_t *head = l->head;  // get head of list

     cur_node->next = head;
     l->head = cur_node;
}

void list_add_at_index(list_t *l, elem value, int index) {

  if (index < 0 || index >= list_length(l)) {
    return;
  };

  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }

  node_t *new_node = (node_t *) getNode(value);
  new_node->value = value;
  node_t *curr = l->head;
  int ind = 0;

  while (ind < index - 1) {
    if (curr == NULL) {
      free(new_node);
      return;
    }
    curr = curr->next;
    ind += 1;
  }
  if (curr == NULL) {
    free(new_node);
    return;
  }
  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) { 
  
  if (l == NULL || l->head == NULL) {
    return -1;
  };

  node_t *curr = l->head;
  if (curr->next == NULL) {
    elem val = curr->value;
    free(curr);
    l->head = NULL;
    return val;
  };

  while (curr->next->next != NULL) {
    curr = curr->next;
  };

  elem val = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return val;
}

elem list_remove_from_front(list_t *l) {
  if (l == NULL || l->head == NULL) {
    return -1;
  }
  
  node_t *curr = l->head;
  elem val = curr->value;
  l->head = curr->next;
  free(curr);

  return val;
}

elem list_remove_at_index(list_t *l, int index) { 
  if (l->head == NULL) {
    return -1;
  }

  if (index == 0) {
    return list_remove_from_front(l);
  }

  node_t *curr = l->head;
  int ind = 0;

  while (curr != NULL && ind != index - 1) {
    curr = curr->next;
    ind += 1;
  }

  if (curr == NULL || curr->next == NULL) {
    return -1;
  }

  node_t *next = curr->next;
  elem val = next->value;
  curr->next = next->next;
  free(next);

  return val;
}


bool list_is_in(list_t *l, elem value) { 
  
  node_t *curr;
  curr = l->head;

  while (curr != NULL) {
    if (curr->value == value) {
      return true;
    };
    curr = curr->next;
  };
  return false;
}

elem list_get_elem_at(list_t *l, int index) { 
  
  node_t *curr;
  curr = l->head;
  int ind = 0;

  while (curr != NULL && ind != index) {
    curr = curr->next;
    ind += 1;
  };

  if (curr == NULL) {
    return -1;
  }

  return curr->value;
}

int list_get_index_of(list_t *l, elem value) { 
  
  node_t *curr;
  curr = l->head;
  int index = 0;

  while (curr != NULL) {
    if (curr->value == value) {
      return index;
    }
    curr = curr->next;
    index += 1;
  }
  return -1;
}