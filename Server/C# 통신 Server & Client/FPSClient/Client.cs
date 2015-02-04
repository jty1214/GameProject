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

            TcpClient client = new TcpClient(ip, Int32.Parse(port));
            NetworkStream ns = client.GetStream();

            StreamWriter writer = new StreamWriter(ns);
            Byte[] Request_Friend_List_Write_Stream = GetPacketStream();
            {
                // 길이 쏘고
                Byte[] send_len = BitConverter.GetBytes(Request_Friend_List_Write_Stream.Length);
                String tmp = Encoding.GetEncoding("euc-kr").GetString(send_len, 0, send_len.Length);
                Char[] buff = tmp.ToCharArray();
                writer.Write(buff, 0, sizeof(Int32));
            }
            {
                // 내용 쏘고
                String tmp = Encoding.GetEncoding("euc-kr").GetString(Request_Friend_List_Write_Stream);
                Char[] buff = tmp.ToCharArray();
                writer.Write(buff, 0, Request_Friend_List_Write_Stream.Length);
            }

            StreamReader reader = new StreamReader(ns);
            Int32 Response_Friend_List_Read_Length = 0;
            Byte[] stream;
            {
                // 길이 읽고
                Char[] buff = new Char[sizeof(Int32)];
                reader.Read(buff, 0, sizeof(Int32));
                Byte[] len = Encoding.GetEncoding("euc-kr").GetBytes(buff);
                Response_Friend_List_Read_Length = BitConverter.ToInt32(len, 0);
            }
            {
                // 내용 읽고
                Char[] buff = new Char[Response_Friend_List_Read_Length];
                reader.Read(buff, 0, Response_Friend_List_Read_Length);
                stream = Encoding.GetEncoding("euc-kr").GetBytes(buff);
            }
            var Response_Friend_List_Read_pkt = GetPacket(stream);
            
            foreach( PDL.RESPONSE_FRIEND_LIST_READ.FRIEND_LIST it in Response_Friend_List_Read_pkt.friendList )
            {
                Console.WriteLine("User Name : " + it.userName);
                Console.WriteLine("User ServerId : " + it.userServerId);
                Console.WriteLine("User Grade : " + it.userGrade);
                Console.WriteLine("User SubGrade: " + it.userSubGrade);
            }

            writer.Close();
            reader.Close();
            client.Close();
        }

        static Byte[] GetPacketStream()
        {
            PDL.REQUEST_FRIEND_LIST_WRITE pkt = new PDL.REQUEST_FRIEND_LIST_WRITE();
            Int32 pkt_length = pkt.GetStreamLength();
            Byte[] stream = new Byte[pkt_length];
            pkt.Serialize(stream);
            return stream;
        }

        static PDL.RESPONSE_FRIEND_LIST_READ GetPacket( Byte[] stream )
        {
            var pkt = new PDL.RESPONSE_FRIEND_LIST_READ();
            pkt.Parsing(stream);

            return pkt;
        }
    }
}
