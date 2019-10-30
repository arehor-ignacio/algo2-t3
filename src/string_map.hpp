template <typename T>
string_map<T>::string_map() : _size(0), raiz(nullptr){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    struct Nodo* n = raiz;
    for (int i = 0; i < clave.size(); i++) {
        if ((n->siguientes).at(clave[i]) == nullptr) {
            (n->siguientes).at(clave[i]) = new Nodo();
            _size++;
            (n->hijos)++;
        }
        n = (n->siguientes).at(clave[i]);
    }
    return n->definicion;
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    int i = 0;
    struct Nodo* n = raiz;

    while (i < clave.size() && ((n->siguientes).at(clave[i]) != nullptr) {
        n = (n->siguiente).at(clave[i]);
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
        n = (n->siguiente).at(clave[i]);
        i++;
    }
    return n->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    struct Nodo* n = raiz;
    
    for (int i = 0; i < clave.size(); i++) n = (n->siguiente).at(clave[i]); 
    
    return n->definicion;
}


struct Nodo* remove(struct Nodo* trieNode, const string& key, int index) {
    struct Nodo* raiz;

    if (index == key.size()) {
        if (trieNode->hijos == 0) {
            delete trieNode;
            raiz = nullptr;
        }
        else {
            trieNode->definicion = nullptr;
            raiz = trieNode;
        }
    }
    else {
       struct Node* nextNode = (trieNode->siguientes).at(key[i]);
       nextNode = remove(nextNode, key, ++index);
       raiz = nextNode;
    }
    return raiz; 
}

int remove(struct Nodo* trieNode, const string& key, int index) {
    int nodosBorrados = 0;
    if (index == key.size()) {
        if (trieNode->hijos == 0) {
            delete trieNode;
            nodosBorrados = 1;
        }
        else {
            nodosBorrados = 0;
        }
    }
    else {
        
    }
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    /*struct Nodo* n = raiz;
    struct Nodo* u = raiz;
    int j = 0;
    for (int i = 0; i < clave.size(); i++) {
        if ( (n->hijos > 1 ) || (n->definicion != nullptr) ) {
            u = n;
            j = i;
        }
        n = (n->siguiente).at(clave[i]);
    }
    
    struct Nodo* actual = (u->siguientes).at(clave[j]);
    (u->siguiente).at(clave[j]) = nullptr;
    u.hijos--;
    j++;
    while (j < clave.size()) {
        struct Nodo* t = actual;
        actual = (actual->siguientes).at(clave[j]);
        delete actual;
        j++;
    }
    _size--;

    




    while (u != n && j < clave.size()) {
        struct Nodo* elim = (u->siguientes).at(clave[j]);
        (u->siguientes).at(clave[j]) = nullptr;
        u = elim;
        j++; 
    }
    while (u' != n && j < clave.size()) {
        struct Nodo* t = u';
        u = (u->siguientes).at(clave[j]);
        delete t;
        j++;
    }*/
    raiz = borrarR(0, clave, raiz);
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}
