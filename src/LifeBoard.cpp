//
// Created by Andrei Itiligator on 23.02.2021.
//

#include <cstdlib>
#include <iostream>
#include "LifeBoard.h"
#define uint_l std::numeric_limits<unsigned>::digits




LifeBoard::LifeBoard(int s)
    : l {(unsigned) s*s/uint_l + 1}
    , storage {new unsigned[s*s/uint_l + 1]}
    , calculated {new unsigned[s*s/uint_l + 1]}
    , sz {s}
    {
        for(int i=0; i<l; i++){
            calculated[i] = rand();
            LifeBoard::CopyCalculatedToStorage();
        }
    }


int LifeBoard::size() const {
    return LifeBoard::sz;
}

bool LifeBoard::GetCellFromStorage(int N, int M) {
    unsigned mask;
    unsigned offset;

    if (N<0){
        N += LifeBoard::size();
    }
    if (N>=LifeBoard::size()){
        N -= LifeBoard::size();
    }

    if (M<0){
        M += LifeBoard::size();
    }
    if (M>=LifeBoard::size()){
        M -= LifeBoard::size();
    }

    offset = (sz * N + M) / uint_l;
    mask = 1 << ((sz * N + M) % uint_l);
    return *(storage + offset) & mask;
}

void LifeBoard::NextStep() {
    int sum;
    for (int i=0; i<LifeBoard::size(); i++){
        for (int j=0; j<LifeBoard::size(); j++){
            sum = 0;
            if (LifeBoard::GetCellFromStorage(i-1, j-1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i-1, j)){++sum;}
            if (LifeBoard::GetCellFromStorage(i-1, j+1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i, j-1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i, j+1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i+1, j-1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i+1, j)){++sum;}
            if (LifeBoard::GetCellFromStorage(i+1, j+1)){++sum;}
            if (LifeBoard::GetCellFromStorage(i, j)){
                if (1>=sum || sum>3) {
                    LifeBoard::ToggleCellInCalculated(i, j);
                }
            }
            else {
                if (sum==3) {
                    LifeBoard::ToggleCellInCalculated(i, j);
                }
            }
        }
    }
    LifeBoard::CopyCalculatedToStorage();


}

void LifeBoard::ToggleCellInCalculated(int N, int M) {
    unsigned bit;
    unsigned offset;

    if (N<0){
        N += LifeBoard::size();
    }
    if (N>=LifeBoard::size()){
        N -= LifeBoard::size();
    }

    if (M<0){
        M += LifeBoard::size();
    }
    if (M>=LifeBoard::size()){
        M -= LifeBoard::size();
    }

    offset = (sz * N + M) / uint_l;
    bit = ((sz * N + M) % uint_l);

    LifeBoard::calculated[offset] ^= 1UL << bit;
}

int LifeBoard::PrintToConsole() {
    char c;
    std::string line (LifeBoard::sz * 2 + 1, 'x');
    for (int i=0; i<LifeBoard::sz; i++){
        for (int j=0; j<LifeBoard::sz; j++){
            c = LifeBoard::GetCellFromStorage(i, j) ? 'x': '.';
            line[2*j] = c;
            line[2*j+1] = ' ';
        }
        line[LifeBoard::sz * 2] = '\n';
        std::cout << line;
    }
    std::cout << std::endl;
    return 0;
}

void LifeBoard::CopyCalculatedToStorage() {
    for (int i=0; i<LifeBoard::l; i++){
        LifeBoard::storage[i] = LifeBoard::calculated[i];
    }

}

LifeBoard::~LifeBoard() {
    delete[] LifeBoard::storage;
    delete[] LifeBoard::calculated;
}
