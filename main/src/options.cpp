#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include <thread>
#include <mutex>
#include <filesystem>
#include <unordered_map>
#include <set>

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
bool isPalindrome(string text){
    int text_size = text.length();
    for (int i = 0; i < text_size/2; ++i){
        if (tolower(static_cast<unsigned char>(text[i])) !=
            tolower(static_cast<unsigned char>(text[text_size - (i + 1)])))
            return false;
    }
    return true;
}

/**
 * @brief Cuenta la cantidad de vocales en un texto.
 * 
 * @param text Texto a analizar.
 * @return int Cantidad de vocales en el texto.
 * 
 * Cuenta la cantidad de vocales en un texto.
 */
int countVowels(string text){
    int vowels = 0;
    for (char c : text){
        if (tolower(static_cast<unsigned char>(c)) == 'a' ||
            tolower(static_cast<unsigned char>(c)) == 'e' ||
            tolower(static_cast<unsigned char>(c)) == 'i' ||
            tolower(static_cast<unsigned char>(c)) == 'o' ||
            tolower(static_cast<unsigned char>(c)) == 'u')
            vowels++;
    }
    return vowels;
}

/**
 * @brief Cuenta la cantidad de letras en un texto.
 * 
 * @param text Texto a analizar.
 * @return int Cantidad de letras en el texto.
 * 
 * Cuenta la cantidad de letras en un texto.
 */
int countLetters(string text){
    int letters = 0;
    for (char c : text){
        if (isalpha(static_cast<unsigned char>(c)))
            letters++;
    }
    return letters;
}

/**
 * @brief Calcula la sumatoria y el promedio de un vector de números.
 * 
 * @param numbers Vector de números.
 * @return pair<int, double> Sumatoria y promedio de los números.
 * 
 * Calcula la sumatoria y el promedio de un vector de números.
 */
pair<int, double> sumAndAverage(const vector<int>& numbers){
    int sum = 0;
    for (int num : numbers){
        sum += num;
    }
    return make_pair(sum, static_cast<double>(sum)/numbers.size());
}

/**
 * @brief Calcula el valor de la función f(x) = 5x^2 + 1/x.
 * 
 * @param n Valor de x.
 * @return double Valor de la función.
 * 
 * Calcula el valor de la función f(x) = 5x^2 + 1/x.
 */
double calculateFunction(double n){
    return 5*n*n + 1/n;
}

void deleteUser(string user, string rol, unordered_map<string, pair<string, string>>& users, string path){
    if (users.find(user) != users.end()){
        if (rol == "Admin"){
            cout << "No puedes eliminar un Admin." << endl;
            return;
        }else {
            users.erase(user);
            ofstream archivo(path, ios::trunc); // Se sobreescribe el archivo y se elimina el contenido.
            if (!archivo.is_open()){
                cerr << "Error al abrir el archivo." << endl;
                exit(1);
                return;
            }
            for (auto& user : users){
                archivo << user.first << ";" << user.second.first << ";" << user.second.second << endl;
            }
            archivo.close();
            cout << "Usuario eliminado exitosamente." << endl;
        }
    } else {
        cout << "El usuario no existe." << endl;
    }
}


/**
 * @brief Crea un usuario.
 * 
 * @param user Nombre de usuario.
 * @param pass Contraseña.
 * @param rol Rol del usuario.
 * @param users Mapa con los usuarios.
 * 
 * Crea un usuario y lo guarda en el archivo de usuarios.
 */
void createUser(string user, string pass, string rol, unordered_map<string, pair<string, string>>& users, string path){
    if (users.find(user) == users.end()){
        users[user] = make_pair(pass, rol);
        ofstream archivo(path);
        for (const auto& par : users) {
            archivo << par.first << ";" << par.second.first << ";" << par.second.second << endl;
        }
        archivo.close();
        cout << "Usuario creado exitosamente." << endl;
    }
    else{
        cout << "El usuario ya existe." << endl;
    }
    return;
}

/**
 * @brief Muestra los usuarios.
 * 
 * @param users Mapa con los usuarios.
 * 
 * Muestra los usuarios en el archivo de usuarios.
 */
void showUsers(unordered_map<string, pair<string, string>> users){
    cout<< "Lista de Usuarios : "<<endl;
    for (const auto& par : users) {
        cout << "Usuario: " << par.first << ", Contraseña: " << par.second.first<< ", Rol: " << par.second.second << endl;
        }
    return;
}

//opcion 10 DEBE IR EN UN ARCHIVO APARTE


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
    string inputDir = getenv("PATH_INPUT_THREAD");
    string outputDir = getenv("PATH_OUTPUT_THREAD");
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