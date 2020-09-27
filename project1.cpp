//Abdurrehman Zulfiqar
//NetID: AXZ190015
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//Define prototypes for functions
void drawUp(fstream&, bool, bool, int);
void drawDown(fstream&, bool, bool, int);
void drawLeft(fstream&, bool, bool, int);
void drawRight(fstream&, bool, bool, int);
void printFile();

int main()
{
//File copy method
/////////////////////////////////////////////////////////////////////////////////////////
    ifstream infile("paint_base.txt");
    ofstream outfile("paint.txt", ios::binary);
    string c;
    if (infile)
    {
        while (getline(infile, c))
        {
            outfile << c << "\n";
        }
    }
    infile.close();
    outfile.close();
/////////////////////////////////////////////////////////////////////////////////////////

    //Defining variables
    bool pen_status, bold_status;
    int num_characters, place;
    fstream canvas, commandStream;
    string commandFile, input;
    long bounds;
    //Open output filestream to paint.txt
    canvas.open("paint.txt", ios::in| ios::out |ios::binary);
    cout << "Enter name of file to get commands from: " << endl;
    cin >> commandFile;

    //Open filestream for commands file
    commandStream.open(commandFile, ios::in);
    //While loop, contains user validation, conditions for pen status, drawing, distance, and bold status
        while(getline(commandStream, input))
        {
            //Input validation cases
            //-------------------------------------------
            if (input.length() < 5 && input.length() > 10)
                continue;
            if (input[1] != ',')
                continue;
            if (input[3] != ',')
                continue;
            //Scans input spot 4 for numbers from 0-9
            if (input[4] != '0' && input[4] != '1' && input[4] != '2' &&
                input[4] != '3' && input[4] != '4' && input[4] != '5' &&
                input[4] != '6' && input[4] != '7' && input[4] != '8' &&
                input[4] != '9')
                continue;
            if (input[6] == 'B' && input[7] == 'B')
                continue;
            if(input[6] == '0' || input[6] == '1' || input[6] == '2' ||
                input[6] == '3' || input[6] == '4' || input[6] == '5' ||
                input[6] == '6' || input[6] == '7' || input[6] == '8' ||
                input[6] == '9')
                continue;
            if (input[6] == 'P' && input[7] == 'P' && input[8] == 'P' &&
                input[9] == 'P')
                continue;

            //If-else statements for pen down/up
            //---------------------------------
            if(input[0] == '1')
            {
                pen_status = false;
            }
            else if(input[0] == '2')
            {
                pen_status = true;
            }
            else if(input[0] != '1' || input[0] != '2')
                continue;

            //If-else statements for distance
            //-------------------------------
            place = ((input[4]) - '0');
            num_characters = place;

            if((input[5] != ',') && (input[4] == '1' || input[4] == '2' ||input[4] == '3' || input[4] == '4' ||
               input[4] == '5' || input[4] == '6' || input[4] == '7' || input[4] == '8' ||
               input[4] == '9') && (input[5] == '0' || input[5] == '1' || input[5] == '2' ||input[5] == '3' || input[5] == '4' ||
               input[5] == '5' || input[5] == '6' || input[5] == '7' || input[5] == '8' ||
               input[5] == '9'))
            {
                   place = (10 * ((input[4]) - '0')) + (input[5] - '0');
                   num_characters = place;
            }

            //if-else statements for bold or no bold
            //--------------------------------------
            if(input[6] == 'B' || input[7] == 'B')
            {
               input[6] = 0;
               input[7] = 0;
               bold_status = true;
            }
            else
            {
                bold_status = false;
            }

            //If-else statements for direction
            //--------------------------------

            //Conditions for if the directions are north, south, east, west, and the functions to call if they are true.
            if (input[2] == 'N' && input[2] != ' ')
                drawUp(canvas, pen_status, bold_status, num_characters);

            else if(input[2] == 'S' && input[2] != ' ')
                drawDown(canvas, pen_status, bold_status, num_characters);

            else if(input[2] == 'E' && input[2] != ' ')
                drawRight(canvas, pen_status, bold_status, num_characters);

            else if(input[2] == 'W' && input[2] != ' ')
                drawLeft(canvas, pen_status, bold_status, num_characters);

            else if (input[2] == 'w' || input[2] == 's' || input[2] == 'n' || input[5] == 'e')
                    continue;
            else if(input [2] != 'W' ||input [2] != 'S' ||input [2] != 'N' ||input [2] != 'E' ||
                    input [2] == ' ')
                    continue;


            //Condition for using printFile function
            //--------------------------------------

            //Find the 'P' in every line to print out the picture in steps.
            if(input.find('P')!= string::npos)
            {
                printFile();
            }

        }
    canvas.close();
    commandStream.close();
    return 0;
}//end main

