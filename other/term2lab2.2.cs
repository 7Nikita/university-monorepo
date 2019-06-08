/*
 * В заданной строке поменять порядок слов на обратный 
 * (слова разделены пробелами).
 */

using System;
using System.Text;

namespace Lab2_2
{
    class MainClass
    {
        public static void Main(string[] args)
        {  
            string text = ' ' + Console.ReadLine();
            StringBuilder sb = new StringBuilder();
            for (int i = text.Length - 1; i >= 0; i--){
                if (text[i] == ' ')
                {
                    for (int j = i + 1; j != text.Length && text[j] != ' '; j++)
                        sb.Append(text[j]);
                    sb.Append(text[i]);
                }
            }
            text = sb.ToString();
            Console.WriteLine(text);
        }
    }
}