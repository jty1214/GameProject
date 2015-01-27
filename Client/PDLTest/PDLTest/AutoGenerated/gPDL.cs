using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL
{
  //Version:3
  public class REQUEST_ENTER_CHANNEL_WRITE
  {
    public Int32 world;
    public Int32 channel;
    public REQUEST_ENTER_CHANNEL_WRITE()
    {
      world= new Int32();
      channel= new Int32();
    }
    public Int32 GetStreamLength()
    {
      Int32 size = 0;
      size += sizeof(Int32);
      size += sizeof(Int32);
      return size;
    }
    public void Serialize(byte[] stream)
    {
      Int32 index = 0;
      foreach(byte worldi2 in BitConverter.GetBytes(world) )
      {
        stream[index++] = worldi2;
      }
      foreach(byte channeli2 in BitConverter.GetBytes(channel) )
      {
        stream[index++] = channeli2;
      }
    }
  }

  public class RESPONSE_ENTER_CHANNEL_READ
  {
    public Boolean valid;
    public Int64 enterChannelTime;
    public RESPONSE_ENTER_CHANNEL_READ()
    {
      valid= new Boolean();
      enterChannelTime= new Int64();
    }
    public void Parsing(byte[] stream)
    {
      Int32 index = 0;
      valid = BitConverter.ToBoolean(stream, index);
      index += sizeof(Boolean);
      enterChannelTime = BitConverter.ToInt64(stream, index);
      index += sizeof(Int64);
    }
  }

  public class REQUEST_FRIEND_LIST_WRITE
  {
    public REQUEST_FRIEND_LIST_WRITE()
    {
    }
    public Int32 GetStreamLength()
    {
      Int32 size = 0;
      return size;
    }
    public void Serialize(byte[] stream)
    {
    }
  }

  public class RESPONSE_FRIEND_LIST_READ
  {
    public class FRIEND_LIST
    {
      public String userName;
      public Int64 userServerId;
      public Int32 userGrade;
      public Int32 userSubGrade;

      public FRIEND_LIST()
      {
        userName= "";
        userServerId= new Int64();
        userGrade= new Int32();
        userSubGrade= new Int32();
      }
    }
    public List<FRIEND_LIST> friendList;
    public RESPONSE_FRIEND_LIST_READ()
    {
      friendList= new List<FRIEND_LIST>();
    }
    public void Parsing(byte[] stream)
    {
      Int32 index = 0;
      Int32 friendListLength2 = BitConverter.ToInt32(stream, index);
      index += sizeof(Int32);
      for(int friendListi2=0;friendListi2 < friendListLength2;friendListi2++)
      {
        FRIEND_LIST friendListit2 = new FRIEND_LIST();
        Int32 userNameLength3 = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        friendListit2.userName = Encoding.Default.GetString(stream, index, userNameLength3);
        index += userNameLength3;
        friendListit2.userServerId = BitConverter.ToInt64(stream, index);
        index += sizeof(Int64);
        friendListit2.userGrade = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        friendListit2.userSubGrade = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        friendList.Add(friendListit2);
      }
    }
  }

  public class TEST_TEMP_PACKET_BOTH
  {
    public class TEST_FIRST_LIST
    {
      public String stringFirstListVariable;
      public Int64 longFirstListVariable;
      public Int32 intFirstListVariable;
      public Boolean boolFirstListVariable;
      public class TEST_SECOND_LIST
      {
        public String stringSecondListVariable;
        public Int64 longSecondListVariable;
        public Int32 intSecondListVariable;
        public Boolean boolSecondListVariable;
        public class TEST_THIRD_LIST
        {
          public String stringThirdListVariable;
          public Int64 longThirdListVariable;
          public Int32 intThirdListVariable;
          public Boolean boolThirdListVariable;

          public TEST_THIRD_LIST()
          {
            stringThirdListVariable= "";
            longThirdListVariable= new Int64();
            intThirdListVariable= new Int32();
            boolThirdListVariable= new Boolean();
          }
        }
        public List<TEST_THIRD_LIST> thirdList;
        public String endofSecondVariable;

        public TEST_SECOND_LIST()
        {
          stringSecondListVariable= "";
          longSecondListVariable= new Int64();
          intSecondListVariable= new Int32();
          boolSecondListVariable= new Boolean();
          thirdList= new List<TEST_THIRD_LIST>();
          endofSecondVariable= "";
        }
      }
      public List<TEST_SECOND_LIST> secondList;
      public class TEST_SPECIAL_LIST
      {
        public String stringSpecialListVariable;
        public Int64 longSpecialListVariable;
        public Int32 intSpecialListVariable;
        public Boolean boolSpecialListVariable;

        public TEST_SPECIAL_LIST()
        {
          stringSpecialListVariable= "";
          longSpecialListVariable= new Int64();
          intSpecialListVariable= new Int32();
          boolSpecialListVariable= new Boolean();
        }
      }
      public List<TEST_SPECIAL_LIST> specialList;

      public TEST_FIRST_LIST()
      {
        stringFirstListVariable= "";
        longFirstListVariable= new Int64();
        intFirstListVariable= new Int32();
        boolFirstListVariable= new Boolean();
        secondList= new List<TEST_SECOND_LIST>();
        specialList= new List<TEST_SPECIAL_LIST>();
      }
    }
    public List<TEST_FIRST_LIST> firstList;
    public TEST_TEMP_PACKET_BOTH()
    {
      firstList= new List<TEST_FIRST_LIST>();
    }
    public Int32 GetStreamLength()
    {
      Int32 size = 0;
      size += sizeof(Int32);
      for(int firstListi2=0;firstListi2 < firstList.Count;firstListi2++)
      {
        size += sizeof(Int32);
        size += Encoding.Default.GetBytes(firstList[firstListi2].stringFirstListVariable).Length;
        size += sizeof(Int64);
        size += sizeof(Int32);
        size += sizeof(Boolean);
        size += sizeof(Int32);
        for(int secondListi3=0;secondListi3 < firstList[firstListi2].secondList.Count;secondListi3++)
        {
          size += sizeof(Int32);
          size += Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].stringSecondListVariable).Length;
          size += sizeof(Int64);
          size += sizeof(Int32);
          size += sizeof(Boolean);
          size += sizeof(Int32);
          for(int thirdListi4=0;thirdListi4 < firstList[firstListi2].secondList[secondListi3].thirdList.Count;thirdListi4++)
          {
            size += sizeof(Int32);
            size += Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].stringThirdListVariable).Length;
            size += sizeof(Int64);
            size += sizeof(Int32);
            size += sizeof(Boolean);
          }
          size += sizeof(Int32);
          size += Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].endofSecondVariable).Length;
        }
        size += sizeof(Int32);
        for(int specialListi3=0;specialListi3 < firstList[firstListi2].specialList.Count;specialListi3++)
        {
          size += sizeof(Int32);
          size += Encoding.Default.GetBytes(firstList[firstListi2].specialList[specialListi3].stringSpecialListVariable).Length;
          size += sizeof(Int64);
          size += sizeof(Int32);
          size += sizeof(Boolean);
        }
      }
      return size;
    }
    public void Serialize(byte[] stream)
    {
      Int32 index = 0;
      foreach(byte firstListi2 in BitConverter.GetBytes(firstList.Count) )
      {
        stream[index++] = firstListi2;
      }
      for(int firstListi2=0;firstListi2 < firstList.Count;firstListi2++)
      {
        foreach(byte stringFirstListVariablei3 in BitConverter.GetBytes(Encoding.Default.GetBytes(firstList[firstListi2].stringFirstListVariable).Length) )
        {
          stream[index++] = stringFirstListVariablei3;
        }
        foreach(byte stringFirstListVariablei3 in Encoding.Default.GetBytes(firstList[firstListi2].stringFirstListVariable) )
        {
          stream[index++] = stringFirstListVariablei3;
        }
        foreach(byte longFirstListVariablei3 in BitConverter.GetBytes(firstList[firstListi2].longFirstListVariable) )
        {
          stream[index++] = longFirstListVariablei3;
        }
        foreach(byte intFirstListVariablei3 in BitConverter.GetBytes(firstList[firstListi2].intFirstListVariable) )
        {
          stream[index++] = intFirstListVariablei3;
        }
        foreach(byte boolFirstListVariablei3 in BitConverter.GetBytes(firstList[firstListi2].boolFirstListVariable) )
        {
          stream[index++] = boolFirstListVariablei3;
        }
        foreach(byte secondListi3 in BitConverter.GetBytes(firstList[firstListi2].secondList.Count) )
        {
          stream[index++] = secondListi3;
        }
        for(int secondListi3=0;secondListi3 < firstList[firstListi2].secondList.Count;secondListi3++)
        {
          foreach(byte stringSecondListVariablei4 in BitConverter.GetBytes(Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].stringSecondListVariable).Length) )
          {
            stream[index++] = stringSecondListVariablei4;
          }
          foreach(byte stringSecondListVariablei4 in Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].stringSecondListVariable) )
          {
            stream[index++] = stringSecondListVariablei4;
          }
          foreach(byte longSecondListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].longSecondListVariable) )
          {
            stream[index++] = longSecondListVariablei4;
          }
          foreach(byte intSecondListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].intSecondListVariable) )
          {
            stream[index++] = intSecondListVariablei4;
          }
          foreach(byte boolSecondListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].boolSecondListVariable) )
          {
            stream[index++] = boolSecondListVariablei4;
          }
          foreach(byte thirdListi4 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList.Count) )
          {
            stream[index++] = thirdListi4;
          }
          for(int thirdListi4=0;thirdListi4 < firstList[firstListi2].secondList[secondListi3].thirdList.Count;thirdListi4++)
          {
            foreach(byte stringThirdListVariablei5 in BitConverter.GetBytes(Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].stringThirdListVariable).Length) )
            {
              stream[index++] = stringThirdListVariablei5;
            }
            foreach(byte stringThirdListVariablei5 in Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].stringThirdListVariable) )
            {
              stream[index++] = stringThirdListVariablei5;
            }
            foreach(byte longThirdListVariablei5 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].longThirdListVariable) )
            {
              stream[index++] = longThirdListVariablei5;
            }
            foreach(byte intThirdListVariablei5 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].intThirdListVariable) )
            {
              stream[index++] = intThirdListVariablei5;
            }
            foreach(byte boolThirdListVariablei5 in BitConverter.GetBytes(firstList[firstListi2].secondList[secondListi3].thirdList[thirdListi4].boolThirdListVariable) )
            {
              stream[index++] = boolThirdListVariablei5;
            }
          }
          foreach(byte endofSecondVariablei4 in BitConverter.GetBytes(Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].endofSecondVariable).Length) )
          {
            stream[index++] = endofSecondVariablei4;
          }
          foreach(byte endofSecondVariablei4 in Encoding.Default.GetBytes(firstList[firstListi2].secondList[secondListi3].endofSecondVariable) )
          {
            stream[index++] = endofSecondVariablei4;
          }
        }
        foreach(byte specialListi3 in BitConverter.GetBytes(firstList[firstListi2].specialList.Count) )
        {
          stream[index++] = specialListi3;
        }
        for(int specialListi3=0;specialListi3 < firstList[firstListi2].specialList.Count;specialListi3++)
        {
          foreach(byte stringSpecialListVariablei4 in BitConverter.GetBytes(Encoding.Default.GetBytes(firstList[firstListi2].specialList[specialListi3].stringSpecialListVariable).Length) )
          {
            stream[index++] = stringSpecialListVariablei4;
          }
          foreach(byte stringSpecialListVariablei4 in Encoding.Default.GetBytes(firstList[firstListi2].specialList[specialListi3].stringSpecialListVariable) )
          {
            stream[index++] = stringSpecialListVariablei4;
          }
          foreach(byte longSpecialListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].specialList[specialListi3].longSpecialListVariable) )
          {
            stream[index++] = longSpecialListVariablei4;
          }
          foreach(byte intSpecialListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].specialList[specialListi3].intSpecialListVariable) )
          {
            stream[index++] = intSpecialListVariablei4;
          }
          foreach(byte boolSpecialListVariablei4 in BitConverter.GetBytes(firstList[firstListi2].specialList[specialListi3].boolSpecialListVariable) )
          {
            stream[index++] = boolSpecialListVariablei4;
          }
        }
      }
    }
    public void Parsing(byte[] stream)
    {
      Int32 index = 0;
      Int32 firstListLength2 = BitConverter.ToInt32(stream, index);
      index += sizeof(Int32);
      for(int firstListi2=0;firstListi2 < firstListLength2;firstListi2++)
      {
        TEST_FIRST_LIST firstListit2 = new TEST_FIRST_LIST();
        Int32 stringFirstListVariableLength3 = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        firstListit2.stringFirstListVariable = Encoding.Default.GetString(stream, index, stringFirstListVariableLength3);
        index += stringFirstListVariableLength3;
        firstListit2.longFirstListVariable = BitConverter.ToInt64(stream, index);
        index += sizeof(Int64);
        firstListit2.intFirstListVariable = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        firstListit2.boolFirstListVariable = BitConverter.ToBoolean(stream, index);
        index += sizeof(Boolean);
        Int32 secondListLength3 = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        for(int secondListi3=0;secondListi3 < secondListLength3;secondListi3++)
        {
          TEST_FIRST_LIST.TEST_SECOND_LIST secondListit3 = new TEST_FIRST_LIST.TEST_SECOND_LIST();
          Int32 stringSecondListVariableLength4 = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          secondListit3.stringSecondListVariable = Encoding.Default.GetString(stream, index, stringSecondListVariableLength4);
          index += stringSecondListVariableLength4;
          secondListit3.longSecondListVariable = BitConverter.ToInt64(stream, index);
          index += sizeof(Int64);
          secondListit3.intSecondListVariable = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          secondListit3.boolSecondListVariable = BitConverter.ToBoolean(stream, index);
          index += sizeof(Boolean);
          Int32 thirdListLength4 = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          for(int thirdListi4=0;thirdListi4 < thirdListLength4;thirdListi4++)
          {
            TEST_FIRST_LIST.TEST_SECOND_LIST.TEST_THIRD_LIST thirdListit4 = new TEST_FIRST_LIST.TEST_SECOND_LIST.TEST_THIRD_LIST();
            Int32 stringThirdListVariableLength5 = BitConverter.ToInt32(stream, index);
            index += sizeof(Int32);
            thirdListit4.stringThirdListVariable = Encoding.Default.GetString(stream, index, stringThirdListVariableLength5);
            index += stringThirdListVariableLength5;
            thirdListit4.longThirdListVariable = BitConverter.ToInt64(stream, index);
            index += sizeof(Int64);
            thirdListit4.intThirdListVariable = BitConverter.ToInt32(stream, index);
            index += sizeof(Int32);
            thirdListit4.boolThirdListVariable = BitConverter.ToBoolean(stream, index);
            index += sizeof(Boolean);
            secondListit3.thirdList.Add(thirdListit4);
          }
          Int32 endofSecondVariableLength4 = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          secondListit3.endofSecondVariable = Encoding.Default.GetString(stream, index, endofSecondVariableLength4);
          index += endofSecondVariableLength4;
          firstListit2.secondList.Add(secondListit3);
        }
        Int32 specialListLength3 = BitConverter.ToInt32(stream, index);
        index += sizeof(Int32);
        for(int specialListi3=0;specialListi3 < specialListLength3;specialListi3++)
        {
          TEST_FIRST_LIST.TEST_SPECIAL_LIST specialListit3 = new TEST_FIRST_LIST.TEST_SPECIAL_LIST();
          Int32 stringSpecialListVariableLength4 = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          specialListit3.stringSpecialListVariable = Encoding.Default.GetString(stream, index, stringSpecialListVariableLength4);
          index += stringSpecialListVariableLength4;
          specialListit3.longSpecialListVariable = BitConverter.ToInt64(stream, index);
          index += sizeof(Int64);
          specialListit3.intSpecialListVariable = BitConverter.ToInt32(stream, index);
          index += sizeof(Int32);
          specialListit3.boolSpecialListVariable = BitConverter.ToBoolean(stream, index);
          index += sizeof(Boolean);
          firstListit2.specialList.Add(specialListit3);
        }
        firstList.Add(firstListit2);
      }
    }
  }

}
