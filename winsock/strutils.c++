#include <string.h>
#include <math.h>
#include "strutils.h"





//------------------------------------------------------------------------------
// Function name: FragmenteStr
// Description	: Return the tokens of a string separed by delimiters  
// Parameter	: source; le string source
//				  Delimiter; The delimiters				  	
//------------------------------------------------------------------------------
char** FragmenteStr(const char* source, char* delimiter, int& numfrags)
{
	if (source == NULL|| strlen(source) <= 0) 
		return NULL;                           

	numfrags = 0;
	char** liste = NULL;
	
	liste = new char*[strlen(source)];
	
	if ( liste == NULL)
		return NULL;
	
	
	for(int i = 0 ; i < strlen(source) ; i++)
	{
		liste[i] = new char[ strlen(source) ];

		if (liste[i] == NULL )
		{
			for (int k = 0 ; k <= i ; k++)
			delete [] liste[i];

			return NULL;
		}
	}


	char* ptr = NULL;
	char* copy = NULL;
	copy = new char[strlen(source) + 1];
	
	if ( copy == NULL )
		return NULL;
		
	strcpy(copy, source);
	
	ptr = strtok(copy,delimiter);
	if ( !ptr ) 
		return NULL;

	strcpy(liste[0],ptr);

	int j = 1;
	while (ptr)
	{
		ptr =  strtok(0,delimiter);

		if (ptr)
		{
			strcpy(liste[j], ptr); 
			j++;
		}
	}
	
	numfrags = j;
	delete [] copy;
	return liste;
}





//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
bool LineEmpty(char* line)
{
 bool empty = true;
 if (line == NULL || strlen(line) == 0)
    {
     return true;
     }
 int size = strlen(line);
 for(int i = 0; i < size; i++)
    {
     if(line[i] != ' ')
       {
        empty = false;
       }
     }
 return empty;
}



//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
bool check_entier(char ch)
{
  int val=int(ch);

  if (val > 47 && val < 58)    //chiffres de 0 a 9
                return true;
  else
                return false;
}



//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
int pow (int val, int exp)
{
int res;
for(res=1; exp>0; exp--)
        {res=res*val;}

return res;
}


//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
char* DecToBin(int value,int sizeofBin,bool complDeux)
{
 bool erreur=false;
 int t_size = sizeofBin -1;

 //vérifie si value débordera lors de sa traduction binaire
 if (complDeux)
        {
   if ((value > pow(2,t_size)-1) || (value < -pow(2,t_size)))
        erreur=true;
   }
 else
        {
   t_size = sizeofBin;
   if (value > pow(2,t_size)-1)
        erreur=true;
   }

 if (erreur)        //Si il y a déjà une erreur, on arrête avant de traduire
        return err4;
 else
 {
        char signe = '+';

        if (value < 0)
                {
        value = -value; //Si le nombre est négatif, on le rend positif pour
                                         //pouvoir le traduire en binaire
        signe = '-';
        }

        char* binVal;
        binVal = new char[sizeofBin];

        for(int i = 0; i < sizeofBin; i++) //Remplissage de la chaîne binVal avec des
                {                                                                                 //zero
        binVal[i] = '0';
        }

        int reste;
        t_size = sizeofBin-1;

        while (value && t_size >= 0 )
        {
        reste = value%2;
        value = value / 2;
        if (reste == 1)
     {binVal[t_size] = '1';}

     t_size--;
        }

        if (signe == '-') //Si le signe est négatif, on effectue le complément à deux
        {
      for (int f=0; f < sizeofBin; f++)
        {
         if (binVal[f] == '0')
                binVal[f] = '1';
         else
            binVal[f] = '0';
         }

      int retenue = 1;
      t_size = sizeofBin-1;


      while (retenue==1 && (t_size >= 0))
        {
         if (binVal[t_size]=='1')
                {
                binVal[t_size]='0';
            t_size--;
            }
         else
                {
            binVal[t_size] = '1';
            retenue = 0;
            }
         }
      }

    binVal[sizeofBin] = '\0';
    return binVal;
 }

}


//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
int BinToDec(char* binVal)
{
 int size = strlen(binVal);
 double currentBase = 0.0;
 long int value = 0;

 for(int i = size - 1; i >= 0; i--)
    {
     if (binVal[i] == '1')
      {
       value = value + int(pow(2.0, currentBase));
       }
       currentBase++;
     }
return value;
}


//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
char* strrev(char* s)
{
 int i = strlen(s);
 int revIndex = i - 1 ;
 char* temp = new char[i+2];
 
 for (int j = 0; j < i ; j++)
 {
 	temp[j] = s[revIndex];
 	revIndex--;
 }
 return temp;
 
}


//------------------------------------------------------------------------------
// Function name: 
// Description	:   
// Parameter	: 
//------------------------------------------------------------------------------
char* strlwr(char* s)
{
 int size = strlen(s);
 char* temp = new char[size + 1];
  
 for (int i = 0 ; i < size; i++)
 {
  	if (65 <=  s[i] && s[i] <= 90)
  	 {
  	 	temp[i] = s[i] + 32;
  	 }
  	else
  	 { 
  		temp[i] = s[i];
  	 }
 }
  
 return temp;
} 


