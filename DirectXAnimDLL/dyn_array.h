#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include "stdafx.h"

#define DEFAULT_CAPACITY 32

struct Array
{
	int size;
	int capacity;

	void **data;
};

Array CreateArray();
void InitArray(Array *_array);

void ExpandArray(Array *_array);

void PushBackArray(Array *_array, void *_obj);
void RemoveObjArray(Array *_array, void *_obj);
void RemoveIndexArray(Array *_array, int _index);
void EmptyArray(Array *_array, bool _freeElems);

#endif