#ifndef USERTYPE_H
#define USERTYPE_H

typedef struct ItemTypeTag {
  int x;
  int y;
  struct ItemTypeTag *back;
  char type;
} ItemType;

#endif
