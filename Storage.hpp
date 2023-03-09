#pragma once

#include <string>

class Storage
{
private:
    int tileStorage[4][9]{};
public:
    Storage() {};
    void Add(const wchar_t* tile)
    {
        char name[5];
        wcstombs_s(nullptr, name, sizeof(name), tile, sizeof(name) - 1);
        // number tile
        if (name[0] >= '1' && name[0] <= '9')
        {
            switch (name[1])
            {
            case 'm':
                ++tileStorage[0][(int)(name[0] - '1')];
                break;
            case 'p':
                ++tileStorage[1][(int)(name[0] - '1')];
                break;
            case 's':
                ++tileStorage[2][(int)(name[0] - '1')];
                break;
            default:
                break;
            }
        }
        // dragon tile
        else if (name[1] == 'd')
        {
            switch (name[0])
            {
            case 'w':
                ++tileStorage[3][4];
                break;
            case 'g':
                ++tileStorage[3][5];
                break;
            case 'r':
                ++tileStorage[3][6];
                break;
            default:
                break;
            }
        }
        // wind tile
        else
        {
            switch (name[0])
            {
            case 'e':       // wind
                ++tileStorage[3][0];
                break;
            case 's':
                ++tileStorage[3][1];
                break;
            case 'w':
                ++tileStorage[3][2];
                break;
            case 'n':
                ++tileStorage[3][3];
                break;
            default:        // error
                break;
            }
        }
    }
    bool Calculate(std::wstring& message)
    {
        // Count tiles in hand. If not 14, then return false with corresponding message
        int numberOfTiles = CountTiles();
        if (numberOfTiles > 14) {
            message = L"Hand too large!";
            return false;
        }
        if (numberOfTiles < 14) {
            message = L"Hand too small!";
            return false;
        }
        // Check if any tile appears more than 4 times
        if (CheckInvalid()) {
            message = L"This is not a valid hand.";
            return false;
        }

        // Check for chiitoitsu (all pairs)
        if (CheckChiitoitsu()) {
            message = L"This is a winning hand!";
            return true;
        }
        // Check for Kokushi (13 orphans)
        if (CheckKokushi()) {
            message = L"This is a winning hand!";
            return true;
        }

        // Check for normal hand
        if (SubtractMeldRecursive(tileStorage)) {
            message = L"This is a winning hand!";
            return true;
        }

        // if nothing passes
        message = L"This is not a winning hand.";
        return false;
    }
    void Reset()
    {
        memset(tileStorage, 0, 36 * (sizeof(int)));
    }

private:
    int CountTiles()
    {
        int numberOfTiles = 0;
        for (auto& suit : tileStorage)
        {
            for (int& count : suit)
            {
                numberOfTiles += count;
            }
        }
        return numberOfTiles;
    }
    bool CheckInvalid()
    {
        for (auto& suit : tileStorage)
        {
            for (int& count : suit)
            {
                if (count >4)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool CheckChiitoitsu()
    {
        int pairCount = 0;
        for (auto& suit : tileStorage)
        {
            for (int& count : suit)
            {
                if (count == 2)
                {
                    ++pairCount;
                }
            }
        }
        return pairCount == 7;
    }
    bool CheckKokushi()
    {
        // Check that all tiles are present
        bool allTerminals =
            tileStorage[0][0] && tileStorage[0][8] &&
            tileStorage[1][0] && tileStorage[1][8] &&
            tileStorage[2][0] && tileStorage[2][8];
        bool allHonors =
            tileStorage[3][0] && tileStorage[3][1] && tileStorage[3][2] && tileStorage[3][3] &&
            tileStorage[3][4] && tileStorage[3][5] && tileStorage[3][6];
        return allTerminals && allHonors && HasPair(tileStorage);
    }

    bool HasPair(int (&tempArray)[4][9])
    {
        for (auto& suit : tempArray)
        {
            for (int& count : suit)
            {
                if (count == 2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool HasPairOnly(int(&tempArray)[4][9])
    {
        bool pairFound = false;
        for (auto& suit : tempArray)
        {
            for (int& count : suit)
            {
                if (count == 1 || count >= 3)
                {
                    return false;
                }
                if (count == 2)
                {
                    // if pair is already found
                    if (pairFound) {
                        return false;
                    }
                    pairFound = true;
                }
            }
        }
        return pairFound;
    }
    bool SubtractMeldRecursive(int(&tempArray)[4][9])
    {
        // Check only pair left
        if (HasPairOnly(tempArray)) {
            return true;
        }

        // Check for triplets
        for (int suit = 0; suit < 4; ++suit)
        {
            for (int tile = 0; tile < 9; ++tile)
            {
                if (tempArray[suit][tile] >= 3)
                {
                    int recursiveArray[4][9];
                    memcpy(recursiveArray, tempArray, 36 * sizeof(int));
                    recursiveArray[suit][tile] -= 3;
                    if (SubtractMeldRecursive(recursiveArray)) {
                        return true;
                    }
                }
            }
        }
        // Check for sequences
        bool oneInARow = false;
        bool twoInARow = false;
        for (int suit = 0; suit < 3; ++suit)
        {
            oneInARow = false;
            twoInARow = false;
            for (int tile = 0; tile < 9; ++tile)
            {
                if (tempArray[suit][tile] >= 1)
                {
                    // if first in sequence
                    if (!oneInARow && !twoInARow) {
                        oneInARow = true;
                    }
                    // if second in sequence
                    else if (oneInARow && !twoInARow) {
                        twoInARow = true;
                    }
                    // if third in sequence, then good to go deeper
                    else if (oneInARow && twoInARow) {
                        // this should never happen, but just in case
                        if (tile <= 1) {
                            return false;
                        }
                        int recursiveArray[4][9];
                        memcpy(recursiveArray, tempArray, 36 * sizeof(int));
                        recursiveArray[suit][tile-2] -= 1;
                        recursiveArray[suit][tile-1] -= 1;
                        recursiveArray[suit][tile] -= 1;
                        if (SubtractMeldRecursive(recursiveArray)) {
                            return true;
                        }
                    }
                }
                else
                {
                    oneInARow = false;
                    twoInARow = false;
                }
            }
        }
        // No sequences or triples or pair
        return false;
    }
};