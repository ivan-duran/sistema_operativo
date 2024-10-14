#include "../include/utils.h"
#include "../include/options.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[]) {
    string  path_out = "", extension = "", path_inverted_index = "";

    int c;
    while ((c = getopt(argc, argv, "o:e:i:")) != -1) {
        switch (c) {
            case 'o':
                path_out = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            case 'i':
                path_inverted_index = optarg;
                break;
        }
    }

    }
    if (path_out.empty() || !std::__fs::filesystem::exists(path_out)) {
        cerr << "Error: Carpeta de salida no existe o no fue especificada.\n";
        return 1;
    }
    if (path_inverted_index.empty() || !std::__fs::filesystem::exists(path_inverted_index)) {
        cerr << "Error: Carpeta de archivos limpios no existe o no fue especificada.\n";
        return 1;
    }

    system("clear");
    showMenu();
    //mapa_archivo(path_map, extension, path_in);
    //cout << "Se ejecuto mapa_archivo\n";
    stop_words(path_stop, path_in, path_map, extension, path_clean);
    cout << "se ejecuto stop_words\n";
    parallelWordCount(path_clean, path_out, 4);

    //funcion que cuente palabras con threads//
    
    return 0;
}
