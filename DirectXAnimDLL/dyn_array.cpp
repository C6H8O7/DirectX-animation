#include "stdafx.h"

Array CreateArray()
{
	Array a =
	{
		0,
		DEFAULT_CAPACITY,
		(void**)calloc(DEFAULT_CAPACITY, sizeof(void*))
	};

	return a;
}

void InitArray(Array *_array)
{
	_array->size		= 0;
	_array->capacity	= DEFAULT_CAPACITY;
	_array->data		= (void**)calloc(DEFAULT_CAPACITY, sizeof(void*));
}

void ExpandArray(Array *_array)
{
	_array->capacity	= _array->capacity * 2;
	_array->data		= (void**)realloc((void*)_array->data, _array->capacity * sizeof(void*));
}

void PushBackArray(Array *_array, void *_obj)
{
	if(_array->size == _array->capacity)
		ExpandArray(_array);

	_array->data[_array->size++] = _obj;
}

void RemoveObjArray(Array *_array, void *_obj)
{
	void **data = _array->data;

	for(int i=0; i<_array->size; i++)
		if(data[i] == _obj)
			data[i] = data[--_array->size];
}

void RemoveIndexArray(Array *_array, int _index)
{
	_array->data[_index] = _array->data[--_array->size];
}

void EmptyArray(Array *_array, bool _freeElems)
{
	if(_freeElems)
		for(int i=0; i<_array->size; i++)
			free(_array->data[i]);

	_array->size = 0;
}