
#include "string_map.h"

template <typename T>
string_map<T>::string_map() : _raiz(nullptr), _keys(std::set<string>()){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    std::set<string>::const_iterator it = d._keys.begin();
    std::set<string>::const_iterator itEnd = d._keys.end();
    while (it != itEnd) {
        T elem = d.at(*it);
        (*this)[*it] = elem;
        it++;
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    std::set<string>::iterator it = this->_keys.begin();
    std::set<string>::iterator itEnd = this->_keys.end();

    while (it != itEnd) {           // Se indefine?
        this->raiz = _remove(this->raiz, *it, 0);
        it = this->_keys.erase(it);
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    struct Nodo* ptrDirSigNodo = this->raiz;
    // bool updt = false;

    for (int i = 0; i < clave.size(); i++) {
        if (*ptrDirSigNodo == nullptr) {
            *ptrDirSigNodo = new Nodo();
        }

        ptrDirSigNodo = &((*ptrDirSigNodo)->siguientes.at(clave[i]));
    }
    return *((*ptrDirSigNodo)->definicion);

    // for (int i = 0; i < clave.size(); i++) {
    //     if ((n->siguientes).at(clave[i]) == nullptr) {
    //         (n->siguientes).at(clave[i]) = new Nodo();
    //         updt = true;
    //     }
    //     n = (n->siguientes).at(clave[i]);
    // }
    // if (updt) {
    //     _keys.insert(clave);
    // }
    // return *(n->definicion);
}


template <typename T>
int string_map<T>::count(const string& clave) const {
    int i = 0;
    struct Nodo* n = this->raiz;

    while (i < clave.size() && n != nullptr) {
        n = (n->siguientes).at(clave[i]);
        i++;
    }
    return 0;
}

// Pre { def?(c, d) }
template <typename T>
const T& string_map<T>::at(const string& clave) const {
    int i = 0;
    struct Nodo* n = raiz;
    
    while (i < clave.size()) {
        n = (n->siguientes).at(clave[i]);
        i++;
    }
    return *(n->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    struct Nodo* n = raiz;
    
    for (int i = 0; i < clave.size(); i++) n = (n->siguientes).at(clave[i]);
    return *(n->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    raiz = _remove(raiz, clave, 0);
    _keys.erase(clave);
}

template <typename T>
int string_map<T>::size() const{
    return this->_keys.size();
}

template <typename T>
bool string_map<T>::empty() const{
    return this->_keys.empty();
}
template<typename T>
void string_map<T>::insert(const pair<string, T>& value_type) {
    struct Nodo* ptrDirSigNodo = this->raiz;
    std::string clave = std::get<0>(value_type);
    T significado = std::get<1>(value_type);

    for (int i = 0; i < clave.size(); i++) {
        if (ptrDirSigNodo == nullptr) {
            ptrDirSigNodo = new Nodo();
        }
        
        ptrDirSigNodo = &((*ptrDirSigNodo)->siguientes.at(clave[i]));
    }

    (*ptrDirSigNodo)->definicion = &(significado);
    this->_keys.insert(std::get<0>(value_type));
}
