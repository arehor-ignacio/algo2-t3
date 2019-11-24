
#include "string_map.h"

template <typename T>
string_map<T>::string_map() : _raiz(nullptr), _keys(std::set<string>()){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for (string key : d._keys) {
        T def = d.at(key);
        (*this)[key] = def;
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    eliminarNodo(this->_raiz);
}

template <typename T>
void string_map<T>::eliminarNodo(string_map::Nodo* nodoTrie) {
    if (nodoTrie != nullptr) {
        for (int i = 0; i < SIGUIENTES_SIZE; ++i) {
            eliminarNodo(nodoTrie->siguientes[i]);
        }
        delete nodoTrie->definicion;
        delete nodoTrie;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if (this->_raiz == nullptr) {
        this->_raiz = new Nodo();
    }
    struct Nodo* nodoTrie = this->_raiz;

    for (int i = 0; i < clave.size(); ++i) {
        if (nodoTrie->siguientes[clave[i]] == nullptr) {
            nodoTrie->siguientes[clave[i]] = new Nodo();
        }
        nodoTrie = nodoTrie->siguientes[clave[i]];
    }

    this->_keys.insert(clave);
    nodoTrie->esFinDePalabra = true;
    return *(nodoTrie->definicion);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& entrada) {
    (*this)[std::get<0>(entrada)] = std::get<1>(entrada);
    this->_keys.insert(std::get<0>(entrada));
}

template <typename T>
int string_map<T>::count(const string& clave) const {
    return this->_keys.count(clave);
}
/*  struct Nodo* nodoTrie = this->_raiz;

    int i = 0;
    while (i < clave.size() && nodoTrie != nullptr){
        nodoTrie = nodoTrie->siguientes.at(clave[i]);
        ++i;
    }
    return (i == clave.size() ? 1 : 0);
}*/

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    struct Nodo* nodoTrie = this->_raiz;

    for (int i = 0; i < clave.size(); ++i) {
        nodoTrie = nodoTrie->siguientes[clave[i]];
    }
    return *(nodoTrie->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    struct Nodo* nodoTrie = this->_raiz;

    for (int i = 0; i < clave.size(); ++i) {
        nodoTrie = nodoTrie->siguientes[clave[i]];
    }
    return *(nodoTrie->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    this->_keys.erase(clave);
    this->_raiz = removerNodo(this->_raiz, clave,0);
}

template<typename T>
typename string_map<T>::Nodo* string_map<T>::removerNodo(string_map::Nodo*& nodoTrie, const string& clave, int index) {
    if (index == clave.size()) {
        if ((*nodoTrie).esHoja()) {
            delete nodoTrie->definicion;
            delete nodoTrie;
            return nullptr;
        } else {
            //delete nodoTrie->definicion;
            nodoTrie->esFinDePalabra = false;
            return nodoTrie;
        }
    } else {
        nodoTrie->siguientes[clave[index]] = removerNodo(nodoTrie->siguientes[clave[index]], clave, index+1);
        if (!nodoTrie->esFinDePalabra && nodoTrie->esHoja()){
            delete nodoTrie->definicion;
            delete nodoTrie;
            return nullptr;
        } else return nodoTrie;
    }
}

template <typename T>
int string_map<T>::size() const{
    return this->_keys.size();
}

template <typename T>
bool string_map<T>::empty() const{
    return this->_keys.empty();
}