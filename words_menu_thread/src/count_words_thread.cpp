#include "../include/utils.h"
#include "../include/options.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[]) {
    string path_in = "", path_out = "", extension = "", path_map = "", path_stop = "", path_clean = "";

    int c;
    while ((c = getopt(argc, argv, "i:o:e:m:s:c:")) != -1) {
        switch (c) {
            case 'i':
                path_in = optarg;
                break;
            case 'o':
                path_out = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            case 'm':
                path_map = optarg;
                break;
            case 's':
                path_stop = optarg;
                break;
            case 'c':
                path_clean = optarg;
                break;

        }
    }

        // Verificar si los paths están vacíos o si no existen
    // Verify that all required directories exist
    const vector<string> requiredDirs = {path_in, path_out, path_clean, path_map, path_stop};
    for (const string& dir : requiredDirs) {
        if (dir.empty() || !std::filesystem::exists(dir)) {
            std::cerr << "Error: " << dir << " does not exist or was not specified.\n";
            return 1;
        }
    }


    system("clear");
    showMenu();
    mapa_archivo(path_map, extension, path_in);
    cout << "Se ejecuto mapa_archivo\n";
    stop_words(path_stop, path_in, path_map, extension, path_clean);
    cout << "se ejecuto stop_words\n";
    parallelWordCount(path_clean, path_out, 4);

    //funcion que cuente palabras con threads//
    
    return 0;
}
