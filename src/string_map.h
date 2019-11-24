#ifndef STRING_MAP_H_
#define STRING_MAP_H_
#define SIGUIENTES_SIZE 256

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo() : definicion(nullptr) {
            for (int i = 0; i < 256; i++) siguientes[i] = nullptr;
        };
    };

    std::set<string> _keys;
    struct Nodo* raiz;

    bool esHoja(struct Nodo* nodo) {
        int i = 0;
        while ((i < nodo->siguientes.size()) && (nodo->siguientes[i] != nullptr)) ++i;
        return i == nodo->siguientes.size();
    }
    string_map<T>::Nodo* _remove(struct Nodo* trieNode, const string& key, int index) {
        struct Nodo* res;
        if (index == key.size()) {
            if (esHoja(trieNode)) {
                delete trieNode;
                res = nullptr;
            }
            else {
                trieNode->definicion = nullptr;
                res = trieNode;
            }
        }
        else {
           struct Nodo** ptrNodoSiguiente = &(trieNode->siguientes).at(key[index]);
           (*ptrNodoSiguiente) = _remove(*ptrNodoSiguiente, key, ++index);
           res = *ptrNodoSiguiente;
        }
        return res;
    }

};

#include "string_map.hpp"

#endif // STRING_MAP_H_
