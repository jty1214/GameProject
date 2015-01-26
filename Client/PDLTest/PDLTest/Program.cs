using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDLTest
{
    class Program
    {
        static void Main(string[] args)
        {
            PDL.RESPONSE_FRIEND_LIST_READ pkt = new PDL.RESPONSE_FRIEND_LIST_READ();

            String[] Name = { "세이라", "카디스 에트라마 디 라이제르", "ㅏㅡㅏㅡㅏㅡㅏㅡㅏㅡㅏㅡ", "Kim John", "John Kim" };
            Int64[] ServerId = { 102938102948901, 120934810293, 12, 012938012938, 34124124142 };
            Int32[] Grade = { 1, 4, 3, 4, 4 };
            Int32[] SubGrade = { 1, 3, 5, 7, 11 };
            for (int i = 0; i < 5; i++)
            {
                PDL.RESPONSE_FRIEND_LIST_READ.FRIEND_LIST element = new PDL.RESPONSE_FRIEND_LIST_READ.FRIEND_LIST();
                element.userName = Name[i];
                element.userServerId = ServerId[i];
                element.userGrade = Grade[i];
                element.userSubGrade = SubGrade[i];

                pkt.friendList.Add(element);

                Int32 StreamLength = pkt.GetStreamLength();
                Console.WriteLine("Stream Length : " + StreamLength);
                Byte[] stream = new Byte[StreamLength];
                pkt.Serialize(stream);
                Console.Write("Buffer : ");
                for (int j = 0; j < stream.Length; j++) Console.Write(stream[j] + " ");
                Console.WriteLine("");
            }

            Int32 SreamLength = pkt.GetStreamLength();
        }
    }
}
