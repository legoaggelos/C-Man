#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <vector>
#include <cassert>
#include <iostream>
#include <vector>
#include <string_view>
#include <bits/stdc++.h>
#include "random.h"
#include <algorithm>
namespace WordList
{
    std::vector<std::string_view> words{"mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};
    std::string_view getRandomWord()
    {
        return WordList::words[Random::get(static_cast<unsigned int>(0), static_cast<unsigned int>(WordList::words.size() - 1))];
    }
}
class Session
{
    std::string_view word{WordList::getRandomWord()};
    std::set<char> alreadyGuessedLetters{};
    short guessesLeft{6};
    bool isBeaten{false};

public:
    Session() = default;
    Session(short guesses) : guessesLeft{guesses} {}
    void displayState()
    {
        displayNonWordState();
        std::cout << "The word: ";
        isBeaten = true;
        for (auto e : word)
        {
            if (std::ranges::contains(alreadyGuessedLetters, e))
            {
                std::cout << e;
            }
            else
            {
                std::cout << "_";
                if (isBeaten)
                {
                    isBeaten = false;
                }
            }
        }
        std::cout << '\n';
        if (guessesLeft <= 0)
        {
            std::cout << "You lost! The word was: " << word;
            return;
        }
        if (getIsBeaten())
        {
            std::cout << "You won! The word was: " << word;
            return;
        }
    }
    void printGuessedLetters()
    {
        for (auto e : alreadyGuessedLetters)
        {
            std::cout << e;
        }
    }
    void displayNonWordState()
    {
        std::cout << "Wrong Guesses left: " << guessesLeft << ". Letters guessed : ";
        printGuessedLetters();
        std::cout << '\n';
    }
    short getGuessesLeft()
    {
        return guessesLeft;
    }
    void displayDebugState()
    {
        std::cout << "([DEBUG]correct word is: " << word << ")";
        return displayState();
    }
    std::string_view getCorrectWord()
    {
        return word;
    }
    char getGuess()
    {
        char attempt{};
        bool isFirstAttempt{true};
        do
        {
            if (!isFirstAttempt)
            {
                std::cin.clear();
                std::cout << "That wasn't a valid input.  Try again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                isFirstAttempt = false;
            }
            std::cout << "Enter your next letter: ";
            std::cin >> attempt;

        } while (!std::cin || (attempt < 'a' || attempt > 'z'));
        if (!std::ranges::contains(word, attempt) && !alreadyGuessedLetters.contains(attempt))
        {
            guessesLeft--;
        }
        return attempt;
    }
    void guess()
    {
        alreadyGuessedLetters.insert(getGuess());
    }
    bool getIsBeaten()
    {
        return isBeaten;
    }
};
char getYorNFromUser()
{
    std::vector<char> validChars{'Y','n'};
    char attempt{};
    bool isFirstAttempt{true};
    do
    {
        if (!isFirstAttempt)
        {
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            isFirstAttempt = false;
        }
        
        std::cin >> attempt;

    } while (!std::cin || (!std::ranges::contains(validChars,attempt)));
    return attempt;
}
int main()
{
    bool wantsToPlayAgain{false};
    do
    {
        Session currentSession{};
        std::cout << "Welcome to C++man (a variant of Hangman)\nTo win: guess the word.  To lose: run out of pluses.\n\n";
        currentSession.displayState();
        while (currentSession.getGuessesLeft() > 0 && !currentSession.getIsBeaten())
        {
            currentSession.guess();
            currentSession.displayState();
        }
        std::cout << "\nDo you want to play again?(Y/n)";
        wantsToPlayAgain=getYorNFromUser()=='Y' ? true : false;
    } while (wantsToPlayAgain);
    return 0;
}