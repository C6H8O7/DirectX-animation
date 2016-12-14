#ifndef DYN_LIST_H
#define DYN_LIST_H

#include "stdafx.h"

void* dyn_addObjectToListFRONT( void* _obj, int _size, void** _list );

void* dyn_addObjectToListBACK( void* _obj, int _size, void** _list );

void dyn_removeObjectFromList( void* _obj, void** _list );

unsigned int dyn_getListSize( void* _list );

void dyn_emptyList( void** _list );

void dyn_saveListToFile( void* _list, int _size, FILE* _file );
unsigned int dyn_loadListFromFile( void** _list, int _size, FILE* _file );

#endif