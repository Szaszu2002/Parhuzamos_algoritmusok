using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

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
            public int number;
            public int code;
            public int n;
        }

        static void Main(string[] args)
        {
            //algolgoritmus hibádzik!!!
            
            data[] uncoded = new data[100000];
            data2[] coded = new data2[uncoded.Length];
            Stopwatch fulltime = new Stopwatch();
            fulltime.Start();
            StreamReader read=new StreamReader("text_short_story.txt");
            int i=0;
            string line;
            while(!read.EndOfStream)
            {
                line = read.ReadLine();
                //string[] lines = line;
                for(int j = 0; j < line.Length; j++)
                {
                    uncoded[i].character = line[j];
                    i++;
                }
            }
            read.Close();

            Stopwatch encoding_time = new Stopwatch();
            encoding_time.Start();
            EncodingText(uncoded, coded);
            encoding_time.Stop();
            CodedFileDump(coded);
            Stopwatch decoding_time = new Stopwatch();
            decoding_time.Start();
            Decoding(coded, uncoded);
            decoding_time.Stop();
            DecodedFileDump(uncoded);

            fulltime.Stop();
            TimeSpan ts_fulltime = fulltime.Elapsed;
            TimeSpan ts_encoding_time = encoding_time.Elapsed;
            TimeSpan ts_decoding_time = decoding_time.Elapsed;
            runtime_display(ts_fulltime, ts_encoding_time, ts_decoding_time);
            


            //Console.ReadLine();
        }

        static void EncodingText(data[] uncoded, data2[] coded)
        {
            int p = 1039;
            //int p = 313;
            int q = 2617;
            //int q = 157;
            int n = p * q;
            int e = 11;
            Parallel.For(0, uncoded.Length, (i) =>
            {
                if (uncoded[i].character == ' ')
                {
                    coded[i].number = 32;
                }
                else if (uncoded[i].character == '!')
                {
                    coded[i].number = 33;
                }
                else if (uncoded[i].character == '%')
                {
                    coded[i].number = 37;
                }
                else if (uncoded[i].character == '(')
                {
                    coded[i].number = 40;
                }
                else if (uncoded[i].character == ')')
                {
                    coded[i].number = 41;
                }
                else if (uncoded[i].character == '+')
                {
                    coded[i].number = 43;
                }
                else if (uncoded[i].character == ',')
                {
                    coded[i].number = 44;
                }
                else if (uncoded[i].character == '-')
                {
                    coded[i].number = 45;
                }
                else if (uncoded[i].character == '.')
                {
                    coded[i].number = 46;
                }
                else if (uncoded[i].character == '/')
                {
                    coded[i].number = 47;
                }
                else if (uncoded[i].character == '0')
                {
                    coded[i].number = 48;
                }
                else if (uncoded[i].character == '1')
                {
                    coded[i].number = 49;
                }
                else if (uncoded[i].character == '2')
                {
                    coded[i].number = 50;
                }
                else if (uncoded[i].character == '3')
                {
                    coded[i].number = 51;
                }
                else if (uncoded[i].character == '4')
                {
                    coded[i].number = 52;
                }
                else if (uncoded[i].character == '5')
                {
                    coded[i].number = 53;
                }
                else if (uncoded[i].character == '6')
                {
                    coded[i].number = 54;
                }
                else if (uncoded[i].character == '7')
                {
                    coded[i].number = 55;
                }
                else if (uncoded[i].character == '8')
                {
                    coded[i].number = 56;
                }
                else if (uncoded[i].character == '9')
                {
                    coded[i].number = 57;
                }
                else if (uncoded[i].character == ':')
                {
                    coded[i].number = 58;
                }
                else if (uncoded[i].character == ';')
                {
                    coded[i].number = 59;
                }
                else if (uncoded[i].character == '<')
                {
                    coded[i].number = 60;
                }
                else if (uncoded[i].character == '=')
                {
                    coded[i].number = 61;
                }
                else if (uncoded[i].character == '>')
                {
                    coded[i].number = 62;
                }
                else if (uncoded[i].character == '?')
                {
                    coded[i].number = 63;
                }
                else if (uncoded[i].character == '@')
                {
                    coded[i].number = 64;
                }
                else if (uncoded[i].character == 'A' || uncoded[i].character == 'Á')
                {
                    coded[i].number = 65;
                }
                else if (uncoded[i].character == 'B')
                {
                    coded[i].number = 66;
                }
                else if (uncoded[i].character == 'C')
                {
                    coded[i].number = 67;
                }
                else if (uncoded[i].character == 'D')
                {
                    coded[i].number = 68;
                }
                else if (uncoded[i].character == 'E' || uncoded[i].character == 'É')
                {
                    coded[i].number = 69;
                }
                else if (uncoded[i].character == 'F')
                {
                    coded[i].number = 70;
                }
                else if (uncoded[i].character == 'G')
                {
                    coded[i].number = 71;
                }
                else if (uncoded[i].character == 'H')
                {
                    coded[i].number = 72;
                }
                else if (uncoded[i].character == 'I')
                {
                    coded[i].number = 73;
                }
                else if (uncoded[i].character == 'J')
                {
                    coded[i].number = 74;
                }
                else if (uncoded[i].character == 'K')
                {
                    coded[i].number = 75;
                }
                else if (uncoded[i].character == 'L')
                {
                    coded[i].number = 76;
                }
                else if (uncoded[i].character == 'M')
                {
                    coded[i].number = 77;
                }
                else if (uncoded[i].character == 'N')
                {
                    coded[i].number = 78;
                }
                else if (uncoded[i].character == 'O' || uncoded[i].character == 'Ó' || uncoded[i].character == 'Ö' || uncoded[i].character == 'Ő')
                {
                    coded[i].number = 79;
                }
                else if (uncoded[i].character == 'P')
                {
                    coded[i].number = 80;
                }
                else if (uncoded[i].character == 'Q')
                {
                    coded[i].number = 81;
                }
                else if (uncoded[i].character == 'R')
                {
                    coded[i].number = 82;
                }
                else if (uncoded[i].character == 'S')
                {
                    coded[i].number = 83;
                }
                else if (uncoded[i].character == 'T')
                {
                    coded[i].number = 84;
                }
                else if (uncoded[i].character == 'U' || uncoded[i].character == 'Ú' || uncoded[i].character == 'Ü' || uncoded[i].character == 'Ű')
                {
                    coded[i].number = 85;
                }
                else if (uncoded[i].character == 'V')
                {
                    coded[i].number = 86;
                }
                else if (uncoded[i].character == 'W')
                {
                    coded[i].number = 87;
                }
                else if (uncoded[i].character == 'X')
                {
                    coded[i].number = 88;
                }
                else if (uncoded[i].character == 'Y')
                {
                    coded[i].number = 89;
                }
                else if (uncoded[i].character == 'Z')
                {
                    coded[i].number = 90;
                }
                else if (uncoded[i].character == 'a' || uncoded[i].character == 'á')
                {
                    coded[i].number = 97;
                }
                else if (uncoded[i].character == 'b')
                {
                    coded[i].number = 98;
                }
                else if (uncoded[i].character == 'c')
                {
                    coded[i].number = 99;
                }
                else if (uncoded[i].character == 'd')
                {
                    coded[i].number = 100;
                }
                else if (uncoded[i].character == 'e' || uncoded[i].character == 'é')
                {
                    coded[i].number = 101;
                }
                else if (uncoded[i].character == 'f')
                {
                    coded[i].number = 102;
                }
                else if (uncoded[i].character == 'g')
                {
                    coded[i].number = 103;
                }
                else if (uncoded[i].character == 'h')
                {
                    coded[i].number = 104;
                }
                else if (uncoded[i].character == 'i' || uncoded[i].character == 'í')
                {
                    coded[i].number = 105;
                }
                else if (uncoded[i].character == 'j')
                {
                    coded[i].number = 106;
                }
                else if (uncoded[i].character == 'k')
                {
                    coded[i].number = 107;
                }
                else if (uncoded[i].character == 'l')
                {
                    coded[i].number = 108;
                }
                else if (uncoded[i].character == 'm')
                {
                    coded[i].number = 109;
                }
                else if (uncoded[i].character == 'n')
                {
                    coded[i].number = 110;
                }
                else if (uncoded[i].character == 'o' || uncoded[i].character == 'ó' || uncoded[i].character == 'ö' || uncoded[i].character == 'ő')
                {
                    coded[i].number = 111;
                }
                else if (uncoded[i].character == 'p')
                {
                    coded[i].number = 112;
                }
                else if (uncoded[i].character == 'q')
                {
                    coded[i].number = 113;
                }
                else if (uncoded[i].character == 'r')
                {
                    coded[i].number = 114;
                }
                else if (uncoded[i].character == 's')
                {
                    coded[i].number = 115;
                }
                else if (uncoded[i].character == 't')
                {
                    coded[i].number = 116;
                }
                else if (uncoded[i].character == 'u' || uncoded[i].character == 'ú' || uncoded[i].character == 'ü' || uncoded[i].character == 'ű')
                {
                    coded[i].number = 117;
                }
                else if (uncoded[i].character == 'v')
                {
                    coded[i].number = 118;
                }
                else if (uncoded[i].character == 'w')
                {
                    coded[i].number = 119;
                }
                else if (uncoded[i].character == 'x')
                {
                    coded[i].number = 120;
                }
                else if (uncoded[i].character == 'y')
                {
                    coded[i].number = 121;
                }
                else if (uncoded[i].character == 'z')
                {
                    coded[i].number = 122;
                }
                else
                {
                    coded[i].number = 35;
                }

                int M = coded[i].number;
                long C=1;
                
                C = 1 % n;
                C = (M * C) % n;    //1

                C = (C * C) % n;

                C = (C * C) % n;
                C = (M * C) % n;    //1

                C = (C * C) % n;
                C = (M * C) % n;    //1
                coded[i].code = (int) C;
            });
            return;
        }//kódolás
        static void CodedFileDump(data2[] coded)
        {
            StreamWriter iro = new StreamWriter("coded_text2.txt");
            for (int i = 0; i < coded.Length; i++)
            {
                iro.Write(coded[i].code + " ");
            }
            iro.Close();

        }//kódolt szöveg kiírása
        static void Decoding(data2[] coded, data[] uncoded)
        {
            int p = 1039;
            int q = 2617;
            //int p = 313;
            //int q = 157;
            int n = p * q;
            int e = 11;
            int d = ((7 * (p - 1) * (q - 1)) + 1) / e;  //1727987
            
            Parallel.For(0, coded.Length, (i) =>
            {
                long C;
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
        static void DecodedFileDump(data[] uncoded)
        {
            StreamWriter iro = new StreamWriter("decoded_text2.txt");
            for (int i = 0; i < uncoded.Length; i++)
            {
                iro.Write(uncoded[i].new_character + " ");
            }
            iro.Close();
        }//dekódolt szöveg kiírása
        static void runtime_display(TimeSpan ts_fulltime, TimeSpan ts_encoding_time, TimeSpan ts_decoding_time)
        {
            StreamWriter iro = new StreamWriter("runtime2.txt",true);
            iro.Write(ts_fulltime.TotalMilliseconds + "; " + ts_encoding_time.TotalMilliseconds + "; " + ts_decoding_time.TotalMilliseconds); //mérési időket behelyettesíteni
            iro.Write("\n");
            iro.Close();
        }//futási idők kiírása
    }
}
