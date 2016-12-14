/*
	Fichier : dyn_list.cpp

	Auteur : Marco

	Date : 20/10/2014

	Description :
	
	Ce fichier a �t� r�alis� dans le but d'�conomiser un bon nombre de lignes et de temps
	pour tout ce qui s'appr�te � la gestion de listes chain�es, il est utilis� pour la gestion
	des listes chain�es de fa�on g�n�rique.

	Il sert aussi � la sauvegarde et au chargement des diff�rentes listes en respectant la syntaxe suivante :

		(Nombre N d'�lements stock�s)(Element 1)(Element 2)...(Element N-1)(Element N)

	Pour parvenir � concevoir cette gestion "g�n�rique" de listes chain�es, j'ai trouv� le concept suivant :

		On place le pointeur "next" au d�but de chaque structure utilis�e dans une liste,
		ainsi, on sait que pour n'importe quel type de donn�e � utiliser, le pointeur vers la donn�e
		suivante se trouve � l'endroit meme o� la donn�e "commence" en m�moire.
		On peut donc acc�der � ce pointeur sans connaitre le type de donn�e utilis�e, en consid�rant que
		le pointeur "next" peut s'interpr�ter comme une donn�e de type entier non sign� 32 bits,
		c'est � dire compris entre 0x00000000 et 0xFFFFFFFF, "comme" pour une adresse m�moire sous
		syst�me x86. ( Le code s'adaptera seul aux �xigences d'une architecture x64. )

	Il devient alors tr�s simple de r�cup�rer la valeur de "next" avec un pointeur de structure :

		MEM_ADDR adresse, next;

		On cast le pointeur de structure en pointeur d'adresse :
			adresse = (MEM_ADDR*)(pointeur de structure);

		On sait que l'adresse du "next" se trouve � l'endroit meme ou commence la structure :
			next = *adresse;

		Ce qui revient � faire :
			next = *(MEM_ADDR*)(pointeur de structure);

	Et pour �crire l'emplacement du "next", �tant donn� que l'emplacement m�moire est d�j� r�serv� dans la structure :
			*(MEM_ADDR*)(adresse) = next;
*/

#include "stdafx.h"

#if defined(_WIN64)
	typedef unsigned __int64 MEM_ADDR;
#else
	typedef unsigned __int32 MEM_ADDR;
#endif

typedef unsigned char BYTE;

/*
	J'ai voulu "recr�er" la fonction memcpy dans le but d'essayer de gagner en performance
	( �viter d'appeller une fonction qui se trouve hors de mon code ), je l'ai refaite de la mani�re
	la plus basique possible : une copie Byte apr�s Byte.
*/

inline void cpy( void* _dst, void* _src, unsigned int _size )
{
	unsigned int i;
	for( i=0; i<_size; i++ ) *(BYTE*)((MEM_ADDR)_dst + i) = *(BYTE*)((MEM_ADDR)_src + i);
}

/*
	Cette fonction ajoute l'objet en t�te de liste ( pour faire des piles )
*/

inline void* push_front( void* _obj, int _size, void** _list )
{
	void *new_obj = calloc(1, _size);
	cpy(new_obj, _obj, _size);

	*(MEM_ADDR*)(new_obj) = *(MEM_ADDR*)(_list);
	*_list = new_obj;

	return new_obj;
}

/*
	Cette fonction ajoute l'objet en queue de liste ( pour faire des files )
*/

inline void* push_back( void* _obj, int _size, void** _list )
{
	void *new_obj = calloc(1, _size), *cur = *_list;
	MEM_ADDR nxt = 0;
	cpy(new_obj, _obj, _size);

	if( !(*_list) ) return push_front(_obj, _size, _list);

	while( cur )
	{
		nxt = *(MEM_ADDR*)(cur);
		if( !nxt )
		{
			*(MEM_ADDR*)(cur) = (MEM_ADDR)new_obj;
			*(MEM_ADDR*)(new_obj) = 0;
		}
		cur = (void*)nxt;
	}

	return new_obj;
}

/*
	Je me suis un peu inspir� de la fonction time pour cette fonction :
	Elle retourne la m�me valeur qu'elle stocke dans l'argument, on peut donc s'en servir
	pour r�cup�rer le pointeur "next" tout en effectuant un test sur le retour.
*/

