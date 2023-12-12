Pais::Pais() {
    this.p = Punto();
    this.pais = "";
    this.bandera = "";
}

Punto Pais::GetPunto() const {

}

string Pais::GetPais() const {

}

string Pais::GetBandera() const {

}

bool Pais::operator<(const Pais &P) const{

}

bool Pais::operator==(const Pais &P) const{

}

bool Pais::operator==(const Punto &P) const{

}

friend istream &operator>>(istream &is, Pais &P) {
    double lat, lng;

    is >> lat >> lng >> P.pais >> P.bandera;

    P.p = Punto(lat, lng, "");
    return is;
}

friend ostream &operator<<(ostream &os, const Pais &P) {
    os << P.p << " " << P.pais << " " << P.bandera << endl;
    return os;
}