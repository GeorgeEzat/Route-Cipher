#include <bits/stdc++.h>
using namespace std;
// ======================================================
// ======================================================
string sentence_validation(string sentenceI)
{
    while(true)
    {
        string sentenceII;
        cout << "Please enter sentenceI that contain at least 4 alphabetical characters: "; getline(cin,sentenceI);
        for (int i = 0; i < size(sentenceI) ; i++)
        {
            if (islower(sentenceI[i]) || isupper(sentenceI[i]))
                sentenceII += toupper(sentenceI[i]);
            else
                continue;
        }
        sentenceI = sentenceII;
        if (size(sentenceI) > 3) {
            return sentenceI;
        }
        else {
            continue;
        }
    }
}
// ======================================================
// ======================================================
int Encryption_Key(int EN_Size)
{
    int key; cout << "Enter the key: ";
    while (!(cin >> key))
    {
        // check the input is numbers only
        cout << "Please enter a valid key from 2 to " << (EN_Size/2) << " only: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true)
    {       // Check that the key not less than 2 and not more than (size of the sentence after editing) / 2
            if (key >= 2 && key <= (EN_Size/2))
                return key;
            else
            {
                cout << "Please enter a valid key from 2 to " << (EN_Size/2) << " only: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!(cin >> key))
                {
                    // check the input is numbers only
                    cout << "Please enter a valid key from 2 to " << (EN_Size/2) << " only: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
    }
}
// ======================================================
// ======================================================
int Decryption_Key(int ED_Size)
{
    int key; cout << "Enter the key: ";
    while (!(cin >> key))
    {   // check the input is numbers only
        cout << "Please enter a valid key: ";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true)
    {       // Check that the key not less than 2 and not more than (size of the sentence after editing) / 2
            // and divides the size without remainder
            if ((key >= 2) && (key <= (ED_Size/2)) && (ED_Size % key == 0))
                return key;
            else
            {
                cout << "Please enter a valid key: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!(cin >> key))
                {   // check the input is numbers only
                    cout << "Please enter a valid key: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
    }
}
// ======================================================
// ======================================================
string encryption (string sentenceI)
{
    sentenceI = sentence_validation(sentenceI);
    double EN_Size = size(sentenceI);
    const int columns = Encryption_Key(EN_Size);
    const int rows = ceil(EN_Size/columns);
    // ==================================================
    int remainder = fmod(EN_Size,columns); // remainder will help us to fill empty cells with 'X'(if they exist)
    char EN_matrix[rows][columns]; 
    int index = 0;
    for (int ro = 0 ; ro < rows ; ro++ )
    {
        for (int co =0 ; co < columns ; co++)
        {
            if ( (ro == (rows -1)) && (remainder != 0) && (remainder <= co)) // this is effective only in final row with empty cells(if they exist)
            {
                EN_matrix [ro][co] = 'X';
            }
            else if ( ro < rows)
            {   // fill the matrix with the sentence, all cells have only one character of the sentence
                EN_matrix [ro][co] = sentenceI[index];
                index++ ;
            }
        }
    }
    // ==================================================
    string encrypted_text;
    int r = rows, c = columns, count = rows*columns, z = 0, x = 0;
    // count variable makes us reassured that we will never get over the number of characters(size of the sentence)
    while (z < r && x < c)
    {   // move spirally by clockwise direction on the matrix and add each element consequently to encrypted_text variable
        for (int i = z ; (i < r && (count != 0 )) ; i++)
        {   // to move down
            encrypted_text += EN_matrix[i][c - 1] ;
            count--;
        }
        c--;
        if (z < r)
        {   // to move left
            for (int i = c - 1 ; (i >= x && (count != 0 )) ; i--)
            {
                encrypted_text += EN_matrix[r - 1][i];
                count--;
            }
            r--;
        }
        if (x < c)
        {   // to move up
            for (int i = r - 1 ; (i >= z && (count != 0 )) ; i--)
            {
                encrypted_text += EN_matrix[i][x];
                count--;
            }
            x++;
        }
        for(int i = x ; (i < c && (count != 0 )) ; i++)
        {   // to move right
            encrypted_text += EN_matrix[z][i];
            count--;
        }
        z++;
    }
    cout << "=========================\n";
    return encrypted_text;
}
// ======================================================
// ======================================================
string decryption (string sentenceI)
{
    sentenceI = sentence_validation(sentenceI);
    int DE_Size = size(sentenceI);
    const int columns = Decryption_Key(DE_Size);
    const int rows = (DE_Size/columns);
    // ==================================================
    char matrix [rows][columns]; 
    int r = rows, c = columns, count = rows*columns, z = 0, x = 0, index = 0;
    // count variable makes us reassured that we will never get over the number of characters(size of the sentence)
    while (z < r && x < c)
    {   // fill the matrix spirally in clockwise direction with the encrypted sentence,
        // all cells have only one character of the sentence
        for (int i = z ; (i < r && (count != 0)) ; i++)
        {   // to move down
            matrix[i][c - 1] = sentenceI[index] ;
            index ++;
            count--;
        }
        c--;
        if (z < r)
        {   // to move left
            for (int i = c - 1 ; (i >= x && (count != 0)) ; i--)
            {
                matrix[r - 1][i] = sentenceI[index];
                index ++;
                count--;
            }
            r--;
        }
        if (x < c)
        {   // to move up
            for (int i = r - 1 ; (i >= z && (count != 0)) ; i--)
            {
                matrix[i][x] = sentenceI[index];
                index ++;
                count--;
            }
            x++;
        }
        for(int i = x ; (i < c && (count != 0)) ; i++)
        {   // to move right
            matrix[z][i] = sentenceI[index];
            index ++;
            count--;
        }
        z++;
    }
    // ==================================================
    string original_text;
    for (int j = 0 ; j < rows ; j++) // moving on the matrix by ascending index order
    {
        for (int k = 0 ; k < columns ; k++)
        {
            original_text += matrix[j][k]; // add each element consequently to original_text variable
        }
    }
    cout << "=========================\n";
    return original_text;
}
// ======================================================
// ======================================================
int main()
{
    string answer;
    string zSentence;
    cout << "Welcome to Route Cipher!" << endl;
    while(true)
    {
        cout << "What do you like to do today?\n";
        cout << "1)Cipher a message\n2)Decipher a message\n3)End\n(1/2/3): ";
        getline(cin, answer);
        if (answer == "1"){
            zSentence = encryption(zSentence);
            cout << "the encrypted text is: " << zSentence;
            cout << "\n===========================\n";
            cin.ignore();
        }
        else if(answer == "2"){
            zSentence = decryption(zSentence);
            cout << "the decrypted text is: " << zSentence;
            cout << "\n===========================\n";
            cin.ignore();
        }
        else if(answer == "3"){
            cout << "Thank you for using Route Cipher\n";
            cout << "===========================\n";
            break;
        }
        else{
            cout << "Please enter a valid choice\n";
        }
    }
    return 0;
}