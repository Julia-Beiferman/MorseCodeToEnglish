/*
Author: Julia Beiferman
Date: March 24th 2022
Description: Translate English into Morse code and vice versa. Sends output into a txt or mc file
Usuage: <exe> <input file> <-mc|-e> <output file>
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;
int symbols = 0;

typedef struct morseCodes //create a typedef so we can store a char* and char for morse to english translation
{
  const char *code; //morse code variable
  char letter; //english letter variable
};

morseCodes mcodes[] = //2D array to define all morse code to english translations, used in morseToEnglish() function
    {{".-", 'A'},
     {"-...", 'B'},
     {"-.-.", 'C'},
     {"-..", 'D'},
     {".", 'E'},
     {"..-.", 'F'},
     {"--.", 'G'},
     {"....", 'H'},
     {"..", 'I'},
     {".---", 'J'},
     {"-.-", 'K'},
     {".-..", 'L'},
     {"--", 'M'},
     {"-.", 'N'},
     {"---", 'O'},
     {".--.", 'P'},
     {"--.-", 'Q'},
     {".-.", 'R'},
     {"...", 'S'},
     {"-", 'T'},
     {"..-", 'U'},
     {"...-", 'V'},
     {".--", 'W'},
     {"-..-", 'X'},
     {"-.--", 'Y'},
     {"--..", 'Z'},
     {"/", ' '},
     {"\r", '\r'},
     {"\n", '\n'}};

morseCodes symbols_list[] =
{
  {".-.-.-", '.'},
  {"--..--", ','}, 
  {"..--..", '?'},
  //{".----.", ' '},
  {"-.-.--", '!'},
  {"-..-.", '/'},
  {"-.--.", '('}, 
  {"-.--.-", ')'},
  {".-...", '&'}, 
  {"---...", ':'},
  {"-.-.-.", ';'},
  {"-...-", '='},
  {".-.-.", '+'}, 
  {"-....-", '-'},
  {"..--.-", '_'},
  {".-..-.", '"'},
  {"...-..-", '$'},
  {".--.-.", '@'},
  //{"..-.-", '¿'},
  //{"--...-", '¡'},
};

const char *englishToMorse(char eng)
{
  char const *error = "eeee"; //error message is the default
  switch (tolower(eng)) //huge switch statement to manage translations from english to morse code
  {
  case 'a':
    return ".-";
  case 'b':
    return "-...";
  case 'c':
    return "-.-.";
  case 'd':
    return "-..";
  case 'e':
    return ".";
  case 'f':
    return "..-.";
  case 'g':
    return "--.";
  case 'h':
    return "....";
  case 'i':
    return "..";
  case 'j':
    return ".---";
  case 'k':
    return "-.-";
  case 'l':
    return ".-..";
  case 'm':
    return "--";
  case 'n':
    return "-.";
  case 'o':
    return "---";
  case 'p':
    return ".--.";
  case 'q':
    return "--.-";
  case 'r':
    return ".-.";
  case 's':
    return "...";
  case 't':
    return "-";
  case 'u':
    return "..-";
  case 'v':
    return "...-";
  case 'w':
    return ".--";
  case 'x':
    return "-..-";
  case 'y':
    return "-.--";
  case 'z':
    return "--..";
  case ' ':
    return "/";
  case '|':
    return "|";
  case '\n':
    return "\n";
  case '\r':
    return "\r";
  default:
    return error;
    break;
  }

  if(symbols = 1){
    for (int i = 0; i < sizeof(symbols_list); i++) //refers back to mcodes to iterate thorugh the array
    {
      if (eng == symbols_list[i].letter) //checks to see if given const char* is in the array
      {
        return symbols_list[i].code; //then returns the letter translation
      }
    }

  }
  // return error; //error output
}

char morseToEnglish(const char *morseIn) //morse to english translator function instead of a big switch statement I use strcmp through a 2D array
{
  std::cout << "Entering for loop" << std::endl;
  std::cout <<"Morse In " << morseIn << std::endl;
  for (int i = 0; i < 29; i++) //refers back to mcodes to iterate thorugh the array
  {
    if (strcmp(morseIn, mcodes[i].code) == 0) //checks to see if given const char* is in the array
    {
      return mcodes[i].letter; //then returns the letter translation
    }
  }
  std::cout << "Exiting for loop" << std::endl;

  if(symbols == 1){ //if the user turns on symbols
    std::cout << "Symbols are turned on, testing morse code... " << std::endl;
    for (int i = 0; i < sizeof(symbols_list); i++) //uses the symbols list to translate the number or special character
    {
      if (strcmp(morseIn, symbols_list[i].code) == 0) //checks to see if given const char* is in the array
      {
        return symbols_list[i].letter; //then returns the english translation
      }
    }

  }

  return '#'; //if all fails return the error '#'
}

void engReadFile(const char *inputfile, const char *outputfile, int verbose) // this function reads an english file to convert it into Morse Code
{
  char cars[255];  // character array to store every line
  ifstream infile; // initialize in and output files
  ofstream outfile;
  infile.open(inputfile, ios::in);
  outfile.open(outputfile, ios::out);

  while (infile.getline(cars, 255)) // while loop to iterate through all lines in the file
  {
    char *word; // tokenize each line into words seperated by a space

    
    if (verbose == 1)
    { // shows progress if in verbose mode
      std::cout << "READ:: " << cars << std::endl;
    }
    

    word = strtok(cars, " ");

    char morseLine[255]; // get each line of translated morse code for verbose mode
    morseLine[0] = 0;
    while (word != NULL)
    {
      int arrSize = strlen(word); // get size of the word
      char d[50];            // d is the individual character per word

      //std::cout << "The word is " << word << std::endl;
      for (int i = 0; i < arrSize; i++) // loop through each word for each of its characters
      {
        d[i] = *word;
        word++;
        if (d[i] == NULL) // sometimes we will get null characters from reading the file, so just convert it to an empty space
        {
          d[i] = ' ';
        }
        std::cout << "Letter: " << d[i] << " Conversion: " << englishToMorse(d[i]) <<std::endl;
        strcat(morseLine, ((char *)englishToMorse(d[i])));
        strcat(morseLine, ((char *)englishToMorse('|')));

        outfile << englishToMorse(d[i]); // calls the englishToMorse translator function to write the character to the output file
        outfile << englishToMorse('|');  // add the '|' delimeter at the end of each morse code character
      }

      word = strtok(NULL, " "); // tokenize the word again until we only get letters
    }

    if (verbose == 1)
    {
      std::cout << "WROTE:: " << morseLine << std::endl;
    }

    morseLine[0] = 0;

  }
  infile.close(); // close files
  outfile.close();
}

void morseReadFile(const char *inputfile, const char *outputfile, int verbose) //verbose parameter added for extra credit
{
  ifstream morseIn; //define our input and output files
  ofstream transEng;
  morseIn.open(inputfile, ios::in);
  transEng.open(outputfile, ios::out);

  char text[255]; //define text that we are reading from the file. 

  while (morseIn.getline(text, 255, '\n')) //read loop for the file
  {
    const char *letter;
    letter = strtok(text, "|");
    // std::cout << letter;
    // std::cout << "here in the while loop";
    while (letter != NULL)
    {
      std::cout << "This is the letter: " << letter << std::endl;
      if (strcmp("\r", letter) == 0 || strcmp("\n", letter) == 0) //output a space since we are not getting it from return characters or newline for some reason.
      {
        transEng << morseToEnglish("/");
        std::cout << "The letter is an end line " << letter << std::endl;
      }
      std::cout << "Entering morse to english" << std::endl;
      transEng << morseToEnglish(letter); //output our translation into the output file.
      std::cout << "Exiting morse to english" << std::endl;
      // transEng << d;
      std::cout << "This is the morse translation: " << morseToEnglish(letter) << std::endl;

      letter = strtok(NULL, "|"); //tokenize the letter by '|' so we can iterate through the next one. 
    }
  }
  morseIn.close();
  transEng.close();
}

int main(int argc, char *argv[]) // use argc and argv parameters to get variables from the command line
{
  // define variables to create our function
  char *inputfile;
  char *outputfile;
  char *cmd;
  char *progress;

  std::cout << "hi " << std::endl;

  if (argc < 4)
  { // if too little parameters are given: return an error message
    std::cout << "Error -- usage: <exe> <input file> <-mc|-e> <output file";
  }
  else
  {                // else continue with the program
    inputfile = argv[1]; //assign all variables from the command line
    cmd = argv[2];
    outputfile = argv[3];
    progress = argv[4];
    int v = 0;
    std::cout << "1" << std::endl;

    /*
    if (strcmp("-v", progress) == 0)
    { // checks if the user wants to go into verbose mode (extra credit)
      std::cout << "2" << std::endl;
      v = 1;
    }
    

      std::cout << "3" << std::endl;


    if(strcmp("-mcx", cmd) == 0 || strcmp("-ex", cmd) == 0){
      std::cout << "The if statement is running" << std::endl;
      symbols = 1;
    } else {
      std::cout << "The if statement is rnot unning" << std::endl;
      symbols = 0;
    }
    */

    if (strcmp("-mc", cmd) == 0 || strcmp("-mcx", cmd) == 0)
    {                                        // strcmp to check if user wants a file in Morse Code.
      engReadFile(inputfile, outputfile, v); // translates to Morse Code
    }
    else if (strcmp("-e", cmd) == 0 || strcmp("-ex", cmd) == 0)
    {                                          // check if the command if for eng
      std::cout << "Translating Morse into English " << std::endl;
      morseReadFile(inputfile, outputfile, v); // translates to English
    }

    symbols = 0;

  }

  // morseReadFile(infile, outfile);

  return 0;
}
