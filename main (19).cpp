#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string> // Include this header for string manipulation

using namespace std;

class Fecha {
public:
    Fecha(int year, int month, int day) : year(year), month(month), day(day) {}

    // Getters for year, month, and day
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    // Comparison operators for Fecha objects
    bool operator<(const Fecha& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator>(const Fecha& other) const {
        return other < *this;
    }

    bool operator<=(const Fecha& other) const {
        return !(other < *this);
    }

    bool operator>=(const Fecha& other) const {
        return !(*this < other);
    }

    bool operator==(const Fecha& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

private:
    int year;
    int month;
    int day;
};

class BitacoraLinea {
public:
    // Constructor predeterminado sin argumentos
    BitacoraLinea() = default;

    BitacoraLinea(const string& fecha, const string& hora, const string& ipOrigen,
                  int puertoOrigen, const string& nombreOrigen, const string& ipDestino,
                  int puertoDestino, const string& nombreDestino)
        : fecha(fecha), hora(hora), ipOrigen(ipOrigen), puertoOrigen(puertoOrigen),
          nombreOrigen(nombreOrigen), ipDestino(ipDestino), puertoDestino(puertoDestino),
          nombreDestino(nombreDestino) {
    }

    // Métodos para obtener los campos de la línea de bitácora
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    string getIPOrigen() const { return ipOrigen; }
    int getPuertoOrigen() const { return puertoOrigen; }
    string getNombreOrigen() const { return nombreOrigen; }
    string getIPDestino() const { return ipDestino; }
    int getPuertoDestino() const { return puertoDestino; }
    string getNombreDestino() const { return nombreDestino; }

private:
    string fecha;
    string hora;
    string ipOrigen;
    int puertoOrigen;
    string nombreOrigen;
    string ipDestino;
    int puertoDestino;
    string nombreDestino;
};

// Forward declaration of parseFecha
Fecha parseFecha(const string& fechaStr);

template <class T>
class Ordenamiento {
public:
    static vector<T> insercion(vector<T> e, bool (*compara)(T, T)) {
        T index;

        int n = (int)e.size();

        for (int i = 1; i < n; i++) {
            index = e[i];

            int j = i - 1;

            while (j >= 0 && compara(index, e[j])) {
                e[j + 1] = e[j];
                j--;
            }

            e[j + 1] = index;
        }

        return e;
    }
};

// Función de comparación para ordenar BitacoraLinea por fecha
bool comparaPorFecha(BitacoraLinea a, BitacoraLinea b) {
    Fecha fechaA(parseFecha(a.getFecha()));
    Fecha fechaB(parseFecha(b.getFecha()));
    return fechaA < fechaB;
}

// Definition of parseFecha function
Fecha parseFecha(const string& fechaStr) {
    int year, month, day;
    char dash;
    stringstream ss(fechaStr);
    ss >> year >> dash >> month >> dash >> day;
    return Fecha(year, month, day);
}

vector<BitacoraLinea> read_csv_bitacora(const string& filename) {
    vector<BitacoraLinea> bitacora;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("No se puede abrir el archivo");
    }

    string linea;
    // registroCount = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string fecha, hora, ipOrigen, nombreOrigen, ipDestino, nombreDestino;
        int puertoOrigen, puertoDestino;

        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, ipOrigen, ',');
        ss >> puertoOrigen;
        ss.ignore();
        getline(ss, nombreOrigen, ',');
        getline(ss, ipDestino, ',');
        ss >> puertoDestino;
        ss.ignore();
        getline(ss, nombreDestino, ',');

        bitacora.emplace_back(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino);
     
    }

    file.close();

    return bitacora;
}

int main() {
    string filename = "equipo13.csv";
    try {
        vector<BitacoraLinea> bitacora = read_csv_bitacora(filename);

        // Ordena el vector de bitácora por fecha utilizando la función de ordenamiento
        bitacora = Ordenamiento<BitacoraLinea>::insercion(bitacora, comparaPorFecha);

        for (const BitacoraLinea& linea : bitacora) {
            cout << "Fecha: " << linea.getFecha() << ", Hora: " << linea.getHora() << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
