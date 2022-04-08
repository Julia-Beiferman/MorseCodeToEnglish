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
     {"\n", '\n'},
     {"|", '|'}
     };

morseCodes symbols_list[] = //list of special characters for extra credit.
{
  {"-----", '0'},
  {".----", '1'}, 
  {"..---", '2'}, 
  {"...--", '3'},
  {"....-", '4'}, 
  {".....", '5'}, 
  {"-....", '6'}, 
  {"--...", '7'}, 
  {"---..", '8'}, 
  {"----.", '9'}, 
  {".-.-.-", '.'},
  {"--..--", ','}, 
  {"..--..", '?'},
  {".----.", '\''},
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
  {".--.-.", '@'}
  //{"..-.-", '¿'},
  //{"--...-", '¡'}
  };

const char *englishToMorse(char eng)
{
  char const *error = "eeee"; //error message is the default

  if(symbols = 1){
    for (int i = 0; i < 27; i++) //refers back to mcodes to iterate thorugh the array
    {
      if (eng == symbols_list[i].letter) //checks to see if given const char* is in the array
      {
        return symbols_list[i].code; //then returns the letter translation
      }
    }

  }

  //std::cout << "Input" << eng << std::endl;

  for (int i = 0; i < 30; i++) //refers back to mcodes to iterate thorugh the array
  {
    if (toupper(eng) == mcodes[i].letter) //checks to see if given const char* is in the array
    {
      return mcodes[i].code; //then returns the letter translation
    }
  }

  return error;

}

char morseToEnglish(const char *morseIn) //morse to english translator function instead of a big switch statement I use strcmp through a 2D array
{
  for (int i = 0; i < 30; i++) //refers back to mcodes to iterate thorugh the array
  {
    if (strcmp(morseIn, mcodes[i].code) == 0) //checks to see if given const char* is in the array
    {
      return mcodes[i].letter; //then returns the letter translation
    }
  }

  if(symbols == 1){ //if the user turns on symbols
    for (int i = 0; i < 27; i++) //uses the symbols list to translate the number or special character
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

  std::cout << "Translating " << inputfile << " to morse code" << std::endl;

  while (infile.getline(cars, 255)) // while loop to iterate through all lines in the file
  {
    char *word; // tokenize each line into words seperated by a space

    
    if(verbose == 1){
      std::cout << "READ:: " << cars << std::endl;
      std::cout << "WROTE:: ";
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
        //std::cout << "Letter: " << d[i] << " Conversion: " << englishToMorse(d[i]) <<std::endl;
        if (verbose == 1)
        {
          std::cout << englishToMorse(d[i]) << englishToMorse('|');
        }

        outfile << englishToMorse(d[i]); // calls the englishToMorse translator function to write the character to the output file
        outfile << englishToMorse('|');  // add the '|' delimeter at the end of each morse code character
      }

        outfile << englishToMorse(' '); //adds the space in between words
        outfile << englishToMorse('|');

        if(verbose == 1){
          std::cout << englishToMorse(' ');
          std::cout << englishToMorse('|');
        }

      word = strtok(NULL, " "); // tokenize the word again until we only get letters
    }

    if(verbose == 1){
      std::cout << std::endl; //an endline for the verbose funciton
    }

    morseLine[0] = 0;

  }
  std::cout << outputfile << " file completed." << std::endl;

  infile.close(); // close files
  outfile.close();
}

void morseReadFile(const char *inputfile, const char *outputfile, int verbose) //reads a morse code file and converts it into english.
{
  ifstream morseIn; //define our input and output files
  ofstream transEng;
  morseIn.open(inputfile, ios::in);
  transEng.open(outputfile, ios::out);

  char text[255]; //define text that we are reading from the file.

  std::cout << "Translating " << inputfile << " to English" << std::endl; 

  while (morseIn.getline(text, 255, '\n')) //read loop for the file
  {
    const char *letter;

    if(verbose == 1){ //verbose read and write
      std::cout << "READ:: " << text << std::endl;
      std::cout << "WROTE:: ";
    }


    letter = strtok(text, "|"); //tokenize the string into letters
    while (letter != NULL) //loops until the letter string is empty
    {
      if (strcmp("\r", letter) == 0 || strcmp("\n", letter) == 0) //output a space since we are not getting it from return characters or newline for some reason.
      {
        transEng << morseToEnglish("/"); 
      }

      transEng << morseToEnglish(letter); //output our translation into the output file.
      
      if(verbose == 1){
        std::cout << morseToEnglish(letter); //outputs the line if in verbose mode
      }

      letter = strtok(NULL, "|"); //tokenize the letter by '|' so we can iterate through the next one. 
    }
    if(verbose == 1){
      std::cout << std::endl;
    }

  }

  std::cout << outputfile << " file completed." << std::endl;

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

  if (argc < 4)
  { // if too little parameters are given: return an error message
    std::cout << "Error -- usage: <exe> <input file> <-mc|-e> <output file";
  }
  else
  {                // else continue with the program
    inputfile = argv[1]; //assign all variables from the command line
    cmd = argv[2];
    outputfile = argv[3];
    
    int v = 0;

    if (argc  == 5){
      progress = argv[4];
      if (strcmp("-v", progress) == 0)
      { // checks if the user wants to go into verbose mode (extra credit)
        v = 1; 
      }
    }

    if(strcmp("-mcx", cmd) == 0 || strcmp("-ex", cmd) == 0){ //checks if user wants to use special characters
      symbols = 1;
    } else {
      symbols = 0;
    }
  

    if (strcmp("-mc", cmd) == 0 || strcmp("-mcx", cmd) == 0)
    {                                        // strcmp to check if user wants a file in Morse Code.
      engReadFile(inputfile, outputfile, v); // translates to Morse Code
    }
    else if (strcmp("-e", cmd) == 0 || strcmp("-ex", cmd) == 0)
    {                                          // check if the command if for eng
      morseReadFile(inputfile, outputfile, v); // translates to English
    }

    symbols = 0;

  }

  // morseReadFile(infile, outfile);

  return 0;
}
