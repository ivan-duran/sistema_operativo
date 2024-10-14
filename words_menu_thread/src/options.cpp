#include "options.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>

#include <thread>
#include <mutex>
#include <filesystem>
#include <unordered_map>
#include <set>
#include <unordered_set>


using namespace std;

/**
 * @brief Verifica si un texto es un palíndromo.
 * 
 * @param text Texto a verificar.
 * @return true Si el texto es un palíndromo.
 * @return false Si el texto no es un palíndromo.
 * 
 * Un palíndromo es una palabra o frase que se lee igual de izquierda a derecha que de derecha a izquierda.
*/
string readFile(const string& path) {
    ifstream archivo(path); 
    stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();
    
    return buffer.str();
}

/**
 * @brief Lee los archivos de una carpeta y los guarda en un vector.
 * 
 * @param carpetaPath Ruta de la carpeta a leer.
 * @param exten Extensión de los archivos a leer.
 * @return vector<pair<string, string
 * 
 * Lee los archivos de una carpeta y los guarda en un vector de pares, donde el primer elemento es el título del archivo y el segundo es el contenido.
 */    
vector<pair<string, string>> readFolder(const string& carpetaPath,string exten) {
    vector<pair<string, string>> todosLosArchivos;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(carpetaPath)) {
        string pathArchivo = entry.path().string();
        
        if (entry.path().extension().string()== exten){
            string titulo = entry.path().stem().string();
            string contenido = readFile(pathArchivo);
            todosLosArchivos.push_back(make_pair(titulo, contenido));
        }
    }
    return todosLosArchivos;
}

/**
 * @brief Cuenta la cantidad de palabras en un texto.
 * 
 * @param texto Texto a contar.
 * @return unordered_map<string, int> Mapa con las palabras y su cantidad.
 * 
 * Cuenta la cantidad de palabras en un texto y las guarda en un mapa.
 */
unordered_map<string, int> countWord(const string& texto) {
    unordered_map<string, int> conteoPalabras; 
    stringstream ss(texto);
    string palabra;
    
    while (ss >> palabra) {
        while (!palabra.empty() && !isalpha(palabra.back())) {
            palabra.pop_back();
        }
        while (!palabra.empty() && !isalpha(palabra.front())) {
            palabra.erase(palabra.begin()); 
        }
        for (char& c : palabra) {
            c = tolower(c);
        }
        
        if (!palabra.empty()) {
            conteoPalabras[palabra]++;
        }
    }
    return conteoPalabras;
}

/**
 * @brief Crea archivos con el conteo de palabras de un texto.
 * 
 * @param textos Vector de pares con el título y contenido de los textos.
 * @param path Ruta de la carpeta donde se guardarán los archivos.
 * @param exten Extensión de los archivos a crear.
 * @return vector<pair<string, int>> Vector de pares con la ruta de los archivos creados y la cantidad de palabras diferentes.
 * 
 * Crea archivos con el conteo de palabras de un texto y los guarda en una carpeta con la extensión especificada.
 */
vector<pair<string, int>> fileOut(const vector<pair<string, string>>& textos, const string& path, const string& exten) {
    vector<pair<string, int>> salida;
    for (const auto& texto : textos) {
        string titulo = texto.first;
        string contenido = texto.second;
    
        unordered_map<string, int> conteo = countWord(contenido);
        
        // Crear el archivo en la carpeta con la extensión especificada
        string archivoPath = path + "/" + titulo + exten;
        ofstream archivo(archivoPath);

        // Escribir el conteo de palabras en el archivo
        int diffWords = 0;
        for (const auto& par : conteo) {
            archivo << par.first << "; " << par.second << endl; 
            diffWords ++;
        }

      archivo.close(); 
        salida.push_back(make_pair(archivoPath, diffWords));
    }
    return salida;
}


//opcion 10    

mutex mtx;  // Para proteger la salida al archivo
set<string> stopWords;  // Set de palabras de parada

void countWordsInFile(const string& filepath, const string& outputDir) {
    ifstream file(filepath);
    unordered_map<string, int> wordCount;
    string word;

    // Leer y contar las palabras del archivo
    while (file >> word) {
        // Limpiar las palabras de parada (stop words)
        if (stopWords.find(word) == stopWords.end()) {
            wordCount[word]++;
        }
    }
    file.close();

    // Bloquear el acceso para escribir en los archivos de salida
    {
        lock_guard<mutex> guard(mtx);
        string outputFilename = outputDir + "/" + std::filesystem::path(filepath).filename().string();
        ofstream outFile(outputFilename);
        for (const auto& entry : wordCount) {
            outFile << entry.first << ": " << entry.second << endl;
        }
        outFile.close();
    }
}

