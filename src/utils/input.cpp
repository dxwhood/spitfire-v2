#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cctype>

namespace chess {

namespace {
// Sets non-canonical (non-blocking, no-echo) mode if enable is true; otherwise restores defaults
void setNonBlockingMode(bool enable) {
    static struct termios origTermios;
    static bool saved = false;
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    if (enable) {
        if (!saved) {
            origTermios = tty; // save original settings
            saved = true;
        }
        tty.c_lflag &= ~(ICANON | ECHO);
    } else {
        if (saved)
            tty = origTermios; // restore saved settings
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// Checks if a key is available (non-blocking)
bool keyPressed() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

// Reads a single character from STDIN
char getChar() {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0)
        return c;
    return '\0';
}

// Hide and show the terminal cursor using ANSI escape sequences
void hideCursor() {
    std::cout << "\033[?25l" << std::flush;
}

void showCursor() {
    std::cout << "\033[?25h" << std::flush;
}

bool isValidSquare(const std::string& square) {
    return square.length() == 2 &&
           square[0] >= 'a' && square[0] <= 'h' &&  // File must be 'a' to 'h'
           square[1] >= '1' && square[1] <= '8';    // Rank must be '1' to '8'
}

bool isValidPromotion(char piece) {
    return piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n'; // UCI promotion pieces
}

}

namespace Input {

    // Displays a prompt with a blinking '>' at a fixed location,
    // and lets the user type after that. Returns the input string
    std::string inputMove() {
        std::string move;
        bool done = false;
        
        // Set terminal into non-blocking, no-echo mode and hide the cursor
        setNonBlockingMode(true);
        hideCursor();
        
        // Mark the start time for blinking calculations
        auto startTime = std::chrono::steady_clock::now();
        
        // Main loop: check for input and update display.
        while (!done) {
            // Poll and process all available keypresses.
            while (keyPressed()) {
                char ch = getChar();
                if (ch == '\n' || ch == '\r') {
                    done = true;
                    break;
                } else if (ch == 127) { // Handle Backspace (127 is DEL on macOS)
                    if (!move.empty())
                        move.pop_back();
                } else if (isprint(ch)) {
                    move.push_back(ch);
                }
            }
            
            // Check whether the blinking ">" should be visible
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
            bool blinkVisible = ((elapsed / 500) % 2 == 0);
            
            // Clear the current line (using ANSI escape code "\033[2K") and return carriage
            std::cout << "\r\033[2K";
            
            // Redraw the prompt
            std::cout << "Enter your move " 
                    << (blinkVisible ? ">" : " ") << " " 
                    << move << std::flush;
            
            // Sleep briefly so we don't hog the CPU.
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        
        // Restore terminal mode and show the cursor
        showCursor();
        setNonBlockingMode(false);

        // Print final input line and return the move
        std::cout << "\r\033[2KEnter your move > " << move << std::endl;
        return move;
    }

    bool validateInputMove(const std::string& move) {
        if (move.length() == 4) {  // Normal move (e2e4)
            return isValidSquare(move.substr(0, 2)) && isValidSquare(move.substr(2, 2));
        } 
        
        if (move.length() == 5) {  // Promotion move (e7e8q)
            return isValidSquare(move.substr(0, 2)) &&
                isValidSquare(move.substr(2, 2)) &&
                isValidPromotion(move[4]) &&
                move[0] == move[2] &&  // Promotion must be on the same file
                ((move[1] == '7' || move[3] == '8') ||  // Must be from rank 7 to rank 8 (white)
                (move[1] == '2' || move[3] == '1'));    // Must be frome rank 2 to rank 1 (black)
        }

        return false; 
    }

    // Parses a UCI compliant move string and returns a Move object
    Move parseUCIMove(std::string move) {
        // Get from square
        Square from = static_cast<Square>((move[0] - 'a') + 8 * (move[1] - '1'));
        // Get to square
        Square to = static_cast<Square>((move[2] - 'a') + 8 * (move[3] - '1'));

        // Get promotion piece (if any)
        uint8_t flags = 0;
        if (move.length() == 5) {
            switch (move[4]) {
                case 'q': flags = static_cast<uint8_t>(MoveCode::QUEEN_PROMO); break;
                case 'r': flags = static_cast<uint8_t>(MoveCode::ROOK_PROMO); break;
                case 'b': flags = static_cast<uint8_t>(MoveCode::BISHOP_PROMO); break;
                case 'n': flags = static_cast<uint8_t>(MoveCode::KNIGHT_PROMO); break;
            }
        }

        return Move(from, to, flags);
    }



}
}