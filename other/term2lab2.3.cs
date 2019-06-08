/*
 * Дана строка, содержащая число с десятичной точкой. 
 * Преобразовать эту строку в число действительного типа 
 * (не пользуясь стандартным Parse/TryParse).
 */

using System;

namespace Lab2_3
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            var num = Console.ReadLine().Split('.');
            double ans = 0.0;
            for (int letter = 0; letter < num[0].Length; letter++)
            {
                ans += (num[0][letter] - '0') * Math.Pow(10, num[0].Length - letter - 1);
            }
            for (int letter = 0; letter < num[1].Length; letter++)
            {
                ans += (num[1][letter] - '0') * Math.Pow(10, -1 * (letter + 1));
            }
            Console.Write(ans.ToString());
        }
    }
}