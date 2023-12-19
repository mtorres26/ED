/**
 * @brief Constructor. Genera un sudoku killer de 9x9 casillas.
 */
SudokuKiller();

/**
 * @brief Constructor de copia. 
 * @param sk un objeto sudoku killer
 */
SudokuKiller(const SudokuKiller & sk);

/**
 * @brief Devuelve la/s posicion/es con las que debe de formar una suma la posición pasada por parámetro
 * @param index entero correspondiente a la posicion de la cual queramos saber lo mencionado en la descripcion
 * @return vector<int> con la posicion o posiciones mencionadas en la descripcion.
 */
const vector<int> obtenerPosicionesDeSumaRelativas(int index) const;

/**
 * @brief Devuelve las posiciones con las que se deben formar sumas
 * @return un list<vector<int>> donde cada posicion de la lista es un vector con las posiciones relacionadas entre si
 */
const list<vector<int>> obtenerPosicionesDeSumaGenerales() const;

/**
 * @brief Devuelve la suma asociada a la posicion pasada por parámetro.
 * @param index entero correspondiente a la posicion de la cual queramos saber su suma asociada.
 * @return int entero correspondiente al valor de la suma asociada a index.
 */
int obtenerSumaAsociada(int index) const;

/**
 * @brief Comprueba si el valor que contiene la posicion pasada por parametro es correcto.
 * @param index entero que corresponde con la posicion cuyo valor queremos saber si es correcto.
 * @return true si el valor contenido es correcto,
 *         false si el valor contenido es incorrecto.
 */
bool comprobarPosicion(int index) const;

/**
 * @brief Comprueba si nuestro sudoku es igual al de la solucion
 * @param sk nuestro objeto sudoku killer
 * @return true si los dos sudokus son iguales,
 *         false si no lo son.
 */
bool comprobarSolucion(const SudokuKiller & sk) const;

/**
 * @brief Modifica el valor de la posicion indicada
 * @param index posicion de nuestro sudoku que queremos modificar
 * @param valor valor que queremos asignarle a la posicion
 */
void setValor(int valor, int index);