﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using System.Xml;
using System.IO;

namespace PDL.Helper
{
    public static class XMLReadHelper
    {
        public static bool XMLParsing(ref String Parser, XmlTextReader Reader, StreamWriter Log)
        {
            try
            {
                while (Reader.Read())
                {
                    switch (Reader.NodeType)
                    {
                        case XmlNodeType.Element:
                            Parser += "Node:" + Reader.Name + ":" + Reader.Depth + ";";

                            while (Reader.MoveToNextAttribute())
                            {
                                Parser += "Attribute:" + Reader.Name + ":" + Reader.Value + ";";
                            }
                            break;
                        case XmlNodeType.EndElement:
                            Parser += "EndNode:" + Reader.Name + ":" + Reader.Depth + ";";
                            break;
                        case XmlNodeType.Text: break;
                        case XmlNodeType.Whitespace: break;
                    }
                }
            }
            catch (FileNotFoundException e)
            {
                Log.WriteLine(e);
                return false;
            }
            catch (DirectoryNotFoundException e)
            {
                Log.WriteLine(e);
                return false;
            }
            catch (InvalidOperationException e)
            {
                Log.WriteLine(e);
                return false;
            }
            catch (UriFormatException e)
            {
                Log.WriteLine(e);
                return false;
            }
            return true;
        }

        public static void WriteTime(this StreamWriter Log)
        {
            Log.WriteLine("(" + TimeZone.CurrentTimeZone.ToLocalTime(DateTime.Now).ToString() + ")");
        }
    }
}
