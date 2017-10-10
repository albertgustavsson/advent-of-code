using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _01p2._2
{
    class Program
    {
        static void Main(string[] args)
        {
            bool cont = true;
            char turn, dir = 'N';
            int[] x = new int[1000], y = new int[1000];
            int length, k = 0, coordx = 0, coordy = 0;

            string input = System.IO.File.ReadAllText(@"C:\users\albgus02\GoogleDrive\AdventOfCode\2016\01\p2/input.txt").Replace(" ", "");
            string[] inst = input.Split(',');
            for (int i = 0; i < inst.Length; i++)
            {
                string activeinst = inst[i];
                turn = activeinst[0];
                activeinst = activeinst.Replace("R", "").Replace("L", "");
                length = int.Parse(activeinst);
                if (turn == 'R')
                {
                    if (dir == 'N')
                    {
                        dir = 'E';
                    }
                    else if (dir == 'E')
                    {
                        dir = 'S';
                    }
                    else if (dir == 'S')
                    {
                        dir = 'W';
                    }
                    else if (dir == 'W')
                    {
                        dir = 'N';
                    }
                }
                else if (turn == 'L')
                {
                    if (dir == 'N')
                    {
                        dir = 'W';
                    }
                    else if (dir == 'W')
                    {
                        dir = 'S';
                    }
                    else if (dir == 'S')
                    {
                        dir = 'E';
                    }
                    else if (dir == 'E')
                    {
                        dir = 'N';
                    }
                }
                for (int j = 0; j < length; j++)
                {
                    x[k] = coordx;
                    y[k] = coordy;
                    if (dir == 'N')
                    {
                        coordy++;
                    }
                    else if (dir == 'E')
                    {
                        coordx++;
                    }
                    else if (dir == 'S')
                    {
                        coordy--;
                    }
                    else if (dir == 'W')
                    {
                        coordx--;
                    }
                    Console.WriteLine("x: " + coordx + " , y: " + coordy);
                    for (int l = 0; l < x.Length; l++)
                    {
                        if (x[l] == coordx && y[l] == coordy)
                        {
                            cont = false;
                            break;
                        }
                    }
                    if (cont == false)
                    {
                        break;
                    }
                    k++;
                }
                if (cont == false)
                {
                    break;
                }
            }
            Console.WriteLine("Stannade på " + coordx + " , " + coordy);
            Console.ReadKey();
        }
    }
}
