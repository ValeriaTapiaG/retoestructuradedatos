#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;


class BitacoraLinea {
public:
  
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


vector<BitacoraLinea> read_csv_bitacora(const string& filename) {
    vector<BitacoraLinea> bitacora; 
    ifstream file(filename);

    
    if (!file.is_open()) {
        throw runtime_error("No se puede abrir el archivo");
    }

    string linea;


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


        for (const BitacoraLinea& linea : bitacora) {
            cout << "Fecha: " << linea.getFecha() << ", Hora: " << linea.getHora() << endl;
          
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
