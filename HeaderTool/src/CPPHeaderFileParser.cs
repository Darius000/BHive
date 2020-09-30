using HeaderTool.src;
using System;

namespace HeaderTool
{
    public class CPPHeaderFileParser
    {
        public CPPHeaderFileParser()
        {

        }
        public CPPHeaderFileParser(string file)
        {
            ParseCPPHeader(file);
        }

        public void ParseCPPHeader(string file)
        {
            if (!ExtChecker.IsValidExtension(file))
                return;

            currentFile = file;

            int lastslash = currentFile.LastIndexOf('\\');
            bool hasSlash = lastslash != -1;

            System.Console.WriteLine($"{lastslash}, {hasSlash}");

            int length = currentFile.Length;
            int start = hasSlash ? lastslash + 1 : 0;
            int offset = length - start;
            currentFileName = currentFile.Substring(start, offset);

            System.Console.WriteLine("Parsing " + currentFileName);

            System.Console.ReadLine();
        }

        private void ParseFileContents(string file)
        {

        }

        private void GenerateFile(string file)
        {

        }

        private string currentFile;
        private string currentFileName;
        private string outputPath;
        private CheckExtension ExtChecker = new CheckExtension();
    }
}