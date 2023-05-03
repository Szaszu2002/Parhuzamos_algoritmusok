using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RSA_2
{
    internal class RSA
    {
        struct data
        {
            public char character;
            public char new_character;
            
        }
        struct data2
        {
            public int firstnumber;
            public int secondnumber;
            public int code;
            public int n;
        }
        public void EncodingText(data[] uncoded, data2[] coded)
        {
            
            int p = 1039;
            int q = 2617;
            int n = p * q;
            int e = 11;
            Parallel.For(0, uncoded.Length, (i) =>
            {
                if (uncoded[i].character == ' ')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 0;
                }
                else if (uncoded[i].character == '!')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == '%')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == '(')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == ')')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == '+')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 11;
                }
                else if (uncoded[i].character == ',')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 12;
                }
                else if (uncoded[i].character == '-')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 13;
                }
                else if (uncoded[i].character == '.')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 14;
                }
                else if (uncoded[i].character == '/')
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 15;
                }
                else if (uncoded[i].character == '0')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 0;
                }
                else if (uncoded[i].character == '1')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == '2')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 2;
                }
                else if (uncoded[i].character == '3')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 3;
                }
                else if (uncoded[i].character == '4')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 4;
                }
                else if (uncoded[i].character == '5')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == '6')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 6;
                }
                else if (uncoded[i].character == '7')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 7;
                }
                else if (uncoded[i].character == '8')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == '9')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == ':')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 10;
                }
                else if (uncoded[i].character == ';')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 11;
                }
                else if (uncoded[i].character == '<')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 12;
                }
                else if (uncoded[i].character == '=')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 13;
                }
                else if (uncoded[i].character == '>')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 14;
                }
                else if (uncoded[i].character == '?')
                {
                    coded[i].firstnumber = 3;
                    coded[i].secondnumber = 15;
                }
                else if (uncoded[i].character == '@')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 0;
                }
                else if (uncoded[i].character == 'A' || uncoded[i].character == 'Á')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == 'B')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 2;
                }
                else if (uncoded[i].character == 'C')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 3;
                }
                else if (uncoded[i].character == 'D')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 4;
                }
                else if (uncoded[i].character == 'E' || uncoded[i].character == 'É')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == 'F')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 6;
                }
                else if (uncoded[i].character == 'G')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 7;
                }
                else if (uncoded[i].character == 'H')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == 'I')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == 'J')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 10;
                }
                else if (uncoded[i].character == 'K')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 11;
                }
                else if (uncoded[i].character == 'L')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 12;
                }
                else if (uncoded[i].character == 'M')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 13;
                }
                else if (uncoded[i].character == 'N')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 14;
                }
                else if (uncoded[i].character == 'O' || uncoded[i].character == 'Ó' || uncoded[i].character == 'Ö' || uncoded[i].character == 'Ő')
                {
                    coded[i].firstnumber = 4;
                    coded[i].secondnumber = 15;
                }
                else if (uncoded[i].character == 'P')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 0;
                }
                else if (uncoded[i].character == 'Q')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == 'R')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 2;
                }
                else if (uncoded[i].character == 'S')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 3;
                }
                else if (uncoded[i].character == 'T')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 4;
                }
                else if (uncoded[i].character == 'U' || uncoded[i].character == 'Ú' || uncoded[i].character == 'Ü' || uncoded[i].character == 'Ű')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == 'V')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 6;
                }
                else if (uncoded[i].character == 'W')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 7;
                }
                else if (uncoded[i].character == 'X')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == 'Y')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == 'Z')
                {
                    coded[i].firstnumber = 5;
                    coded[i].secondnumber = 10;
                }
                else if (uncoded[i].character == 'a' || uncoded[i].character == 'á')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == 'b')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 2;
                }
                else if (uncoded[i].character == 'c')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 3;
                }
                else if (uncoded[i].character == 'd')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 4;
                }
                else if (uncoded[i].character == 'e' || uncoded[i].character == 'é')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == 'f')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 6;
                }
                else if (uncoded[i].character == 'g')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 7;
                }
                else if (uncoded[i].character == 'h')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == 'i' || uncoded[i].character == 'í')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == 'j')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 10;
                }
                else if (uncoded[i].character == 'k')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 11;
                }
                else if (uncoded[i].character == 'l')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 12;
                }
                else if (uncoded[i].character == 'm')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 13;
                }
                else if (uncoded[i].character == 'n')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 14;
                }
                else if (uncoded[i].character == 'o' || uncoded[i].character == 'ó' || uncoded[i].character == 'ö' || uncoded[i].character == 'ő')
                {
                    coded[i].firstnumber = 6;
                    coded[i].secondnumber = 15;
                }
                else if (uncoded[i].character == 'p')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 0;
                }
                else if (uncoded[i].character == 'q')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 1;
                }
                else if (uncoded[i].character == 'r')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 2;
                }
                else if (uncoded[i].character == 's')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 3;
                }
                else if (uncoded[i].character == 't')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 4;
                }
                else if (uncoded[i].character == 'u' || uncoded[i].character == 'ú' || uncoded[i].character == 'ü' || uncoded[i].character == 'ű')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 5;
                }
                else if (uncoded[i].character == 'v')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 6;
                }
                else if (uncoded[i].character == 'w')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 7;
                }
                else if (uncoded[i].character == 'x')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 8;
                }
                else if (uncoded[i].character == 'y')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 9;
                }
                else if (uncoded[i].character == 'z')
                {
                    coded[i].firstnumber = 7;
                    coded[i].secondnumber = 10;
                }
                else
                {
                    coded[i].firstnumber = 2;
                    coded[i].secondnumber = 3;
                }

                int M = (16 * (coded[i].firstnumber)) + (coded[i].firstnumber);
                int C;

                C = 1 % n;
                C = (M * C) % n;
                C = (C * C) % n;
                C = (C * C) % n;
                C = (M * C) % n;
                C = (C * C) % n;
                C = (M * C) % n;
                coded[i].code = C;
            });
            return;
        }//kódolás
        public void CodedFileDump(data2[] coded)
        {

        }//kódolt szöveg kiírása
        public void Decoding(data2[] coded, data[] uncoded)
        {
            int p = 1039;
            int q = 2617;
            int n = p * q;
            int e = 11;
            int d = ((7 * (p - 1) * (q - 1)) + 1) / e;  //1727987
            Parallel.For(0, coded.Length, (i) =>
            {
                int C;
                int bin = 0;
                C = 1 % n;  //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //0
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //0
                C = (C * C) % n; //0
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //0
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //0
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //0
                C = (C * C) % n; //0
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                C = (C * C) % n; //1
                C = (coded[i].code * C) % n;
                if (C == 32)
                {
                    uncoded[i].new_character = ' ';
                }
                else if (C == 33)
                {
                    uncoded[i].new_character = '!';
                }
                else if (C == 35)
                {
                    uncoded[i].new_character = '%';
                }
                else if (C == 40)
                {
                    uncoded[i].new_character = '(';
                }
                else if (C == 41)
                {
                    uncoded[i].new_character = ')';
                }
                else if (C == 43)
                {
                    uncoded[i].new_character = '+';
                }
                else if (C == 44)
                {
                    uncoded[i].new_character = ',';
                }
                else if (C == 45)
                {
                    uncoded[i].new_character = '-';
                }
                else if (C == 46)
                {
                    uncoded[i].new_character = '.';
                }
                else if (C == 47)
                {
                    uncoded[i].new_character = '/';
                }
                else if (C == 48)
                {
                    uncoded[i].new_character = '0';
                }
                else if (C == 49)
                {
                    uncoded[i].new_character = '1';
                }
                else if (C == 50)
                {
                    uncoded[i].new_character = '2';
                }
                else if (C == 51)
                {
                    uncoded[i].new_character = '3';
                }
                else if (C == 52)
                {
                    uncoded[i].new_character = '4';
                }
                else if (C == 53)
                {
                    uncoded[i].new_character = '5';
                }
                else if (C == 54)
                {
                    uncoded[i].new_character = '6';
                }
                else if (C == 55)
                {
                    uncoded[i].new_character = '7';
                }
                else if (C == 56)
                {
                    uncoded[i].new_character = '8';
                }
                else if (C == 57)
                {
                    uncoded[i].new_character = '9';
                }
                else if (C == 58)
                {
                    uncoded[i].new_character = ':';
                }
                else if (C == 59)
                {
                    uncoded[i].new_character = ';';
                }
                else if (C == 60)
                {
                    uncoded[i].new_character = '<';
                }
                else if (C == 61)
                {
                    uncoded[i].new_character = '=';
                }
                else if (C == 62)
                {
                    uncoded[i].new_character = '>';
                }
                else if (C == 63)
                {
                    uncoded[i].new_character = '?';
                }
                else if (C == 64)
                {
                    uncoded[i].new_character = '@';
                }
                else if (C == 65)
                {
                    uncoded[i].new_character = 'A';
                }
                else if (C == 66)
                {
                    uncoded[i].new_character = 'B';
                }
                else if (C == 67)
                {
                    uncoded[i].new_character = 'C';
                }
                else if (C == 68)
                {
                    uncoded[i].new_character = 'D';
                }
                else if (C == 69)
                {
                    uncoded[i].new_character = 'E';
                }
                else if (C == 70)
                {
                    uncoded[i].new_character = 'F';
                }
                else if (C == 71)
                {
                    uncoded[i].new_character = 'G';
                }
                else if (C == 72)
                {
                    uncoded[i].new_character = 'H';
                }
                else if (C == 73)
                {
                    uncoded[i].new_character = 'I';
                }
                else if (C == 74)
                {
                    uncoded[i].new_character = 'J';
                }
                else if (C == 75)
                {
                    uncoded[i].new_character = 'K';
                }
                else if (C == 76)
                {
                    uncoded[i].new_character = 'L';
                }
                else if (C == 77)
                {
                    uncoded[i].new_character = 'M';
                }
                else if (C == 78)
                {
                    uncoded[i].new_character = 'N';
                }
                else if (C == 79)
                {
                    uncoded[i].new_character = 'O';
                }
                else if (C == 80)
                {
                    uncoded[i].new_character = 'P';
                }
                else if (C == 81)
                {
                    uncoded[i].new_character = 'Q';
                }
                else if (C == 82)
                {
                    uncoded[i].new_character = 'R';
                }
                else if (C == 83)
                {
                    uncoded[i].new_character = 'S';
                }
                else if (C == 84)
                {
                    uncoded[i].new_character = 'T';
                }
                else if (C == 85)
                {
                    uncoded[i].new_character = 'U';
                }
                else if (C == 86)
                {
                    uncoded[i].new_character = 'V';
                }
                else if (C == 87)
                {
                    uncoded[i].new_character = 'W';
                }
                else if (C == 88)
                {
                    uncoded[i].new_character = 'X';
                }
                else if (C == 89)
                {
                    uncoded[i].new_character = 'Y';
                }
                else if (C == 90)
                {
                    uncoded[i].new_character = 'Z';
                }
                else if (C == 97)
                {
                    uncoded[i].new_character = 'a';
                }
                else if (C == 98)
                {
                    uncoded[i].new_character = 'b';
                }
                else if (C == 99)
                {
                    uncoded[i].new_character = 'c';
                }
                else if (C == 100)
                {
                    uncoded[i].new_character = 'd';
                }
                else if (C == 101)
                {
                    uncoded[i].new_character = 'e';
                }
                else if (C == 102)
                {
                    uncoded[i].new_character = 'f';
                }
                else if (C == 103)
                {
                    uncoded[i].new_character = 'g';
                }
                else if (C == 104)
                {
                    uncoded[i].new_character = 'h';
                }
                else if (C == 105)
                {
                    uncoded[i].new_character = 'i';
                }
                else if (C == 106)
                {
                    uncoded[i].new_character = 'j';
                }
                else if (C == 107)
                {
                    uncoded[i].new_character = 'k';
                }
                else if (C == 108)
                {
                    uncoded[i].new_character = 'l';
                }
                else if (C == 109)
                {
                    uncoded[i].new_character = 'm';
                }
                else if (C == 110)
                {
                    uncoded[i].new_character = 'n';
                }
                else if (C == 111)
                {
                    uncoded[i].new_character = 'o';
                }
                else if (C == 112)
                {
                    uncoded[i].new_character = 'p';
                }
                else if (C == 113)
                {
                    uncoded[i].new_character = 'q';
                }
                else if (C == 114)
                {
                    uncoded[i].new_character = 'r';
                }
                else if (C == 115)
                {
                    uncoded[i].new_character = 's';
                }
                else if (C == 116)
                {
                    uncoded[i].new_character = 't';
                }
                else if (C == 117)
                {
                    uncoded[i].new_character = 'u';
                }
                else if (C == 118)
                {
                    uncoded[i].new_character = 'v';
                }
                else if (C == 119)
                {
                    uncoded[i].new_character = 'w';
                }
                else if (C == 120)
                {
                    uncoded[i].new_character = 'x';
                }
                else if (C == 121)
                {
                    uncoded[i].new_character = 'y';
                }
                else if (C == 122)
                {
                    uncoded[i].new_character = 'z';
                }
                else
                {
                    uncoded[i].new_character = '#';
                }
            });
            return;
        }//dekódolás 
        public void DecodedFileDump(data[] uncoded)
        {

        }//dekódolt szöveg kiírása
        public void runtime_display()
        {

        }//futási idők kiírása
        public void Main(string[] args)
        {
            int[] adatok = File.ReadAllLines("text.txt");
            //beolvasást és a kiíratásokat megírni !!!! + időmérések
            
            data[] uncoded = new data[adatok.Length];
            data2[] coded = new data2[adatok.Length];
            EncodingText(uncoded, coded);
            CodedFileDump(coded);
            Decoding(coded, uncoded);
            DecodedFileDump(uncoded);
            runtime_display();
            


            Console.ReadLine();
        }
    }
}
