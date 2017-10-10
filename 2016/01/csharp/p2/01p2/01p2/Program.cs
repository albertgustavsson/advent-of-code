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
            int NS = 0, EW = 0, blocks = 0, i, j, k = 1, l, m = 0, n, o = 1, dubbelkoordinatskriv = 0;
            int[] x = new int[1000], y = new int[1000], X = new int[500], Y = new int[500];
            string way = "N";

            string input = System.IO.File.ReadAllText(@"C:\Users\albgus02\GoogleDrive\AdventOfCode\2016\01\p2\test.txt").Replace(" ", "");
            
            string[] instructions = input.Split(',');

            for (i = 0; i < instructions.Length; i++)
            {
                string inst = instructions[i];
                if (inst[0] == 'R')
                {
                    if (way == "N") { way = "E"; }
                    else if (way == "E") { way = "S"; }
                    else if (way == "S") { way = "W"; }
                    else if (way == "W") { way = "N"; }
                }
                else if (inst[0] == 'L')
                {
                    if (way == "N") { way = "W"; }
                    else if (way == "W") { way = "S"; }
                    else if (way == "S") { way = "E"; }
                    else if (way == "E") { way = "N"; }
                }
                inst = inst.Replace("R", "").Replace("L", "");
                blocks = int.Parse(inst);
                
                if (way == "N")
                {
                    for (j = 0; j < blocks; j++)
                    {
                        o = 0;
                        for (n = 0; n < 1000; n++)      //Kollar tidigare koordinater
                        {
                            if (x[o] == EW && y[o] == NS)       //Om nuvarande koordinater besökts tidigare
                            {
                                Y[m] = NS;      //Sparar matchande koordinater
                                X[m] = EW;
                                m++;
                            }
                            o++;
                        }
                        NS++;       //Går ett kvarter mot norr
                        x[k] = EW;      //Sparar nuvarande koordinater
                        y[k] = NS;
                        k++;
                    }
                }
                else if (way == "E")
                {
                    for (j = 0; j < blocks; j++)
                    {
                        m = 0;
                        for (n = 0; n < 500; n++)      //Kollar tidigare koordinater
                        {
                            if (x[n] == EW && y[n] == NS)       //Om nuvarande koordinater besökts tidigare
                            {
                                Y[m] = NS;      //Sparar matchande koordinater
                                X[m] = EW;
                                m++;
                            }
                        }
                        EW++;       //Går ett kvarter mot öst
                        x[k] = EW;      //Sparar nuvarande koordinater
                        y[k] = NS;
                        k++;
                    }
                }
                else if (way == "S")
                {
                    for (j = 0; j < blocks; j++)
                    {
                        m = 0;
                        for (n = 0; n < 500; n++)      //Kollar tidigare koordinater
                        {
                            if (x[n] == EW && y[n] == NS)       //Om nuvarande koordinater besökts tidigare
                            {
                                Y[m] = NS;      //Sparar matchande koordinater
                                X[m] = EW;
                                m++;
                            }
                        }
                        NS--;       //Går ett kvarter mot syd
                        x[k] = EW;      //Sparar nuvarande koordinater
                        y[k] = NS;
                        k++;
                    }
                }
                else if (way == "W")
                {
                    for (j = 0; j < blocks; j++)
                    {
                        m = 0;
                        for (n = 0; n < 500; n++)      //Kollar tidigare koordinater
                        {
                            if (x[n] == EW && y[n] == NS)       //Om nuvarande koordinater besökts tidigare
                            {
                                Y[m] = NS;      //Sparar matchande koordinater
                                X[m] = EW;
                                m++;
                            }
                        }
                        EW--;       //Går ett kvarter mot väst
                        x[k] = EW;      //Sparar nuvarande koordinater
                        y[k] = NS;
                        k++;
                    }
                }
            }
            for (l = 0; l < x.Length; l++)
            {
                Console.WriteLine("x: " + x[l] + ", y: " + y[l]);
            }

            Console.WriteLine("Santa found his own footprints in these locations:");
            for (dubbelkoordinatskriv = 0; dubbelkoordinatskriv < 100; dubbelkoordinatskriv++)
            {
                Console.WriteLine("x: " + X[dubbelkoordinatskriv] + ", y: " + Y[dubbelkoordinatskriv]);
            }

            Console.WriteLine("Santa claus found his own footprints at x: " + X[1] + ", y: " + Y[1] + ", Which means he's " + (Math.Abs(X[1])+Math.Abs(Y[1])) + " blocks away from his start position.");
            Console.WriteLine("Santa claus found Easter Bunny HQ at " + EW + " blocks EW and " + NS + " blocks NS. This is " + (Math.Abs(NS) + Math.Abs(EW)) + " blocks away from his start position");
            Console.ReadKey();
        }
    }
}
