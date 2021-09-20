#include <pong.h>

int main(int argc, char* argv[])
{
	// initiliaze all SDL 
	pong::initialization();

	// Start the main game
	pong::mainLoop();

	// Safely Quit SDL before ending the program
	pong::quitAll();
}