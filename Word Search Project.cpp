#include <iostream>
#include <string>
#include <cstdlib>  // Used to apply random letter grids each time
#include <ctime>    // Used for time(0) to make the grid random every time
#include <cctype>  // Used for toupper() to handle small/capital letters
#include <windows.h> // Added for colors and boxes

using namespace std;

//  colors (14: Gold, 11: Cyan, 10: Green, 12: Red, 7: White)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    // Starting the random generator using system time
    srand(time(0));
    char playAgain;

    do {
        system("cls"); // Clear the screen for a new game
        const int SIZE = 12;
        char grid[SIZE][SIZE];
        int mode, category, playerScore = 0, compScore = 0, wordsFound = 0;
        string w1, w2, w3, w4, userWord;
        bool f1 = false, f2 = false, f3 = false, f4 = false;

        string playerMsg = "Welcome! Find the first word.";
        string compMsg = "Waiting for your move...";

        // --- REGION 1: Game Menu & Category Selection ---
        setColor(14); //  Gold Title
        cout << "\n  ========================================================" << endl;
        cout << "  ||                   WORD SEARCH GAME                 ||" << endl;
        cout << "  ========================================================" << endl;

        setColor(11);
        cout << "\n  --- Please make a selection from the following list ---" << endl;
        setColor(7);
        cout << "\n  1. Single Player\n  2. multiplayer (VS Computer)\n\n  Choice: ";
        cin >> mode;
        system("cls");

        setColor(14);
        cout << "\n  --- Select Category ---" << endl;
        setColor(11);
        cout << "  1. Programming\n  2. Fruit\n  3. Animals\n  4. Countries" << endl;
        setColor(7);
        cout << "\n  Choice: ";
        cin >> category;

        // Picking the word list based on the chosen number
        switch (category) {
        case 1: w1 = "LOOP"; w2 = "ARRAY"; w3 = "STRING"; w4 = "RAM"; break;
        case 2: w1 = "FIG"; w2 = "APPLE"; w3 = "BANANA"; w4 = "STRAWBERRY"; break;
        case 3: w1 = "CAT"; w2 = "TIGER"; w3 = "LION"; w4 = "ELEPHANT"; break;
        case 4: w1 = "OMAN"; w2 = "EGYPT"; w3 = "BRAZIL"; w4 = "PALESTINE"; break;
        default: return 0;
        }

        // --- REGION 2: Building the Grid ---
        // Filling the grid with random characters from A to Z
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                grid[i][j] = 'A' + (rand() % 26);

        //  (Horizontal)
        int r1 = rand() % 3, c1 = rand() % (6 - (int)w1.length() + 1);
        int r2 = 3 + rand() % 3, c2 = rand() % (6 - (int)w2.length() + 1);
        for (int i = 0; i < w1.length(); i++) grid[r1][c1 + i] = w1[i];
        for (int i = 0; i < w2.length(); i++) grid[r2][c2 + i] = w2[i];

        // (Vertical)
        int r3 = rand() % (SIZE - (int)w3.length() + 1), c3 = 6 + rand() % 3;
        int r4 = rand() % (SIZE - (int)w4.length() + 1), c4 = 9 + rand() % 3;
        for (int i = 0; i < w3.length(); i++) grid[r3 + i][c3] = w3[i];
        for (int i = 0; i < w4.length(); i++) grid[r4 + i][c4] = w4[i];

        // --- REGION 3: Main Gameplay Loop ---
        while (wordsFound < 4) {
            system("cls");

            //  Scoreboard Box
            setColor(14);
            cout << "\n  +---------------------------------------------------------+" << endl;
            cout << "  | "; setColor(10); cout << "SCORE: " << playerScore;
            setColor(14); cout << " | "; setColor(11); cout << "WORDS: " << wordsFound << "/4";
            if (mode == 2) { setColor(14); cout << " | "; setColor(13); cout << "Computer: " << compScore; }
            setColor(14); cout << " |" << endl;
            cout << "  +---------------------------------------------------------+" << endl;

            setColor(14);
            cout << "\n  --- WORD SEARCH GRID ---\n";
            setColor(7); // Grid lines
            cout << "    +---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
            for (int i = 0; i < SIZE; i++) {
                cout << "    | ";
                for (int j = 0; j < SIZE; j++) {
                    setColor(11); //  Cyan for letters
                    cout << grid[i][j];
                    setColor(7);
                    cout << " | ";
                }
                cout << endl << "    +---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
            }

            setColor(7);
            cout << "\n  You: "; setColor(10); cout << playerMsg << endl;
            if (mode == 2) { setColor(7); cout << "  " << "Computer: "; setColor(13); cout << compMsg << endl; }

            setColor(7);
            cout << "\n  Enter word: ";
            cin >> userWord;

            // Converting user input to uppercase to match the grid letters
            for (int i = 0; i < userWord.length(); i++) userWord[i] = toupper(userWord[i]);

            // --- REGION 4: Word Search Logic ---
            bool foundInGrid = false;
            // 1. Horizontal Search
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j <= SIZE - userWord.length(); j++) {
                    bool match = true;
                    for (int k = 0; k < userWord.length(); k++) {
                        if (grid[i][j + k] != userWord[k]) { match = false; break; }
                    }
                    if (match) { foundInGrid = true; break; }
                }
                if (foundInGrid) break;
            }
            // 2. Vertical Search 
            if (!foundInGrid) {
                for (int j = 0; j < SIZE; j++) {
                    for (int i = 0; i <= SIZE - userWord.length(); i++) {
                        bool match = true;
                        for (int k = 0; k < userWord.length(); k++) {
                            if (grid[i + k][j] != userWord[k]) { match = false; break; }
                        }
                        if (match) { foundInGrid = true; break; }
                    }
                    if (foundInGrid) break;
                }
            }

            // --- REGION 5: Scoring  ---
            if (userWord == w1 || userWord == w2 || userWord == w3 || userWord == w4) {
                if (foundInGrid) {
                    int points = userWord.length();
                    if (userWord.length() <= 4) points += 1;      // Easy
                    else if (userWord.length() <= 6) points += 2; // Medium
                    else points += 3;                            // Hard


                    if (userWord == w1 && !f1) { f1 = true; wordsFound++; playerScore += points; playerMsg = "CORRECT! Found " + w1; }
                    else if (userWord == w2 && !f2) { f2 = true; wordsFound++; playerScore += points; playerMsg = "CORRECT! Found " + w2; }
                    else if (userWord == w3 && !f3) { f3 = true; wordsFound++; playerScore += points; playerMsg = "CORRECT! Found " + w3; }
                    else if (userWord == w4 && !f4) { f4 = true; wordsFound++; playerScore += points; playerMsg = "CORRECT! Found " + w4; }
                    else { playerMsg = "Already found! Try another word."; }
                }
            }
            else { playerMsg = "WRONG! Word not in list."; }

            // --- REGION 6: Computer Move ---
            if (mode == 2 && wordsFound < 4) {
                string pick = "";
                if (!f1) { f1 = true; pick = w1; }
                else if (!f2) { f2 = true; pick = w2; }
                else if (!f3) { f3 = true; pick = w3; }
                else if (!f4) { f4 = true; pick = w4; }

                if (pick != "") {
                    int cPoints = pick.length() + (pick.length() <= 4 ? 1 : (pick.length() <= 6 ? 2 : 3));
                    wordsFound++;
                    compScore += cPoints;
                    compMsg = "Computer found " + pick;
                }
            }
        }

        // --- REGION 7: Final Screen & Winning ---
        system("cls");
        setColor(14);
        cout << "\n  ========================================================" << endl;
        cout << "  ||                   GAME COMPLETED!                  ||" << endl;
        cout << "  ========================================================" << endl;

        setColor(7);
        cout << "    +---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << "    | ";
            for (int j = 0; j < SIZE; j++) {
                setColor(11);
                cout << grid[i][j];
                setColor(7);
                cout << " | ";
            }
            cout << endl << "    +---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
        }

        setColor(7);
        cout << "\n  Your last move: "; setColor(10); cout << playerMsg << endl;
        if (mode == 2) { setColor(7); cout << "  Computer's last move: "; setColor(13); cout << compMsg << endl; }

        setColor(14);
        cout << "\n  --- FINAL RESULTS ---" << endl;
        setColor(10); cout << "  Your Total Score: " << playerScore << endl;
        if (mode == 2) {
            setColor(13); cout << "  Computer Total Score: " << compScore << endl;
            setColor(14);
            if (playerScore > compScore) cout << "\n  RESULT: CONGRATULATIONS! YOU WON!" << endl;
            else if (compScore > playerScore) cout << "\n  RESULT: GAME OVER! COMPUTER WON!" << endl;
            else cout << "\n  RESULT: IT'S A TIE!" << endl;
        }

        setColor(7);
        cout << "\n  Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}