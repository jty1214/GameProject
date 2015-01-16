using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace FPSClient
{
    class Client
    {
        static void Main(string[] args)
        {
            string ip = "127.0.0.1";
            string port = "9000";
            string msg = "Hello World!";

            TcpClient client = new TcpClient(ip, Int32.Parse(port));
            NetworkStream ns = client.GetStream();
            StreamWriter writer = new StreamWriter(ns);

            writer.WriteLine(msg);
            writer.Flush();
            Console.WriteLine(msg + "를 전송합니다.");

            StreamReader reader = new StreamReader(ns);

            string msg1 = reader.ReadLine();
            Console.WriteLine("[Echo1]: " + msg1);

            writer.Close();
            reader.Close();
            client.Close();
        }
    }
}
