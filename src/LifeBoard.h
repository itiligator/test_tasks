//
// Created by Andrei on 23.02.2021.
//

#ifndef TEST_TASKS_LIFEBOARD_H
#define TEST_TASKS_LIFEBOARD_H


class LifeBoard{
public:
    explicit LifeBoard(int s);
    [[nodiscard]] int size() const;
    void NextStep();
    int PrintToConsole();

private:
    unsigned *storage;
    unsigned *calculated;
    int sz;
    unsigned l;
    bool GetCellFromStorage(int N, int M);
    void ToggleCellInCalculated(int N, int M);
    void CopyCalculatedToStorage();
};


#endif //TEST_TASKS_LIFEBOARD_H
