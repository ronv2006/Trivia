using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using TriviaClient.img;
using System.Threading;
namespace TriviaClient
{
    public class Communicator
    {
        public static TcpClient server;
        private static Mutex mutex;
        
        public Communicator()
        {
            server = new TcpClient("127.0.0.1", 8824);
            mutex = new Mutex();

        }

        public static StatusResponse Login(String username, String password)
        {
            lock (Communicator.mutex)
            {
                LoginRequest request = new LoginRequest(username, password);
                String requestToSend = Serializer.serializeRequest(request);
                byte[] message = Encoding.ASCII.GetBytes(requestToSend);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                StatusResponse response = Deserializer.deserializeResponse(recievedData);
                return response;
            }
        }

        public static StatusResponse Signup(String username, String password, String email)
        {
            lock (Communicator.mutex)
            {
                SignupRequest request = new SignupRequest(username, password, email);
                String requestToSend = Serializer.serializeRequest(request);
                byte[] message = Encoding.ASCII.GetBytes(requestToSend);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }
            
        }

        public static StatusResponse Logout()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.LOGOUT_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }
        }

        public static StatisticsResponse Statistics()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.PERSONAL_STAT_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeStatisticResponse(recievedData);
            }
            }

        public static HighScoreResponse HighScore()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.HIGHEST_SCORES_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeHighScoreResponse(recievedData);
            }

        }

        public static StatusResponse CreateRoom(CreateRoomRequest request)
        {
            lock (Communicator.mutex)
            {
                String requestToSend = Serializer.serializeCreateRoomRequest(request);
                byte[] message = Encoding.ASCII.GetBytes(requestToSend);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }
            

        }

        public static GetRoomsResponse GetRooms()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.GET_ROOMS_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeGetRoomsResponse(recievedData);
            }
        }

        public static GetRoomStateResponse GetRoomState()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.GET_ROOM_STATE_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeGetRoomStateResponse(recievedData);
            }
        }

        public static StatusResponse JoinRoom(JoinRoomRequest request)
        {
            lock (Communicator.mutex)
            {
                String requestToSend = Serializer.serializeJoinRoomRequest(request);
                byte[] message = Encoding.ASCII.GetBytes(requestToSend);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }
        }

        public static StatusResponse LeaveRoom()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.LEAVE_ROOM_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }

        }

        public static StatusResponse CloseRoom()
        {
            lock (Communicator.mutex)
            {
                int code = (int)RequestStatus.CLOSE_ROOM_REQUEST;
                String request = Convert.ToChar(code).ToString();
                byte[] message = Encoding.ASCII.GetBytes(request);
                Communicator.server.GetStream().Write(message, 0, message.Length);
                byte[] buffer = new byte[1024];
                int bytesRead = Communicator.server.GetStream().Read(buffer, 0, buffer.Length);
                String recievedData = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                return Deserializer.deserializeResponse(recievedData);
            }
        }
    }




  }

