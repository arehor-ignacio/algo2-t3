template <typename T>
typename string_map<T>::Nodo* _remove(struct Nodo* trieNode, const string& key, int index) {
    void* res;
    if (index == key.size()) {
        if (trieNode->hijos == 0) {
            delete trieNode;
            res = nullptr;
        }
        else {
            trieNode->definicion = nullptr;
            res = trieNode;
        }
    }
    else {
       struct Node* nextNode = (trieNode->siguientes).at(key[index]);
       nextNode = _remove(nextNode, key, ++index);
       if (nextNode == nullptr) {
            nextNode.hijos--;
       }
       res = nextNode;
    }
    return res; 
}
template <typename T>
string_map<T>::string_map() : raiz(nullptr), _keys(std::set<string>()){
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
    struct Nodo* n = raiz;
    bool updt = false;
    for (int i = 0; i < clave.size(); i++) {
        if ((n->siguientes).at(clave[i]) == nullptr) {
            (n->siguientes).at(clave[i]) = new Nodo();
            (n->hijos)++;
            updt = true;
        }
        n = (n->siguientes).at(clave[i]);
    }
    if (updt) {
        _keys.insert(clave);
    }
    return *(n->definicion);
}


template <typename T>
int string_map<T>::count(const string& clave) const {
    int i = 0;
    struct Nodo* n = raiz;

    while (i < clave.size() &&
        ((n->siguientes).at(clave[i]) != nullptr)) {
        n = (n->siguientes).at(clave[i]);
        i++;
    }
    return ((n->definicion) != nullptr ? 1 : 0);
}

// Pre {def?(c, d) = 1}
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
    (*this)[std::get<0>(value_type)] = std::get<1>(value_type);
}
