using System;


namespace HeaderTool
{
    class Program
    {
        static void Main(string[] args)
        {
            CPPHeaderFileParser parser = new CPPHeaderFileParser();

            if (args.Length > 0)
            {
                foreach (string st in args)
                    parser.ParseCPPHeader(st);
            }

           // parser.ParseCPPHeader("C:\\Users\\Darius Bigbee\\Desktop\\IMG_20200803_210809404.cpp");

            System.Console.ReadLine();
        }
    }
}
