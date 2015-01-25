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
      foreach(byte worldi in BitConverter.GetBytes(world).Reverse() )
      {
        stream[index++] = worldi;
      }
      foreach(byte channeli in BitConverter.GetBytes(channel).Reverse() )
      {
        stream[index++] = channeli;
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
    public Int32 GetStreamLength()
    {
      Int32 size = 0;
      size += sizeof(Boolean);
      size += sizeof(Int64);
      return size;
    }
    public void Serialize(byte[] stream)
    {
      Int32 index = 0;
      foreach(byte validi in BitConverter.GetBytes(valid).Reverse() )
      {
        stream[index++] = validi;
      }
      foreach(byte enterChannelTimei in BitConverter.GetBytes(enterChannelTime).Reverse() )
      {
        stream[index++] = enterChannelTimei;
      }
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
    public Int32 GetStreamLength()
    {
      Int32 size = 0;
      size += sizeof(Int32);
      for(int friendListi=0;friendListi < friendList.Count;friendListi++)
      {
        size += sizeof(Int32);
        size += friendList[friendListi].userName.Length * sizeof(char);
        size += sizeof(Int64);
        size += sizeof(Int32);
        size += sizeof(Int32);
      }
      return size;
    }
    public void Serialize(byte[] stream)
    {
      Int32 index = 0;
      foreach(byte friendListi in BitConverter.GetBytes(friendList.Count).Reverse() )
      {
        stream[index++] = friendListi;
      }
      for(int friendListi=0;friendListi < friendList.Count;friendListi++)
      {
        foreach(byte userNamei in BitConverter.GetBytes(friendList[friendListi].userName.Length).Reverse() )
        {
          stream[index++] = userNamei;
        }
        foreach(char userNamei in friendList[friendListi].userName )
        {
          foreach(byte userNamej in BitConverter.GetBytes(userNamei) )
          {
            stream[index++] = userNamej;
          }
        }
        foreach(byte userServerIdi in BitConverter.GetBytes(friendList[friendListi].userServerId).Reverse() )
        {
          stream[index++] = userServerIdi;
        }
        foreach(byte userGradei in BitConverter.GetBytes(friendList[friendListi].userGrade).Reverse() )
        {
          stream[index++] = userGradei;
        }
        foreach(byte userSubGradei in BitConverter.GetBytes(friendList[friendListi].userSubGrade).Reverse() )
        {
          stream[index++] = userSubGradei;
        }
      }
    }
  }

}
