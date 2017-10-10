using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] side = new int[3];
            int[] sidesint = new int[3];
            string[] input = System.IO.File.ReadAllLines(@"C:\users\albgus02\GoogleDrive\AdventOfCode\2016\03\p1\test.txt");
            foreach (string line in input)
            {
                string[] sides = line.Trim().Split(' ');
                sidesint[0] = int.Parse(sides[0]);
                sidesint[1] = int.Parse(sides[1]);
                sidesint[2] = int.Parse(sides[2]);
            }
            int temp;
            if (sidesint[0] <= sidesint[1] && sidesint[1] <= sidesint[2])
            {
                temp = sidesint[0];
                sidesint[0] = sidesint[2];
                sidesint[2] = temp;
            }
            else if (sidesint[0] <= sidesint[2] && sidesint[2] <= sidesint[1])
            {
                temp = sidesint[0];
                sidesint[0] = sidesint[1];
                sidesint[1] = sidesint[2];
                sidesint[2] = temp;
            }
            else if (sidesint[1] <= sidesint[2] && sidesint[2] <= sidesint[0])
            {
                temp = sidesint[1];
                sidesint[1] = sidesint[2];
                sidesint[2] = temp;
            }
            else if (sidesint[1] <= sidesint[0] && sidesint[0] <= sidesint[2])
            {
                temp = sidesint[1];
                sidesint[1] = sidesint[0];
                sidesint[0] = sidesint[2];
                sidesint[2] = temp;
            }
            else if (sidesint[2] <= sidesint[0] && sidesint[0] <= sidesint[1])
            {
                temp = sidesint[0];
                sidesint[0] = sidesint[1];
                sidesint[1] = temp;
            }
            else if (sidesint[2] <= sidesint[1] && sidesint[1] <= sidesint[0])
            {

            }
            Console.ReadKey();
        }
    }
}
