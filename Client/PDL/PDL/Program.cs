using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

namespace PDL
{
    class Program
    {
        private static String PDLFileName = "PDL.xml";
        static void Main(string[] args)
        {
            String DirectoryPath = Directory.GetCurrentDirectory();
            String GeneratePath = ".";
            if (args.Length >= 1)
            {
                DirectoryPath = args[0];
            }
            if (args.Length >= 2)
            {
                GeneratePath = args[1];
            }

            String PDLPath = DirectoryPath + "\\" + PDLFileName;
            XmlTextReader reader = null;
            reader = new XmlTextReader(PDLPath);

            try
            {
                while (reader.Read())
                {
                    switch (reader.NodeType)
                    {
                        case XmlNodeType.Element:
                            Console.WriteLine("Node Name : " + reader.Name + ", Depth : " + reader.Depth);

                            while (reader.MoveToNextAttribute())
                            {
                                Console.WriteLine("Attribute Name : " + reader.Name);
                                Console.WriteLine("Attribute Value : " + reader.Value);
                            }
                            break;
                        case XmlNodeType.EndElement:
                            Console.WriteLine("EndNode :" + reader.Name);
                            break;

                        case XmlNodeType.Text: break;
                        case XmlNodeType.Whitespace: break;
                    }
                }
            }
            catch (FileNotFoundException)
            {
                Console.WriteLine(DirectoryPath.Impact() + "에서 " + PDLFileName.Impact() + "을 찾을 수 없습니다.");
                return;
            }
            catch (DirectoryNotFoundException)
            {
                Console.WriteLine(DirectoryPath.Impact() + "를 찾을 수 없습니다.");
                return;
            }
            catch (InvalidOperationException)
            {
                Console.WriteLine(PDLPath.Impact() + "가 비어있습니다. 채우는 부분을 확인해주세요.");
                return;
            }
            catch (UriFormatException)
            {
                Console.WriteLine(PDLPath.Impact() + "가 유효하지 않습니다. 확인해주세요.");
                return;
            }
        }
    }

    static class StringHelper
    {
        public static String Impact(this String name)
        {
            return "[" + name + "]";
        }
    }
}