#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>


int main(int argc, char *argv[]) {
    std::ofstream file(argv[1]);
    srand(time(0));
    size_t size = atoi(argv[2]);
    char key[33];
    int flag;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 32; j++) {
            flag = rand() % 2;
            if (flag) {
                key[j] = (char) (rand() % 10 + 48);
            } else {
                key[j] = (char) (rand() % 6 + 97);
            }
        }
        key[32] = '\0';
        file << key << "\t" << abs(rand()) << "\n";
    }
    std::cout << RAND_MAX << "\n";
    return 0;
}