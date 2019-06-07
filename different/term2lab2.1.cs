/*
 *    Дана строка, слова которой разделены пробелами. 
 *    Распознать в ней слова, являющиеся числами в 
 *    шестнадцатеричной системе счисления,
 *    и вывести их десятичный эквивалент.
 */

using System;

namespace Lab2_1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            var wordsArray = Console.ReadLine().Split();
            foreach (var word in wordsArray)
            {
                try
                {
                var decimalNumber = int.Parse(word, System.Globalization.NumberStyles.HexNumber);
                    Console.WriteLine(word + ": " + decimalNumber.ToString());
                }
                catch
                {
                    continue;
                }
            }
            Console.WriteLine("There are no more words.");
        }
    }
}
