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
            StreamReader read=new StreamReader("text_Orkeny4.txt");
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
                switch(uncoded[i].character)
                {
                    case ' ':
                        coded[i].number = 32;
                        break;
                    case '!':
                        coded[i].number = 33;
                        break;
                    case '%':
                        coded[i].number = 37;
                        break;
                    case ')':
                        coded[i].number = 41;
                        break;
                    case '(':
                        coded[i].number = 40;
                        break;
                    case '+':
                        coded[i].number = 43;
                        break;
                    case ',':
                        coded[i].number = 44;
                        break;
                    case '-':
                        coded[i].number = 45;
                        break;
                    case '.':
                        coded[i].number = 46;
                        break;
                    case '/':
                        coded[i].number = 47;
                        break;
                    case '0':
                        coded[i].number = 48;
                        break;
                    case '1':
                        coded[i].number = 49;
                        break;
                    case '2':
                        coded[i].number = 50;
                        break;
                    case '3':
                        coded[i].number = 51;
                        break;
                    case '4':
                        coded[i].number = 52;
                        break;
                    case '5':
                        coded[i].number = 53;
                        break;
                    case '6':
                        coded[i].number = 54;
                        break;
                    case '7':
                        coded[i].number = 55;
                        break;
                    case '8':
                        coded[i].number = 56;
                        break;
                    case '9':
                        coded[i].number = 57;
                        break;
                    case ':':
                        coded[i].number = 58;
                        break;
                    case ';':
                        coded[i].number = 59;
                        break;
                    case '<':
                        coded[i].number = 60;
                        break;
                    case '=':
                        coded[i].number = 61;
                        break;
                    case '>':
                        coded[i].number = 62;
                        break;
                    case '?':
                        coded[i].number = 63;
                        break;
                    case '@':
                        coded[i].number = 64;
                        break;
                    case 'A': 
                        coded[i].number = 65;
                        break;
                    case 'Á':
                        coded[i].number = 65;
                        break;
                    case 'B':
                        coded[i].number = 66;
                        break;
                    case 'C':
                        coded[i].number = 67;
                        break;
                    case 'D':
                        coded[i].number = 68;
                        break;
                    case 'E':
                        coded[i].number = 69;
                        break;
                    case 'É':
                        coded[i].number = 69;
                        break;
                    case 'F':
                        coded[i].number = 70;
                        break;
                    case 'G':
                        coded[i].number = 71;
                        break;
                    case 'H':
                        coded[i].number = 72;
                        break;
                    case 'I':
                        coded[i].number = 73;
                        break;
                    case 'J':
                        coded[i].number = 74;
                        break;
                    case 'K':
                        coded[i].number = 75;
                        break;
                    case 'L':
                        coded[i].number = 76;
                        break;
                    case 'M':
                        coded[i].number = 77;
                        break;
                    case 'N':
                        coded[i].number = 78;
                        break;
                    case 'O':
                        coded[i].number = 79;
                        break;
                    case 'Ó':
                        coded[i].number = 79;
                        break;
                    case 'Ö':
                        coded[i].number = 79;
                        break;
                    case 'Ő':
                        coded[i].number = 79;
                        break;
                    case 'P':
                        coded[i].number = 80;
                        break;
                    case 'Q':
                        coded[i].number = 81;
                        break;
                    case 'R':
                        coded[i].number = 82;
                        break;
                    case 'S':
                        coded[i].number = 83;
                        break;
                    case 'T':
                        coded[i].number = 84;
                        break;
                    case 'U':
                        coded[i].number = 85;
                        break;
                    case 'Ú':
                        coded[i].number = 85;
                        break;
                    case 'Ü':
                        coded[i].number = 85;
                        break;
                    case 'Ű':
                        coded[i].number = 85;
                        break;
                    case 'V':
                        coded[i].number = 86;
                        break;
                    case 'W':
                        coded[i].number = 87;
                        break;
                    case 'X':
                        coded[i].number = 88;
                        break;
                    case 'Y':
                        coded[i].number = 89;
                        break;
                    case 'Z':
                        coded[i].number = 90;
                        break;
                    case 'a':
                        coded[i].number = 97;
                        break;
                    case 'á':
                        coded[i].number = 97;
                        break;
                    case 'b':
                        coded[i].number = 98;
                        break;
                    case 'c':
                        coded[i].number = 99;
                        break;
                    case 'd':
                        coded[i].number = 100;
                        break;
                    case 'e':
                        coded[i].number = 101;
                        break;
                    case 'é':
                        coded[i].number = 101;
                        break;
                    case 'f':
                        coded[i].number = 102;
                        break;
                    case 'g':
                        coded[i].number = 103;
                        break;
                    case 'h':
                        coded[i].number = 104;
                        break;
                    case 'i':
                        coded[i].number = 105;
                        break;
                    case 'í':
                        coded[i].number = 105;
                        break;
                    case 'j':
                        coded[i].number = 106;
                        break;
                    case 'k':
                        coded[i].number = 107;
                        break;
                    case 'l':
                        coded[i].number = 108;
                        break;
                    case 'm':
                        coded[i].number = 109;
                        break;
                    case 'n':
                        coded[i].number = 110;
                        break;
                    case 'o':
                        coded[i].number = 111;
                        break;
                    case 'ó':
                        coded[i].number = 111;
                        break;
                    case 'ő':
                        coded[i].number = 111;
                        break;
                    case 'ö':
                        coded[i].number = 111;
                        break;
                    case 'p':
                        coded[i].number = 112;
                        break;
                    case 'q':
                        coded[i].number = 113;
                        break;
                    case 'r':
                        coded[i].number = 114;
                        break;
                    case 's':
                        coded[i].number = 115;
                        break;
                    case 't':
                        coded[i].number = 116;
                        break;
                    case 'u':
                        coded[i].number = 117;
                        break;
                    case 'ú':
                        coded[i].number = 117;
                        break;
                    case 'ü':
                        coded[i].number = 117;
                        break;
                    case 'ű':
                        coded[i].number = 117;
                        break;
                    case 'v':
                        coded[i].number = 118;
                        break;
                    case 'w':
                        coded[i].number = 119;
                        break;
                    case 'x':
                        coded[i].number = 120;
                        break;
                    case 'y':
                        coded[i].number = 121;
                        break;
                    case 'z':
                        coded[i].number = 122;
                        break;
                    default:
                        coded[i].number = 35;
                        break;
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
