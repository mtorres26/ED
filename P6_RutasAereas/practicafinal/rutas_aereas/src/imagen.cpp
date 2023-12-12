/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>
#include <imagen.h>
#include <imagenES.h>


using namespace std;

/********************************
       FUNCIONES PÚBLICAS
********************************/

Imagen::Imagen() {
    this->nf = 0;
    this->nc = 0;
    this->data = nullptr;
}

// Constructor por defecto
Imagen::Imagen(int f, int c) {
    this->nf = f;
    this->nc = c;
    this->data = new Pixel *[nf];
    for (int i = 0; i < nf; i++) {
        this->data[i] = new Pixel[nc];
        for (int j = 0; j < nc; j++) {
            this->data[i][j].r = 255;
            this->data[i][j].g = 255;
            this->data[i][j].b = 255;
            this->data[i][j].transp = 255;
        }
    }
}

// Constructor de copia
Imagen::Imagen(const Imagen &I) {
    Copiar(I);
}

Imagen::~Imagen() {
    Borrar();
}

void Imagen::Borrar() {
    if (this != nullptr) {
        for (int i = 0; i < this->nf; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr; // Necesario??
    }
}

void Imagen::Copiar(const Imagen &I) {
    if (this != &I) {
        this->nf = I.GetFilas();
        this->nc = I.GetCols();
        this->data = new Pixel *[nf];
        for (int i = 0; i < this->nf; i++) {
            this->data[i] = new Pixel[nc];
        }
        for (int i = 0; i < nf; i++) {
            for (int j = 0; j < nc; j++) {
                this->data[i][j] = I(i, j);
            }
        }
    }
}

// Operador de Asignación
Imagen &Imagen::operator=(const Imagen &orig) {
    if (this != &orig) {
        Borrar();
        Copiar(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase
int Imagen::GetFilas() const {
    return this->nf;
}

int Imagen::GetCols() const {
    return this->nc;
}

const Pixel &Imagen::operator()(int i, int j) const {
    assert(i >= 0 && i < nf && j >= 0 && j < nc);
    return this->data[i][j];
}

Pixel &Imagen::operator()(int i, int j) {
    assert(i >= 0 && i < nf && j >= 0 && j < nc);
    return this->data[i][j];
}

int Imagen::size() const {
    return GetFilas() * GetCols();
}

void Imagen::EscribirImagen(const char *nombre) {
    unsigned char *componentes_pixel = new unsigned char[nf * nc * 3];
    unsigned char *pixeles_pgm = new unsigned char[nf * nc];

    int total = nf * nc * 3;
    for (int i = 0; i < total; i += 3) {
        int posi = i / (nc * 3);
        int posj = (i % (nc * 3)) / 3;

        componentes_pixel[i] = this->data[posi][posj].r;
        componentes_pixel[i + 1] = this->data[posi][posj].g;
        componentes_pixel[i + 2] = this->data[posi][posj].b;
        pixeles_pgm[i / 3] = this->data[posi][posj].transp;
    }

    if (!EscribirImagenPPM(nombre, componentes_pixel, nf, nc)) {
        cerr << "Ha habido un problema en la escritura de " << nombre << endl;
    }
    delete[] componentes_pixel;
    string n_aux = "mascara_";
    n_aux = n_aux + nombre;
    std::size_t found = n_aux.find(".ppm");
    if (found != std::string::npos) {
        n_aux = n_aux.substr(0, found);
    }
    n_aux = n_aux + ".pgm";

    if (!EscribirImagenPGM(n_aux.c_str(), pixeles_pgm, nf, nc)) {
        cerr << "Ha habido un problema en la escritura de " << n_aux << endl;
    }
    delete[] pixeles_pgm;
}

void Imagen::LeerImagen(const char *nombre, const string &nombremascara) {
    int f, c;
    unsigned char *aux, *aux_mask;

    LeerTipoImagen(nombre, f, c);
    aux = new unsigned char[f * c * 3];
    LeerImagenPPM(nombre, f, c, aux);
    if (nombremascara != "") {
        int fm, cm;
        LeerTipoImagen(nombremascara.c_str(), fm, cm);
        aux_mask = new unsigned char[fm * cm];
        LeerImagenPGM(nombremascara.c_str(), fm, cm, aux_mask);
    } else {
        aux_mask = 0;
    }

    Imagen I(f, c);
    int total = f * c * 3;
    for (int i = 0; i < total; i += 3) {
        int posi = i / (c * 3);
        int posj = (i % (c * 3)) / 3;
        //   cout<<posi<<" " <<posj<<endl;
        I(posi, posj).r = aux[i];                   // Accede directamente al r del struct Pixel?
        I(posi, posj).g = aux[i + 1];
        I(posi, posj).b = aux[i + 2];

        if (aux_mask != 0) {
            I(posi, posj).transp = aux_mask[i / 3];
        } else {
            I(posi, posj).transp = 255;
        }
    }

    *this = I;
    if (aux_mask != 0) delete[]aux_mask;
    delete[]aux;
}

void Imagen::PutImagen(int posi, int posj, const Imagen &I, Tipo_Pegado tippegado) {
    //assert(nf>=posi+I.nf && nc>=posj+I.nc);
    for (int i = 0; i < I.GetFilas(); i++)
        for (int j = 0; j < I.GetCols(); j++)
            if (i + posi >= 0 && i + posi < nf && j + posj >= 0 && j + posj < nc) {
                if (I(i, j).transp != 0) {
                    if (tippegado == OPACO)
                        data[i + posi][j + posj] = I(i, j);
                    else {
                        data[i + posi][j + posj].r = (data[i + posi][j + posj].r + I(i, j).r) / 2;
                        data[i + posi][j + posj].g = (data[i + posi][j + posj].r + I(i, j).g) / 2;
                        data[i + posi][j + posj].b = (data[i + posi][j + posj].r + I(i, j).b) / 2;
                    }
                }
            }
}

void Imagen::LimpiarTransp() {
    for (int i = 0; i < this->nf; i++) {
        for (int j = 0; j < this->nc; j++) {
            this->data[i][j].transp = 0;
        }
    }
}

/*
Imagen Imagen::ExtraeImagen(int posi, int posj, int dimi, int dimj) {

}
*/