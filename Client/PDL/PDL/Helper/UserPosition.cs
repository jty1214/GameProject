using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL.Helper
{
    public static class UserPosition
    {
        static String m_UserPos = "";

        public static String GetUser()
        {
            return m_UserPos;
        }
        public static void SetUser(String UserPos)
        {
            m_UserPos = UserPos.ToLower();
        }
        public static bool CheckValid()
        {
            String[] AllowUser =
            {
                "client",
                "server"
            };

            foreach( String i in AllowUser)
            {
                if (m_UserPos == i)
                    return true;
            }

            return false;
        }
    }
}
