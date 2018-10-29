#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool is_rest(string s);
int duration(string fraction);
int frequency(string note);

int main(void)
{
    string note  = get_string("Give me a note in format F#4: ");
    int freq = frequency(note);
    if(freq>=0)
        printf("The frequency of this note is %i\n", freq );
}

bool is_rest(string s)
{
    // Input of function - one line of ASCII codes of notes
    if(strcmp(s,"")==0)
        return true;
    else
        return false;
}

int duration(string fraction)
{
    string numerator = calloc(2,sizeof(char));
    numerator[0]=fraction[0];
    numerator[1]='\0';

    string denominator = calloc(2,sizeof(char));
    denominator[0] = fraction[2];
    denominator[1]='\0';

    return atoi(numerator)*8/atoi(denominator);
}

int frequency(string note) // Input should look lile "F#4"
{
    static const double freqA4 = 440.0;
    string nt = calloc(3, sizeof(char));
    string oct = calloc(2, sizeof(char));
    int octave = 0;

    // 0. parse input
    if(strlen(note)==2)
    {
        nt[0] = note[0];
        nt[1] = '\0';
        oct[0] = note[1];
        oct[1] = '\0';
        octave =  atoi(oct);
    }
    else
    {
        nt[0] = note[0];
        nt[1] = note[1];
        nt[2] = '\0';
        oct[0] = note[2];
        oct[1] = '\0';
        octave =  atoi(oct);
    }
    printf("Note is %s\nOctave is %d\n",nt, octave);

    // Calculate frequency of A in current octave
    double freqA = freqA4*pow(2,octave-4);
    double dist=0;

    // Calculate the distance between A and current note (in semitones)
    if(strcmp(nt,"C")==0)
        dist = -9;
    else if(strcmp(nt,"C#")==0 || strcmp(nt,"Db")==0)
        dist = -8;
    else if(strcmp(nt,"D")==0)
        dist = -7;
    else if(strcmp(nt,"D#")==0 || strcmp(nt,"Eb")==0)
        dist = -6;
    else if(strcmp(nt,"E")==0)
        dist = -5;
    else if(strcmp(nt,"F")==0)
        dist = -4;
    else if(strcmp(nt,"F#")==0 || strcmp(nt,"Gb")==0)
        dist = -3;
    else if(strcmp(nt,"G")==0)
        dist = -2;
    else if(strcmp(nt,"G#")==0 || strcmp(nt,"Ab")==0)
        dist = -1;
    else if(strcmp(nt,"A")==0)
        dist = 0;
    else if(strcmp(nt,"A#")==0 || strcmp(nt,"Bb")==0)
        dist = 1;
    else if(strcmp(nt,"B")==0)
        dist = 2;
    else
    {
        printf("We don't find this note plese check that note's name is correct\n");
        return -1;
    }
    double freq = freqA*pow(2.0, dist/12.0);
    return (int) round(freq);
}