#include "../include/utils.h"
#include "../include/options.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>


using namespace std;

int main(int argc, char *argv[]) {
    string extension = "", path_in= "", path_out = "", path_map = "", path_stop = "", path_clean = "";
    

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
    system("clear");
    showMenu();
    mapa_archivo(path_map, exten, path_in);
    stop_words(path_stop);
    //funcion que cuente palabras con threads//
    
    return 0;
}
