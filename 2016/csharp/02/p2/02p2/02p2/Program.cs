using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _02p1
{
    class Program
    {
        static void Main(string[] args)
        {
            char btn = '5';
            int i = 0, j = 0;
            char[] BTN = new char[5];
            string[] input = System.IO.File.ReadAllLines(@"C:\users\albgus02\GoogleDrive\AdventOfCode\2016\02\p2\input.txt");
            foreach (string line in input)
            {
                i = 0;
                foreach (char inst in line)
                {
                    if (inst == 'U')
                    {
                        if (btn == '1') { btn = '1'; }
                        else if (btn == '2') { btn = '2'; }
                        else if (btn == '3') { btn = '1'; }
                        else if (btn == '4') { btn = '4'; }
                        else if (btn == '5') { btn = '5'; }
                        else if (btn == '6') { btn = '2'; }
                        else if (btn == '7') { btn = '3'; }
                        else if (btn == '8') { btn = '4'; }
                        else if (btn == '9') { btn = '9'; }
                        else if (btn == 'A') { btn = '6'; }
                        else if (btn == 'B') { btn = '7'; }
                        else if (btn == 'C') { btn = '8'; }
                        else if (btn == 'D') { btn = 'B'; }
                    }
                    else if (inst == 'D')
                    {
                        if (btn == '1') { btn = '3'; }
                        else if (btn == '2') { btn = '6'; }
                        else if (btn == '3') { btn = '7'; }
                        else if (btn == '4') { btn = '8'; }
                        else if (btn == '5') { btn = '5'; }
                        else if (btn == '6') { btn = 'A'; }
                        else if (btn == '7') { btn = 'B'; }
                        else if (btn == '8') { btn = 'C'; }
                        else if (btn == '9') { btn = '9'; }
                        else if (btn == 'A') { btn = 'A'; }
                        else if (btn == 'B') { btn = 'D'; }
                        else if (btn == 'C') { btn = 'C'; }
                        else if (btn == 'D') { btn = 'D'; }
                    }
                    else if (inst == 'L')
                    {
                        if (btn == '1') { btn = '1'; }
                        else if (btn == '2') { btn = '2'; }
                        else if (btn == '3') { btn = '2'; }
                        else if (btn == '4') { btn = '3'; }
                        else if (btn == '5') { btn = '5'; }
                        else if (btn == '6') { btn = '5'; }
                        else if (btn == '7') { btn = '6'; }
                        else if (btn == '8') { btn = '7'; }
                        else if (btn == '9') { btn = '8'; }
                        else if (btn == 'A') { btn = 'A'; }
                        else if (btn == 'B') { btn = 'A'; }
                        else if (btn == 'C') { btn = 'B'; }
                        else if (btn == 'D') { btn = 'D'; }
                    }
                    else if (inst == 'R')
                    {
                        if (btn == '1') { btn = '1'; }
                        else if (btn == '2') { btn = '3'; }
                        else if (btn == '3') { btn = '4'; }
                        else if (btn == '4') { btn = '4'; }
                        else if (btn == '5') { btn = '6'; }
                        else if (btn == '6') { btn = '7'; }
                        else if (btn == '7') { btn = '8'; }
                        else if (btn == '8') { btn = '9'; }
                        else if (btn == '9') { btn = '9'; }
                        else if (btn == 'A') { btn = 'B'; }
                        else if (btn == 'B') { btn = 'C'; }
                        else if (btn == 'C') { btn = 'C'; }
                        else if (btn == 'D') { btn = 'D'; }
                    }
                    if (i == (line.Length - 1))
                    {
                        BTN[j] = btn;
                        j++;
                    }
                    i++;
                }
            }
            Console.WriteLine("The code is " + BTN[0] + BTN[1] + BTN[2] + BTN[3] + BTN[4]);
            Console.ReadKey();
        }
    }
}
