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
            var pkt_writer = new PDL.TEST_TT_PACKET_BOTH();
            pkt_writer.keyword = "안Hello녕";

            Byte[] stream = new Byte[pkt_writer.GetStreamLength()];
            pkt_writer.Serialize(stream);

            //TODO : 테스트할 방법들 결정하기
            var pkt_reader = new PDL.TEST_TT_PACKET_BOTH();
            pkt_reader.Parsing(stream);
            Console.WriteLine(pkt_reader.keyword);
        }
    }
}
