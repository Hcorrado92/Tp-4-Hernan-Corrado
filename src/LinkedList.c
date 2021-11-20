#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void) {

	LinkedList *this;
	this = (LinkedList*) malloc(sizeof(LinkedList));

	if (this != NULL) {
		this->pFirstNode = NULL;
		this->size = 0;
	}

	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList *this) {

	int returnAux = -1;

	if (this != NULL) {
		returnAux = this->size;
	}

	return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList *this, int nodeIndex) {

	// struct Node* nIndex;

	int i;
	int len;
	struct Node *siguienteNodo = NULL;
	//Len guarda el size de la lista
	len = ll_len(this);

	//Si la lista no es nula, si el nodo a verificar no es menor a 0, si el nodo a verificar
	if (this != NULL && nodeIndex >= 0 && nodeIndex <= len) {
		if (nodeIndex == 0) {
			//Si el nodo es 0 buscamos en el nodo de la linkedlist
			siguienteNodo = this->pFirstNode;
		} else {
			siguienteNodo = this->pFirstNode;

			for (i = 0; i < nodeIndex; i++) {
				//Buscamos el nodo hasta el index (aca vamos a pasar -1 ya que nos interesa el nodo previo, ya que ese contiene la ubicacion en memoria)
				siguienteNodo = siguienteNodo->pNextNode;
			}

		}

	}

	return siguienteNodo;

}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList *this, int nodeIndex) {
	return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList *this, int nodeIndex, void *pElement) {
	int returnAux = -1;
	int len;

	struct Node *nuevoNodo = NULL;
	struct Node *nodoAnterior = NULL;

	len = ll_len(this);

	//Si la verificacion es correcta procedemos a crear un nuevo nodo
	if (this != NULL && nodeIndex >= 0 && nodeIndex <= len) {
		//Asignamos el espacio de memoria al nodo
		nuevoNodo = (Node*) malloc(sizeof(Node));

		//Verificamos que el nodo se haya podido crear
		if (nuevoNodo != NULL) {
			//Si se pudo crear el nodo, asignamos el elemento a ese nodo
			nuevoNodo->pElement = pElement;
			//Aumentamos el tamaño de la linkedlist +1
			//this->size++;
			//this->size = this->size + 1;
			//Chequeamos que si el index es el primero es decir el 0 (significa que no existen nodos y este el primer nodo de la cadena)
			if (nodeIndex == 0) {

				//Asignamos lo que tenia el otro nodo en la siguiente posicion y lo establecemos en el nuevo nodo
				nuevoNodo->pNextNode = this->pFirstNode;
				//Asignamos la posicion del nuevo nodo al la linked list
				this->pFirstNode = nuevoNodo;
				//Aumentamos el tamaño de la linkedlist +1
				this->size = this->size + 1;

				returnAux = 0;
			} else

			{

				nodoAnterior = (Node*) malloc(sizeof(Node));

				if (nodoAnterior != NULL) {
					//Obtenemos la posicion de index del nodo(para eso restamos -1 ya que para buscarlo necesitamos el index anterior)
					nodoAnterior = getNode(this, nodeIndex - 1);
					//Asignamos lo que tenia el otro nodo en la siguiente posicion y lo establecemos en el nuevo nodo
					nuevoNodo->pNextNode = nodoAnterior->pNextNode;
					//Asignamos la posicion del nuevo nodo al nodo anterior
					nodoAnterior->pNextNode = nuevoNodo;
					//Aumentamos el tamaño de la linkedlist +1
					this->size = this->size + 1;

					returnAux = 0;
				}
			}
		}
	}
	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList *this, int nodeIndex, void *pElement) {
	return addNode(this, nodeIndex, pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList *this, void *pElement) {
	int returnAux = -1;
	int len;

	//Preguntar sobre esta funcion: Que es a lo que se refiere si agregar un Nodo con un elemento o un elemento a un determinado nodo.
	if (this != NULL) {
		len = ll_len(this);

		//Agregamos el nodo con el elemento
		returnAux = addNode(this, len, pElement);

	}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList *this, int index) {
	//Tengo que recibir un index, buscar el nodo y retornar el elemento de ese nodo

	void *returnAux = NULL;
	int len = ll_len(this);
	struct Node *nodoAux;

	//Si la lista existe, si el index esta dentro del rango, tanto igual o superior a 0 y menor a LEN
	if (this != NULL && index >= 0 && index <= len) {
		//Buscamos el nodo y lo asignamos al nodo auxiliar, no restamos en este caso porque queremos el elemento de determinado nodo
		nodoAux = getNode(this, index);
		if (nodoAux != NULL) {
			//Si el nodo existe entonces traeme el elemento
			returnAux = nodoAux->pElement;

		}

	}

	return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList *this, int index, void *pElement) {
	//Tengo que modificar un nodo, para eso tengo que utilizar lo que devuelva get, y asignarlo.
	int returnAux = -1;
	struct Node *nodoIndex;
	int len = ll_len(this);
	if (this != NULL && index <= len && index >= 0) {
		nodoIndex = getNode(this, index);

		if (nodoIndex != NULL) {
			nodoIndex->pElement = pElement;
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList *this, int index) {
	//Tenemos que remover el nodo, para esto voy a necesitar un nodo auxiliar para realizar el anexo
	//Armarme un esquema de vagones
	int returnAux = -1;
	int len;

	struct Node *nodoIndex = NULL;
	struct Node *nodoAnterior = NULL;

	len = ll_len(this);

	//Si la verificacion es correcta procedemos a crear un nuevo nodo
	if (this != NULL && index >= 0 && index <= len) {
		//Asignamos el espacio de memoria al nodo
		nodoIndex = (Node*) malloc(sizeof(Node));
		nodoAnterior = (Node*) malloc(sizeof(Node));

		nodoIndex = getNode(this, index);
		nodoAnterior = getNode(this, index - 1);
		//Verificamos que el nodo se haya podido crear
		if (nodoIndex != NULL) {

			if (index == 0) {
				//Le indicamos a la linkedlist que empiece por la ubicacion del nodo 1 en vez del 0.
				this->pFirstNode = nodoIndex->pNextNode;
				//el node size lo hago aca por estar seguro de no romper nada
				this->size--;
				returnAux = 0;
			} else

			{

				nodoAnterior = (Node*) malloc(sizeof(Node));

				if (nodoAnterior != NULL) {

					nodoAnterior = getNode(this, index - 1);

					//Asignamos lo que tenia el otro nodo en la siguiente posicion y lo establecemos en el nuevo nodo
					nodoAnterior->pNextNode = nodoIndex->pNextNode;
					//Aumentamos el tamaño de la linkedlist +1
					this->size--;

					returnAux = 0;
				}
			}
		}
	}
	return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList *this) {
	int returnAux = -1;
	int len;
	int i;
	len = ll_len(this);

	if (this != NULL)
	{
		for (i = 0; i < len; i++)
		{
			ll_remove(this, i);

		}
      returnAux = 0;
      //free(this);
	}

	return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList *this) {
	int returnAux = -1;


	if (this != NULL)
	{
		ll_clear(this);
		free(this);
		returnAux = 0;
	}
	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList *this, void *pElement) {
	int returnAux = -1;

	int i;
	int len = ll_len(this);
	struct Node* nodoAuxiliar = NULL;

	nodoAuxiliar = (Node*) malloc (sizeof(Node));
	if (this != NULL && nodoAuxiliar != NULL)
	{

		for(i = 0; i < len; i++)
		 {
			nodoAuxiliar = getNode(this, i);

			if(nodoAuxiliar->pElement == pElement)
			{
				returnAux = i;
				break;
			}

		}
	}


	return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si la lista NO esta vacia
 ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList *this) {
	int returnAux = -1;
    int len = ll_len(this);

    if(this != NULL)
    {
    	if(len == 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
	return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList *this, int index, void *pElement) {
	int returnAux = -1;
	int len = ll_len(this);

	if(this !=NULL && index >= 0 && index >= len )
	{
         returnAux = addNode(this, index, pElement);
	}
	return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList *this, int index) {
	void *returnAux = NULL;
	int len = ll_len(this);


	//Acordarse que no puedo borrar un elemento que exceda el tamaño de len
	if(this !=NULL && index >= 0 && index < len )
		{
		//Necesito obtener el elemento, para eso voy a necesitar el get.
	         returnAux = ll_get(this, index);
	         ll_remove(this, index);

		}



	return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 1) Si contiene el elemento
 ( 0) si No contiene el elemento
 */
int ll_contains(LinkedList *this, void *pElement) {
	int returnAux = -1;
	int checker;



	if(this != NULL )
	{
		//Mediante el indexOf comparamos si el elemento coincide con algun valor
		checker = ll_indexOf(this, pElement);

		if(checker > -1)
		{
			returnAux = 1;
		}
		else
		{
			returnAux = 0;
		}

	}





	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
 estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
 ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
 ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
 */
int ll_containsAll(LinkedList *this, LinkedList *this2) {


	/* Contains all verifica lo que esta en contains pero a nivel de la lista
	 * tengo que crear dos items para guardar los resultados de las variables get
	 * y contains, para poder hacer la comparación. Voy a necesitar un for para
	 * poder recorrer toda la lista	 */

	int returnAux = -1;
	int len;
	int i;
	//Para obtener un elemento, vamos a necesitar una variable en formato void.
	void* aux;
	int aux2;
	len = ll_len(this2);

	if(this != NULL && this2 != NULL)
	{
		//Si ninguna es NULL tiene que retornar 0
		returnAux = 0;
		for(i = 0; i < len; i++)
		{
			//obtenemos el elemento de la lista 2
			aux = ll_get(this2, i);
			//comparamos si existe en la lista 1
			aux2 = ll_contains(this, aux);
			//si existe
				if(aux2 == 0)
				{
                  //Agregamos un break para que no recorra toda la lista, si ya existe una comparacion que no existe, debe salir y stopear el for.
					break;
				}
				else
				{
					returnAux = 1;

				}

		}
	}

	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 o (si el indice from es menor a 0 o mayor al len de la lista)
 o (si el indice to es menor o igual a from o mayor al len de la lista)
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_subList(LinkedList *this, int from, int to) {

	/*Lo que necesito hacer aca es indicar desde que index a que index quiero y generar en base a eso una lista nueva
	 * 1 generar sub listalista
	 * 2 for para recorrer la lista original
	 * 4 tengo que crear nuevos nodos para esa lista
	 * 3 copiar a medidad que vaya pasando por los index los elemento a la sublista*/
	LinkedList *cloneArray = NULL;
	int i;
	void* aux;
	int len;


	len = ll_len(this);
	if(this != NULL && to <= len && from < to && from >=0 )
	{

		cloneArray = ll_newLinkedList();

		if(cloneArray != NULL)
		{
			for(i = from; i < to; i++)
			{
				aux = ll_get(this, i);
				//Chequeamos que el elemento no sea nulo, ya que ll get puede traer un error de nulidad
				if(aux != NULL)
				{
					addNode(cloneArray, i, aux );
				}


			}
		}
	}


	return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList *this) {
	LinkedList *cloneArray = NULL;

	int len;

	len = ll_len(this);

	if(this != NULL )
		{
          cloneArray = ll_newLinkedList();

          	  if(cloneArray != NULL)
          	  	  {
          		  	 cloneArray= ll_subList(this, 0, len);
          	  	  }
		}

	return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 ( 0) Si ok
 */
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order) {
	int returnAux = -1;

	/*Tengo que ordenar ascendente y descendente la lista. Me pasan dos criterios y el tipo de orden que tienen que tener
	 * 2 For I y J
	 * 1 Auxiliar ( para copiar y poder ordenar el nodo
	 * 2 Variables para nodos (para comparar i y J)
	 * Tengo la logica en la cabeza de esta funcion pero no entiendo bien y tengo dudas sobre que tiene que hacer en si el pFunc.
	 * */
	return returnAux;

}

