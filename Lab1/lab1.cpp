#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

main(int argc, char * argv[])
{
    int lineCount = 0;
    int wordCount = 0;
    int largest = 0;
    string largestWord;
    string word;
    int occurences[26] = {0};

    //input file stream
    ifstream input(argv[1]);
    if(!input)
    {
        cerr << "Couldn't find input file" << endl;
        return EXIT_FAILURE;
    }

    //output file stream
    ofstream output(argv[2]);
    if(!output)
    {
        cerr << "Couldn't open output file" << endl;
        return EXIT_FAILURE;
    }

    string line;
    string cleanLine;
    //read in file line by line
    while(getline(input, line))
    {   
        wordCount++;
        lineCount++;
        int ind = 0;
        int tempLength = 0;
        bool alpha = false;

        //skip to first character
        while(isblank((int)line[ind]) != 0)
        {
            ind++;
            continue;
        }

        //process line into words
        while(line[ind] != '\0')
        {   
            if(isalpha((int)line[ind]) != 0)
            {
                alpha = true;
            }

            if(alpha == true)
            {
                char temp = line[ind];
                if(temp < 96 && temp != 32)
                    temp += 32;
                cleanLine = cleanLine + temp;
            }

            //count letter occurences
            if(line[ind] > 96 && line[ind] < 123)
            {
                int val = line[ind];
                val -= 97;
                occurences[val]++;
            }
            else if(line[ind] > 64 && line[ind] < 91)
            {
                int val = line[ind];
                val -= 65;
                occurences[val]++;
            }

            //if current char is blank, and next is a letter, count the space as a word
            if(isblank((int)line[ind]) && isalpha((int)line[ind+1]) != 0)
            {
                wordCount++;
            }
            
            //if space is found and not end of string, process previous word length
            if(isblank((int)line[ind]) || line[ind+1] == '\0')
            {
                if(tempLength > largest)
                {
                    largest = tempLength - 1;
                    largestWord = word;
                }
                word = ""; 
                tempLength = 0;   
            }
            ind++;

            word = word + line[ind];
            tempLength++;
        }
        //account for the extra word count in empty lines
        if (alpha == false)
            wordCount--;

        //output the sanitised file with uppercase at the start
        if(cleanLine != "")
        {  
            if(cleanLine[0] > 97)
            {
                cleanLine[0] -= 32;
            } 
            output << cleanLine << endl;
        }
            
        cleanLine = "";
    }
    //output statistics to file
    output << endl << "Statistics" << endl;
    output << "number of lines: " << lineCount << endl;
    output << "number of words: " << wordCount << endl;
    output << "The largest word in the file is: " << largestWord << "with a size of " << largest << " characters" << endl;
    output << "Number of occurences of letters regardless of case:" << endl;

    int j = 0;
    for(int i = 'A'; i < 'N'; i++)
    {
        output << (char)i  << ": " << setw(3) << occurences[j] << "    " << char(i+13) << ": "<< setw(3) << occurences[j+13] << endl;
        j++;
    }

    input.close();
    output.close();

    return EXIT_SUCCESS;

}