//Function for printing to console
void printFile()
{
        //Create input stream, connect to paint.txt, then print the result from paint.txt to the console
        cout << endl;
        string x;
        ifstream ifs("paint.txt");
        while(getline(ifs, x))
        {
            cout << x;
            cout << endl;
        }
        ifs.close();
}
//Function for drawing up
void drawUp(fstream &canvas, bool pen_status, bool bold_status, int num_characters)
{
    //If pen is up, just move the pen and don't write
    if (pen_status == false)
    {
        for(int i = 0; i < num_characters; i++)
        {
            canvas.seekp(-51L, ios::cur);
        }
    }
    //If pen is down, move and write as pen moves
    else if (pen_status == true)
    {
        for(int i = 0; i < num_characters; i++)
        {
            //Start from current position
            canvas.seekp(-51, ios::cur);
            if (bold_status == true || canvas.peek() == '#')
            {
                canvas << '#';
                canvas.seekp(-1L, ios::cur);
            }
            else if (bold_status == false)
            {
                canvas << '*';
                canvas.seekp(-1L, ios::cur);
            }
        }
    }
}
//Function for drawing down
void drawDown(fstream &canvas, bool pen_status, bool bold_status, int num_characters)
{
    if (pen_status == false)
    {
        for(int i = 0; i < num_characters; i++)
        {
            //Start from current position
            canvas.seekp(51L, ios::cur);
        }
    }
    else if(pen_status == true)
    {
        for(int i = 0; i < num_characters; i++)
        {
            //Start from current position
            canvas.seekp(51, ios::cur);
            if (bold_status == true|| canvas.peek() == '#')
            {
                canvas << '#';
                canvas.seekp(-1L, ios::cur);
            }
            else if (bold_status == false)
            {
                canvas << '*';
                canvas.seekp(-1L, ios::cur);
            }
        }
    }
}
//Function for drawing left
void drawLeft(fstream &canvas, bool pen_status, bool bold_status, int num_characters)
{
    if (pen_status == false)
    {
        for(int i = 0; i < num_characters; i++)
        {
            //Start from current position
            canvas.seekp(-1L, ios::cur);
        }
    }
    else if (pen_status == true)
    {
        for(int i = 0; i < num_characters; i++)
        {
            canvas.seekp(-1L, ios::cur);
            if (bold_status == true|| canvas.peek() == '#')
            {
                canvas << '#';
                canvas.seekp(-1L, ios::cur);
            }
            else if (bold_status == false)
            {
                canvas << '*';
                canvas.seekp(-1L, ios::cur);
            }
        }
    }
}
//Function for drawing right
void drawRight(fstream &canvas, bool pen_status, bool bold_status, int num_characters)
{
    if (pen_status == false)
    {
        for(int i = 0; i < num_characters; i++)
        {
            //Start from current position
            canvas.seekp(1L, ios::cur);
        }
    }
    else if (pen_status == true)
    {
        for(int i = 0; i < num_characters; i++)
        {
            canvas.seekp(1L, ios::cur);
            if (bold_status == true|| canvas.peek() == '#')
            {
                canvas << '#';
                canvas.seekp(-1L, ios::cur);
            }
            else if (bold_status == false)
            {
                canvas << '*';
                canvas.seekp(-1L, ios::cur);
            }
        }
    }
}
