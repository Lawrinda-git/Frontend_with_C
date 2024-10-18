#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_QUOTES 7

const char *quotes[NUM_QUOTES] = {
    "\"The greatest glory in living lies not in never falling, but in rising every time we fall.” - Nelson Mandela",
    "\"The way to get started is to quit talking and begin doing.”- Walt Disney",
    "\"Life is what happens when you're busy making other plans” - John Lennon",
    "\"You only live once, but if you do it right, once is enough”. - Mae West",
    "\"Never let the fear of striking out keep you from playing the game”. -Babe Ruth",
    "\"The best way to predict your future is to create it.” -Abraham Lincoln",
    "\"In the end, we will remember not the words of our enemies, but the silence of our friends.” - Martin Luther King Jr."
};

int main(void) {
    srand(time(NULL)); // Seed the random number generator
    int index = rand() % NUM_QUOTES; // Get a random index

    // Set content type
    printf("Content-Type: text/plain\n\n");
    printf("%s\n", quotes[index]); // Print the random quote

    return 0;
}
