#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cctype>

namespace {
// Sets non-canonical (non-blocking, no-echo) mode if enable is true; otherwise restores defaults.
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

// Checks if a key is available (non-blocking).
bool keyPressed() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

// Reads a single character from STDIN.
char getChar() {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0)
        return c;
    return '\0';
}

// Hide and show the terminal cursor using ANSI escape sequences.
void hideCursor() {
    std::cout << "\033[?25l" << std::flush;
}

void showCursor() {
    std::cout << "\033[?25h" << std::flush;
}
}


// The inputMove function: it displays a prompt with a blinking '>' at a fixed location,
// and lets the user type after that. The display refreshes smoothly.
std::string chess::Input::inputMove() {
    std::string move;
    bool done = false;
    
    // Set terminal into non-blocking, no-echo mode and hide the cursor.
    setNonBlockingMode(true);
    hideCursor();
    
    // Mark the start time for blinking calculations.
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
        
        // Compute whether the blinking ">" should be visible.
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        bool blinkVisible = ((elapsed / 500) % 2 == 0);
        
        // Clear the current line (using ANSI escape code "\033[2K") and return carriage.
        std::cout << "\r\033[2K";
        
        // Redraw the prompt.
        // The prompt is:
        //   Enter your move: > user_text
        // where the ">" is blinking in place.
        std::cout << "Enter your move " 
                  << (blinkVisible ? ">" : " ") << " " 
                  << move << std::flush;
        
        // Sleep briefly so we don't hog the CPU.
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    
    // Once done, restore terminal mode and show the cursor.
    showCursor();
    setNonBlockingMode(false);

    // Print final input ensuring the ">" is always visible
    std::cout << "\r\033[2KEnter your move > " << move << std::endl;
    return move;
}


