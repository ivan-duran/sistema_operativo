#include "options.h"
#include "utils.h"
#include "dotenv.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <sys/types.h>




using namespace std;

int main(int argc, char *argv[]) {    
    system("clear");
    string user, pass, rol, text, str_vec;
    vector<int> vec_num;
    double num;
    bool hasUser = false, hasPass = false, hasText = false, hasVector = false, hasNumber = false;

    dotenv::init("path_db.env");
    string path_db = getenv("PATH_DB");
    unordered_map<string, pair<string, string>> users = loadUsers(path_db);


    int c;
    while ((c = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (c) {
            case 'u':
                user = optarg;
                if (!isValidUsername(user)){
                    cerr << "Nombre de usuario no valido, debe contener solo letras y tener al menos 3 caracteres." << endl;
                    return 1;
                }
                hasUser = true;
                break;
            case 'p':
                pass = optarg;
                if (!isValidPassword(pass)){
                    cerr << "Contraseña no valida, debe tener al menos 6 caracteres y contener solo letras y números.." << endl;
                    return 1;
                }
                hasPass = true;

                break;
            case 't':
                text = optarg;
                hasText = true;
                break;
            case 'v': {
                str_vec = optarg;
                if (!isValidVec(str_vec)) {
                    cerr << "ERROR: El argumento -v " << str_vec << " debe estar ingresado en el siguiente formato n;n;...;n." << endl;
                    return 1;
                }
                vec_num = splitInt(str_vec, ';');
                hasVector = true;
                break;
            }
            case 'n':
                try {
                    num = stod(optarg);
                } catch (const std::invalid_argument& ia) {
                    cerr << "El argumento -n '" << optarg << "' debe ser un número real" << endl;
                    return 1;
                }
                hasNumber = true;
                break;
            default:
                cerr << "Opción no válida." << endl;
                return 1;
        }
    }

    
    if (!areParamsProvided(hasUser, hasPass, hasText, hasVector, hasNumber)) {
        return 1;
    }


    if (!veryfyUser(users, user, pass)) {
        cerr << "Usuario o contraseña incorrectos." << endl;
        return 1;
    }
    rol = users[user].second;

    do {
        system("clear");
        char option;
        showMenu(user, rol);
        cout << "Ingrese una opción: ";
        cin >> option;
        system("clear"); 
        switch (option) {
            case '0':
                cout << "Saliendo..." << endl;
                return 0;
            case '1':
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text << endl;
                if (isPalindrome(text))
                    cout << "Es palíndromo." << endl;
                else
                    cout << "No es palíndromo." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case '2':
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text <<"\ntiene " << countVowels(text) << " vocales." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case '3':
                cout << "-----------------------------------" << endl;
                cout << "La palabra: " << text <<"\ntiene " << countLetters(text) << " letras." << endl;
                cout << "-----------------------------------" << endl;
                break;
            case '4': {
                cout << "-----------------------------------" << endl;
                pair<int, double> result = sumAndAverage(vec_num);
                cout << "Vector: (";
                for (int i = 0; i < vec_num.size(); i++) {
                    cout << vec_num[i];
                    if (i != vec_num.size() - 1) cout << ", ";
                }
                cout << ")" << endl;
                cout << "Sumatoria: " << result.first << endl;
                cout << "Promedio: " << result.second << endl;
                cout << "-----------------------------------" << endl;
                break;
                }   
            case '5':
                cout << "-----------------------------------" << endl;
                cout << "f(" << num << ") = " << calculateFunction(num) << endl;
                cout << "-----------------------------------" << endl;
                break;
            case '6':
                cout << "-----------------------------------" << endl;
                system("cd .. ; cd words_menu ; ./count_words");
                cout << "-----------------------------------" << endl;
                break;
            case '7':
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    string userIns, passIns, rolIns;
                    do{
                        cout << "Nombre de usuario: ";
                        cin>>userIns;
                        if (!isValidUsername(userIns)) cout << "El usuario debe ser solo letras y tener mas de 3 caracteres" << endl;
                    }while(!isValidUsername(userIns));
                    do{
                        cout << "Contraseña del usuarios: ";
                        cin>>passIns;
                        if (!isValidPassword(passIns)) cout << "La contraseña debe ser solo numeros o letras y tener mas de 6 caracteres" << endl;
                    }while(!isValidPassword(passIns));
                    cout << "Rol del usuario: ";
                    cin>>rolIns;
                    cout<< "Creando Usuario ..."<<endl;
                    createUser(userIns, passIns, rolIns, users, "usuarios.csv");
                    cout << "-----------------------------------" << endl;
                    break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
            case '8':
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    showUsers(users);
                    cout << "-----------------------------------" << endl;
                    break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
                
            case '9':
                if (rol == "Admin"){
                    cout << "-----------------------------------" << endl;
                    string userDel;
                    cout << "Nombre de usuario: ";
                    cin>>userDel;
                    cout<< "Eliminando Usuario ..."<<endl;
                    deleteUser(userDel, users[userDel].second, users, "usuarios.csv");
                    cout << "-----------------------------------" << endl;
                    break;
                }else {
                    cout << "Opción no válida.\n\n";
                    break;
                }
        }
        do {
            cout << "¿Desea realizar otra operación? (s/n): ";
            string ans;
            cin >> ans;
            if (ans == "n" || ans == "N") {
                cout << "Saliendo..." << endl;
                return 0;
            } else if (ans == "s" || ans == "S" || ans.empty()) {
                break;
            }
        } while (true);

    } while (true);
    return 0;
}
