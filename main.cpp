#include <iostream>
#include <ctime>

typedef unsigned long long ull;
typedef struct TData {
    char key[33];
    ull val;
} TData;


class TVector {
private:
    TData *mass;
    size_t size;
    size_t cap;
public:
    TVector();
    explicit TVector(size_t);
    ~TVector();
    void Add(TData);
    void PrintVector();
    void CountingSort(size_t);
    void RadixSort();
    int CharToNum(size_t i, int cInd);
};


TVector::TVector() {
    mass = new TData;
    size = 0;
    cap = 1;
}


TVector::TVector(size_t trgtSize) {
    mass = new TData[trgtSize+1];
    size = trgtSize;
    cap = trgtSize + 1;
}


TVector::~TVector() {
    delete[] this->mass;
    this->size = 0;
    this->cap = 0;
    this->mass = nullptr;
}


void TVector::Add(TData tmp) {
    if (this->size == this->cap ) {
        this->cap *= 2;
        auto *vec2 = new TData[this->cap];
        std::copy(this->mass, this->mass + this->size, vec2);
        delete[] this->mass;
        this->mass = vec2;
    }
    this->mass[this->size++] = tmp;
}


void TVector::PrintVector() {
    for (size_t i = 0; i < this->size; i++) {
        std::cout << this->mass[i].key << "\t" << this->mass[i].val << '\n';
    }

}


int TVector::CharToNum(size_t i, int cInd) {
    if (97 > this->mass[i].key[cInd]) {
        return this->mass[i].key[cInd] - 48;
    } else {
        return this->mass[i].key[cInd] - 87;
    }
}


void TVector::CountingSort(size_t cInd) {
    auto *res = new TData[this->size];
    size_t count[16] = {0};
    for (size_t i = 0; i < this->size; i++) {
        count[this->CharToNum(i, cInd)]++;
    }
    for (int i = 1; i < 16; i++) {
        count[i] += count[i-1];
    }

    for (size_t i = this->size; i > 0; i--) {
        int ind = this->CharToNum(i-1, cInd);
        res[count[ind]-1] = this->mass[i-1];
        count[ind]--;
    }
    delete[] this->mass;
    this->mass = res;
}


void TVector::RadixSort() {
    for (size_t i = 31; i >= 1; i--) {
        this->CountingSort(i);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    TData tmp;
    TVector vector(0);
    while (std::cin >> tmp.key && std::cin >> tmp.val) {
        vector.Add(tmp);
    }
    vector.RadixSort();
    vector.CountingSort(0);
    vector.PrintVector();
    return 0;
}