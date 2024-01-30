using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;


namespace TriviaClient
{
    public class Serializer
    {
        public static String addSizeToString(String str, int sizeOfMessage)
        {
            str = str + Convert.ToChar(((sizeOfMessage >> 24) & 0xFF)).ToString();
            str = str + Convert.ToChar((sizeOfMessage >> 16) & 0xFF).ToString();
            str = str + Convert.ToChar((sizeOfMessage >> 8) & 0xFF).ToString();
            str = str + Convert.ToChar((sizeOfMessage & 0xFF)).ToString();
            return str;
        }

        public static String serializeRequest(LoginRequest login)
        {
            int code = (int)RequestStatus.LOGIN_REQUEST;
            String str = Convert.ToChar(code).ToString();
            
            String json = JsonSerializer.Serialize(login);
            int sizeOfMessage = json.Length;
            str = addSizeToString(str, sizeOfMessage);
            str = str + json;
            
            

            return str;
        }

        public static String serializeRequest(SignupRequest request)
        {
            int code = (int)RequestStatus.SIGNUP_REQUEST;
            String str = Convert.ToChar(code).ToString();
            String json = JsonSerializer.Serialize(request);
            int sizeOfMessage = json.Length;
            str = addSizeToString(str, sizeOfMessage);
            str = str + json;

            return str;
        }

        public static String serializeCreateRoomRequest(CreateRoomRequest request)
        {
            int code = (int)RequestStatus.CREATE_ROOM_REQUEST;
            String str = Convert.ToChar(code).ToString();
            String json = JsonSerializer.Serialize(request);
            int sizeOfMessage = json.Length;
            str = addSizeToString(str, sizeOfMessage);
            str = str + json;

            return str;
        }

        public static String serializeJoinRoomRequest(JoinRoomRequest request)
        {
            int code = (int)RequestStatus.JOIN_ROOM_REQUEST;
            String str = Convert.ToChar(code).ToString();
            String json = JsonSerializer.Serialize(request);
            int sizeOfMessage = json.Length;
            str = addSizeToString(str, sizeOfMessage);
            str = str + json;

            return str;
        }
    }



}

