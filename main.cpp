#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
using namespace std;

class Game
{
    public:
        Game()
        {
            score = 0;
        }

        void loadGame()
        {
            std::ifstream inFile; 
            inFile.open("data.txt");

            string input;
            string temp;
            int vecNum = 0;
            while(inFile >> temp)
            {
                if(temp != ",")
                {
                    input = input + " " + temp;
                }
                else
                {   
                    input = input.substr(1);
                    switch(vecNum)
                    {
                        case 0:
                            first.push_back(input);
                            break;
                        case 1:
                            last.push_back(input);
                            break;
                        case 2:
                            year.push_back(input);
                            break;
                        case 3:
                            major.push_back(input);
                            break;
                        case 4:
                            minor.push_back(input);
                            break;
                    }
                    vecNum = (vecNum + 1) % 5;
                    input = "";
                }
            }

            for(int i = 0; i < first.size(); i++)
            {
                search.push_back(i);
            }
            random_device rd; 
            mt19937 g(rd()); 
            shuffle(search.begin(), search.end(), g); 
        }
        
        void playGame()
        {
            for(int i = 0; i < first.size(); i++)
            {
                playRound(search[i], i);
            }
        }

        void playRound(int idx, int round)
        {
            string firstCorrect = first[idx];
            string lastCorrect = last[idx];
            string yearCorrect = year[idx];
            string majorCorrect = major[idx];
            string minorCorrect = minor[idx];
            string ans1;
            string ans2;
            string ans3;
            string junk;
            int mode = rand() % 2;

            cout << "-----------Round: " << round + 1 << "/" << first.size() << "-----------" << endl;
            if(mode == 0)
            {
                cout << "First name: " << firstCorrect << endl;
                cout << "Year: " << yearCorrect << endl;
                cout << endl;
                
                cout << "Last name: ";
                getline(cin, ans1);

                cout << "Major: ";
                getline(cin, ans2);

                cout << "Minor: ";
                getline(cin, ans3);

                if(ans1 == lastCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }
                else    
                {
                    cout << "Incorrect - " << lastCorrect << endl;
                    missed.push_back(firstCorrect);
                }

                if(ans2 == majorCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }
                else    
                {
                    cout << "Incorrect - " << majorCorrect << endl;
                    missed.push_back(firstCorrect);
                }

                if(ans3 == minorCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }
                else    
                {
                    cout << "Incorrect - " << minorCorrect << endl;
                    missed.push_back(firstCorrect);
                }
            }

            else
            {
                cout << "Last name: " << lastCorrect << endl;
                cout << "Year: " << yearCorrect << endl;
                cout << endl;
                
                cout << "First name: ";
                getline(cin, ans1);

                cout << "Major: ";
                getline(cin, ans2);

                cout << "Minor: ";
                getline(cin, ans3);

                if(ans1 == firstCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }
                else    
                {
                    cout << "Incorrect - " << firstCorrect << endl;
                    missed.push_back(firstCorrect);
                }

                if(ans2 == majorCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }   
                else    
                {
                    cout << "Incorrect - " << majorCorrect << endl;
                    missed.push_back(firstCorrect);
                }

                if(ans3 == minorCorrect)
                {   
                    cout << "Correct" << endl;
                    score++;
                }
                else    
                {
                    cout << "Incorrect - " << minorCorrect << endl;
                    missed.push_back(firstCorrect);
                }
            }

            cout << endl;
            cout << endl;
            cout << endl;
        }

        void printStats()
        {
            cout << "-----------Game Complete-----------" << endl;
            cout << "Score: " << score << endl;
            cout << "Accuracy: " << double(score) / (first.size() * 3) << endl;
            cout << "Missed names: " << endl;
            for(int i = 0; i < missed.size(); i++)
            {
                cout << "\t" << missed[i] << endl;
            }
        }

    private:
        vector<string> first;
        vector<string> last;
        vector<string> year;
        vector<string> major;
        vector<string> minor;
        vector<int> search;
        vector<string> missed;
        int score;
};

int main()
{
    Game game;
    game.loadGame();
    game.playGame();
    game.printStats();
}