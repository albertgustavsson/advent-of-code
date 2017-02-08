using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _01p2
{
    class Program
    {
        static void Main(string[] args)
        {
            int level = 0, place = 0;
            bool cont = true;
            string line = "";
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\albgus02\GoogleDrive\AdventOfCode\2015\01\p2\input.txt");

            while (cont == true)
            {
                for (int j = 0; j < lines.Length; j++)
                {
                    line = lines[j];

                    for (int i = 0; i < line.Length; i++)
                    {
                        place++;

                        if (line[i] == '(')
                        {
                            level++;
                        }
                        else
                        {
                            level--;
                        }
                        if (level < 0)
                        {
                            cont = false;
                            break;
                        }
                    }
                    if (cont == false)
                    {
                        break;
                    }
                }
            }

            Console.WriteLine("Santa claus went into the basement when following character no." + place + " of the instructions.");
            Console.ReadKey();
        }
    }
}
