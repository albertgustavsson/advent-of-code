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
            int NS = 0, EW = 0, blocks = 0;
            string[] instructions = { };
            string way = "north";

            string text = System.IO.File.ReadAllText(@"C:\Users\albgus02\GoogleDrive\AdventOfCode\2016\01\p1\input.txt").Replace(" ", "");

            instructions = text.Split(',');

            for (int i = 0; i < instructions.Length; i++)
            {
                string inst = instructions[i];
                if (inst[0] == 'R')
                {
                    if (way == "north") { way = "east"; }
                    else if (way == "east") { way = "south"; }
                    else if (way == "south") { way = "west"; }
                    else if (way == "west") { way = "north"; }
                }
                else if (inst[0] == 'L')
                {
                    if (way == "north") { way = "west"; }
                    else if (way == "west") { way = "south"; }
                    else if (way == "south") { way = "east"; }
                    else if (way == "east") { way = "north"; }
                }
                inst = inst.Replace("R", "").Replace("L", "").Replace(" ", "");
                blocks = int.Parse(inst);
                if (way == "north")
                {
                    NS = NS + blocks;
                }
                else if (way == "east")
                {
                    EW = EW + blocks;
                }
                else if (way == "south")
                {
                    NS = NS - blocks;
                }
                else
                {
                    EW = EW - blocks;
                }
            }
            int dist = Math.Abs(NS) + Math.Abs(EW);
            Console.WriteLine("Santa claus has totally travelled " + dist + " blocks");
            Console.ReadKey();
        }
    }
}