inline void* dyn_getNext( void** _obj )
{
	MEM_ADDR nxt = *(MEM_ADDR*)(*_obj);
	*(MEM_ADDR*)(_obj) = nxt;
	return (void*)nxt;
}

/*
	Ces deux fonctions sont les fonctions utilis�es dans les autres fichiers cpp,
	elles font simplement un appel aux fonctions vues plus haut.
*/

void* dyn_addObjectToListFRONT( void* _obj, int _size, void** _list )
{
	return push_front(_obj, _size, _list);
}

void* dyn_addObjectToListBACK( void* _obj, int _size, void** _list )
{
	return push_back(_obj, _size, _list);
}

/*
	Cette fonction est utilis�e dans les autres fichiers cpp,
	C'est elle qui va supprimer n'importe quel �l�ment de n'importe quel type de liste
	qu'on lui donne, elle a simplement besoin de l'adresse � laquelle est stock�
	l'�l�ment que l'on veut supprimer ( on n'utilise pas d'indice )
*/

void dyn_removeObjectFromList( void* _obj, void** _list )
{
	void* cur = *_list;
	MEM_ADDR prev = 0, nxt = 0;

	while( cur )
	{
		nxt = *(MEM_ADDR*)(cur); // On stocke l'adresse du prochain objet de la liste
		if( cur == _obj ) // On a trouv� l'objet � supprimer
		{
			if( !prev )
			{
				if( nxt ) *_list = (void*)nxt;
				else *_list = 0;
				free(cur);
			}
			else if( !nxt )
			{
				*(MEM_ADDR*)(prev) = 0;
				free(cur);
			}
			else
			{
				*(MEM_ADDR*)(prev) = *(MEM_ADDR*)(cur);
				free(cur);
			}
		}
		prev = (MEM_ADDR)cur; // On fait un backup de l'adresse de l'objet actuel ( qui devient le pr�c�dent )
		cur = (void*)nxt;
	}
}

/*
	Cette fonction renvoie simplement le nombre d'objets stock�s
	dans une liste, toujours sur le m�me principe.
*/

unsigned int dyn_getListSize( void* _list )
{
	void *cur = _list;
	int i = 0;
	MEM_ADDR nxt = 0;

	if( !_list ) return 0;

	while( dyn_getNext(&cur) )
		++i;

	return ++i;
}

/*
	Cette fonction va supprimer tous les �l�ments d'une liste
	( lorsqu'on veut charger une partie ou initialiser un nouveau niveau par exemple )
*/

void dyn_emptyList( void** _list )
{
	MEM_ADDR cur = (MEM_ADDR)*_list, nxt = 0;

	if( !*_list ) return;

	while( cur )
	{
		nxt = *(MEM_ADDR*)(cur);
		free((void*)cur);
		cur = nxt;
	}
	
	*_list = 0;
}

/*
	Ces 2 fonctions servent � �crire et lire des donn�es
	depuis un fichier/une liste vers une liste/un fichier
*/

void dyn_saveListToFile( void* _list, int _size, FILE* _file )
{
	MEM_ADDR cur = (MEM_ADDR)_list, nxt = 0;
	unsigned int size = 0;

	if( !cur )
	{
		fwrite(&size, sizeof(unsigned int), 1, _file);
		return;
	}

	size = dyn_getListSize(_list);
	fwrite(&size, sizeof(unsigned int), 1, _file);

	while(cur)
	{
		nxt = *(MEM_ADDR*)(cur);
		fwrite((void*)cur, _size, 1, _file);
		cur = nxt;
	}
}

unsigned int dyn_loadListFromFile( void** _list, int _size, FILE* _file )
{
	unsigned int size = 0, i = 0;
	MEM_ADDR nxt = 0;
	void *list = 0;

	fread(&size, sizeof(unsigned int), 1, _file);

	if(size <= 0)
	{
		*(MEM_ADDR*)(_list) = 0;
		return 0;
	}

	for(i=0; i<size; i++)
	{
		void *obj = malloc(_size);
		fread(obj, _size, 1, _file);
		dyn_addObjectToListBACK(obj, _size, &list);
		free(obj);
	}

	*_list = list;
	return size;
}