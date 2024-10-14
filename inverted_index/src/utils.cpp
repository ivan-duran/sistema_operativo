#include "utils.h"

#include <iostream>
#include <unistd.h> 
#include <filesystem> 

using namespace std ;

/**
 * @brief Muestra el menú de opciones disponibles para el usuario.
 * 
 * Muestra el menú de opciones disponibles para el usuario.
 */
void showMenu(){
    pid_t pid = getpid();
    cout << "Creacion de inverted index" << endl;
    cout << "-----------------------------------" << endl;
    cout << "PID: " << pid << endl;
    cout << endl <<"Creando indice invertido..."<<endl;
    cout << "-----------------------------------" << endl;
}

/**
 * @brief Verifica si un directorio existe.
 * 
 * @param path Ruta del directorio a verificar.
 * @return true Si el directorio existe.
 * 
 * Verifica si un directorio existe.
 */
bool directoryExists(const string& path) {
    return __fs::filesystem::exists(path) && __fs::filesystem::is_directory(path);
}

/**
 * @brief Verifica si un directorio está vacío.
 * 
 * @param path Ruta del directorio a verificar.
 * @return true Si el directorio está vacío.
 * 
 * Verifica si un directorio está vacío.
 */
bool hasFilesWithExtension(const string& path, const string& exten) {
    for (const auto& entry : __fs::filesystem::directory_iterator(path)) {
        if (entry.path().extension().string() == exten) {
            return true;
        }
    }
    return false;
}

inverted_index(const string& path_inverted_index, const string& path_out, const string& extension){
    unordered_map<string, vector<pair<int,int>>> inverted_index;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(path_out)) {
        string pathArchivo = entry.path().string();
        string linea;
        if (entry.path().extension().string()== exten){
            ofstream archivo(pathArchivo);
            string id = entry.path().stem().string();
            while (getline(archivo, linea)) {
                size_t pos = linea.rfind(':');
                string palabra = linea.substr(0, pos);  // Parte antes del último :
                string cant = linea.substr(pos + 1);
                inverted_index[palabra].push_back(make_pair(stoi(id), stoi(cant)));
            }
            archivo.close();
        }
    }

    ofstream archivo(path_inverted_index);
    for (const auto& entry : inverted_index) {
        archivo << palabra << "; "
        string palabra = entry.first;
        for (const auto& id_cant : entry.second) {
            string id = to_string(id_cant.first);
            string cant = to_string(id_cant.second);
            archivo << "( " << id << ", " << cant <<");";
        }
        archivo << endl;
    }
    archivo.close();

}



