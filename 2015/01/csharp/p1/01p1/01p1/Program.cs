using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _01p1
{
    class Program
    {
        static void Main(string[] args)
        {
            int level = 0;
            string line = "";
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\albgus02\GoogleDrive\AdventOfCode\2015\01\p1\input.txt");
            
            for (int j = 0; j < lines.Length; j++)
            {
                line = lines[j];

                for (int i = 0; i < line.Length; i++)
                {
                    if (line[i] == '(')
                    {
                        level++;
                    }
                    else if (line[i] == ')')
                    {
                        level--;
                    }
                }
            }

            Console.WriteLine("Santa claus followed the instructions to level " + level);
            Console.ReadKey();
        }
    }
}