void parallelWordCount() {
    // Obtener las variables de entorno
    string inputDir = getenv("CARPETA_ENTRADA");
    string outputDir = getenv("CARPETA_SALIDA");
    int maxThreads = stoi(getenv("CANTIDAD_THREAD"));
    string stopWordsPath = getenv("STOP_WORD");

    // Cargar las palabras de parada
    ifstream stopWordsFile(stopWordsPath);
    string stopWord;
    while (stopWordsFile >> stopWord) {
        stopWords.insert(stopWord);
    }
    stopWordsFile.close();

    // Vector para guardar los hilos
    vector<thread> threads;
    vector<string> filepaths;

    // Leer los archivos del directorio de entrada
    for (const auto& entry : filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file()) {
            filepaths.push_back(entry.path().string());
        }
    }

    // Crear los hilos para contar las palabras en los archivos
    for (int i = 0; i < filepaths.size(); ++i) {
        if (threads.size() >= maxThreads) {
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }
        threads.push_back(thread(countWordsInFile, filepaths[i], outputDir));
    }

    // Unir los hilos restantes
    for (auto& t : threads) {
        t.join();
    }

    cout << "Conteo paralelo con hilos completado." << endl;
        
}


void mapa_archivo(string& path_map, string& exten, string& path_in){
    int id = 0 ;
    ofstream archivo(path_map);
    for (const auto& entry : std::__fs::filesystem::directory_iterator(path_in)) {
        string pathArchivo = entry.path().string();
        
        if (entry.path().extension().string()== exten){
            string titulo = entry.path().stem().string();
            archivo << titulo << ", " << id<< endl; 
            id++;
        }
    }

}

//STOP_WORDS

/**
 * @brief Carga las palabras de parada desde un archivo en un conjunto (set).
 * 
 * @param stopWordsPath Ruta al archivo de palabras de parada.
 * @return unordered_set<string> Conjunto de palabras de parada.
 */
unordered_set<string> loadStopWords(const string& stopWordsPath) {
    unordered_set<string> stopWords;
    ifstream file(stopWordsPath);
    string word;
    
    // Leer cada palabra en el archivo de palabras de parada y almacenarlas en un conjunto
    while (file >> word) {
        stopWords.insert(word);
    }
    
    file.close();
    return stopWords;
}

/**
 * @brief Limpia el texto de las palabras de parada.
 * 
 * @param text El texto a limpiar.
 * @param stopWords El conjunto de palabras de parada.
 * @return string El texto limpio sin palabras de parada.
 */
string cleanTextFromStopWords(const string& text, const unordered_set<string>& stopWords) {
    stringstream ss(text);
    string word, result;

    // Iterar sobre cada palabra en el texto
    while (ss >> word) {
        // Si la palabra no es una palabra de parada, agregarla al resultado
        if (stopWords.find(word) == stopWords.end()) {
            result += word + " ";
        }
    }

    // Eliminar el último espacio en blanco si existe
    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

/**
 * @brief Limpia un archivo eliminando las palabras de parada y lo guarda en un archivo de salida.
 * 
 * @param inputFile Ruta al archivo de entrada.
 * @param outputFile Ruta al archivo de salida.
 * @param stopWords Conjunto de palabras de parada.
 */
void processFileWithStopWords(const string& inputFile, const string& outputFile, const unordered_set<string>& stopWords) {
    ifstream file(inputFile);
    ofstream outFile(outputFile);
    string line;
    
    // Leer cada línea del archivo de entrada
    while (getline(file, line)) {
        // Limpiar la línea de las palabras de parada
        string cleanedLine = cleanTextFromStopWords(line, stopWords);
        // Escribir la línea limpia en el archivo de salida
        outFile << cleanedLine << endl;
    }

    file.close();
    outFile.close();
}

void stop_words(const string& stopWordsPath, const string& path_in, const string& path_map, const string& exten,const string& path_clean){
    unordered_set<string> stopWords = loadStopWords(stopWordsPath);
    unordered_map<string, int> map_file;

    ifstream file(path_map);
    string line;
    while (getline(file, line)) {
        size_t last_comma = line.find_last_of(',');  // Encontrar la última coma
        // Extraer el nombre del libro (parte antes de la última coma)
        string book_name = line.substr(0, last_comma);
        book_name.erase(book_name.find_last_not_of(" ,") + 1);  // Eliminar espacios y comas finales

        // Extraer el índice (parte después de la última coma)
        string index_str = line.substr(last_comma + 1);
        index_str.erase(index_str.find_last_not_of(" ") + 1);  // Eliminar espacios adicionales 

        int index = stoi(index_str);  // Convertir el índice a entero

        // Insertar el nombre del libro y el índice en el unordered_map
        map_file[book_name] = index;
    }
    int id;

    for (const auto& entry : std::__fs::filesystem::directory_iterator(path_in)) {
        string pathFile = entry.path().string();
        id = map_file[entry.path().stem().string()];
        string path_output = path_clean + "/" + to_string(id) + "." + exten;
        
        if (entry.path().extension().string() == exten){
            processFileWithStopWords(pathFile, path_output,stopWords);
        }
    }
}