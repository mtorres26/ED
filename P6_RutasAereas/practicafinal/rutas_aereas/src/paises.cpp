class iterator {
private:
    set<Pais>::iterator p;

public:

    iterator begin();

    iterator end();

    friend class Paises;

    friend class const_iterator;
};

class const_iterator {
private:
    set<Pais>::const_iterator p;

public:
    const_iterator begin();

    const_iterator end();

    friend class Paises;

};

iterator iterator::begin() {
    iterator it;
    it.p = datos.begin();
    return it;
}

const_iterator const_iterator::begin() const {
    const_iterator it;
    it.p = datos.begin();
    return it;
}

iterator iterator::end() {
    iterator it;
    it.p = datos.end();
    return it;
}

const_iterator const_iterator::end() const {
    const_iterator it;
    it.p = datos.end();
    return it;
}

iterator find(const Pais &p) {
    iterator it;
    set<Pais>::iterator i;
    for (i = datos.begin(); i != datos.end() && !((*i) == p); ++i);
    it.p = i;
    return it;
}

iterator find(const Punto &p) {

}

friend istream &operator>>(istream &is, Paises &R) {
    Paises rlocal;
    //leemos el comentario
    if (is.peek() == '#') {
        string a;
        getline(is, a);
    }

    Pais P;
    while (is >> P) {
        rlocal.Insertar(P);

    }
    R = rlocal;
    return is;
}

friend ostream &operator<<(ostream &os, const Paises &R) {

    Paises::const_iterator it;
    for (it = R.begin(); it != R.end(); ++it) {
        os << *it << "\t";
    }
    return os;
}