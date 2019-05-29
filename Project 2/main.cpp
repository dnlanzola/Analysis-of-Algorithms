//
//  File: main.cpp
//  Project 2: Dynamic Programming
//  COT 4400, Fall 2017.
//
//  Created by:
//              Daniel Anzola.
//              Ezequiel Regueira.
//              Michael Degrande.
//
//
//  Copyright © 2017. All rights reserved.
//

#include <array>
#include <algorithm>
#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <climits>

using namespace std;

//GLOBAL VARIABLES
int nRows;
int nCols;

//MAIN FUNCTION
int main(int argc, const char * argv[]) {
    //VARIABLES
    int i,j;
    int h = 0;
    int k = 0;
    
    //OPEN INPUT FILE
    cout << "Opening file..." << endl;
    ifstream iFile("input.txt");

    //CHECK IF FILE CAN BE OPENED
    if (!iFile)
    {
        cout << "Cannot open file" << endl;
        return 1;
    }
    
    cout << "File has been opened" << endl;
    
    //GET ROWS AND COLUMNS
    iFile >> nRows >> nCols;
    
    //READ IN FROM FILE TO ARRAY
    cout << "building array to traverse..." << endl;
    
    double* f_data = new double[nRows*nCols];
    double** f_array = new double*[nRows];
    double traversal_array[nRows][nCols];
    
    //BUILDING TRAVERSAL ARRAY (traversal_array)
    for (int i = 0; i < nRows; ++i)
        f_array[i] = f_data + nCols*i;
    
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            iFile >> traversal_array[i][j];
    
    //CLOSE INPUT FILE
    iFile.close();
    
    //PRINT TRAVERSAL ARRAY
    cout << "Traveral_Array: " << endl;
    for ( i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            cout << traversal_array[i][j] << " ";
        }
        cout << endl;
    }

    //VARIABLES
    int pos, right, temp, weightedDist;
    double memArr[nRows][nCols];
    string dirArr[nRows][nCols];
    
    //INITIALIZATION OF MEMOIZED ARRAY (memArr)
    for(int i = 0; i < nRows;i++)
    {
        for(int j = 0; j < nCols; j++)
        {
            //COPY FIRST ROW FROM TRAVERAL ARRAY
            if(i == 0)
            {
                memArr[i][j] = traversal_array[i][j];
            }
            //INITIALIZE REST OF ARRAY WITH MAXIMUM INTEGER VALUE
            else
            {
                memArr[i][j] = INT_MAX;
            }
        }
    }

    //PRINTING MEMOIZED ARRAY (memArr)
    cout << "memArr: " << endl;
    for ( i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            cout << memArr[i][j] << " ";
        }
        cout << endl;
    }

    //INITIALIZATION OF DIRECTIONAL ARRAY (dirArr)
    for(int i = 0; i < nRows;i++)
    {
        for(int j = 0; j < nCols; j++)
        {
            //COPY FIRST ROW FROM TRAVERAL ARRAY
            if(i == 0)
            {
                dirArr[i][j] = to_string(j);
            }
            //INITIALIZE REST OF THE ARRAY WITH A SPACE CHARACTER
            else
            {
                dirArr[i][j] = ' ';
            }
        }
    }

    //PRINTING DIRECTIONAL ARRAY (dirArr)
    cout << "dirArr: " << endl;
    for ( i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            cout << dirArr[i][j] << " ";
        }
        cout << endl;
    }

    //MODIFYING MEMOIZED ARRAY AND CALCULATE SHORTEST COST FOR EACH CASE
    for(h = 1; h < nRows; h++)
    {
        for(i = 0; i < nCols; i++)
        {
            int position, right;
            
            //CONDITIONS FOR RIGHT AND LEFT CHECKING
            if (i == 0)
                position = 0;
            else
                position = -1;
            
            if (i == (nCols - 1))
                right = 0;
            else
                right = 1;
            
            //GO THROUGH BOTTOM 3 NEIGHBORS
            for(position; position <= right; position++)
            {
                if (position == 0)
                {
                    if (memArr[h][i] > traversal_array[h - 1][i] + traversal_array[h][i])
                    {
                        memArr[h][i] = traversal_array[h - 1][i] + traversal_array[h][i];
                        dirArr[h][i] = 'S';
                        
                    }
                }
                else
                {
                    if ( memArr[h][i + position] > (traversal_array[h - 1][i] + (1.4 * traversal_array[h][i+position])))
                    {
                        memArr[h][i + position] = traversal_array[h - 1][i] + (1.4 * traversal_array[h][i+position]);
                        if (position == 1)
                            dirArr[h][i + position] = 'E';
                        else
                            dirArr[h][i + position] = 'W';
                    }
                }
            }
        }
        
        //MODIFIES TRAVERAL ARRAY FOR FURTHER CHECKING
        for (k = 0; k < nCols; k++)
        {
            traversal_array[h][k] = memArr[h][k];
        }
        
    }
    
    //PRINTING MODIFIED MEMOIZED ARRAY (memArr)
    cout << "memArr: " << endl;
    for ( i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            cout << memArr[i][j] << " ";
        }
        cout << endl;
    }
    
    //PRINTING MODIFIED DIRECTIONAL ARRAY (dirArr)
    cout << "dirArr: " << endl;
    for ( i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            cout << dirArr[i][j] << " ";
        }
        cout << endl;
    }
    
    //CREATE OUTPUT FILE
    ofstream oFile;
    oFile.open("output.txt");

    //CREATE RESULT ARRAY (resArr)
    string resArr[nRows];
    int aux;
    k = nRows - 1;
    
    //PRINTING & BUILDING RESULT ARRAY (resArr) AND BUILDING OUTPUT FILE
    cout << "resArr: " << endl;
    for (i = 0; i < nCols; i++)
    {
        aux = i;
        k = nRows - 1;
        for ( j = nRows - 1; j >= 0; j--)
        {
            if (dirArr[j][i] == "S")
            {
                resArr[k] = dirArr[j][i];
            }
            else if (dirArr[j][i] == "W")
            {
                resArr[k] = dirArr[j][i];
                i++;
            }
            else if (dirArr[j][i] == "E")
            {
                resArr[k] = dirArr[j][i];
                i--;
            }
            else if (dirArr[j][i] != "S" && dirArr[j][i] != "W" && dirArr[j][i] != "E")
            {
                resArr[k] = dirArr[j][i];
            }
            k--;
        }

        for (i = 0; i < nRows; i++)
        {
            if (resArr[i] == "S")
            {
                cout << "S ";
                oFile << "S ";
            }
            
            if (resArr[i] == "W")
            {
                cout << "SW ";
                oFile << "SW ";
            }
            
            if (resArr[i] == "E")
            {
                cout << "SE ";
                oFile << "SE ";
            }
            
            if (resArr[i] != "S" && resArr[i] != "W" && resArr[i] != "E")
            {
                cout << resArr[i] << ". ";
                oFile << resArr[i] << ". ";
            }
        }

        cout << endl;
        oFile << endl;
        j = nRows;
        i = aux;
    }
    
    oFile.close();

    return 0;
}



