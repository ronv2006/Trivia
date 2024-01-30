using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using TriviaClient.img;

namespace TriviaClient
{
    internal class Deserializer
    {
        public static StatusResponse deserializeResponse(String str)
        {
            
            if (str.Length > 4)
            {
                str = str.Substring(5);
            }
            else
            {
                return new StatusResponse(0);
            }
            StatusResponse response = JsonSerializer.Deserialize<StatusResponse>(str);
            return response;

        }

        public static StatisticsResponse deserializeStatisticResponse(String str)
        {
            
            if (str.Length > 4)
            {
                str = str.Substring(5);
            }
            else
            {
                return new StatisticsResponse();
            }
            StatisticsResponse response = JsonSerializer.Deserialize<StatisticsResponse>(str);
            return response;
        }

        public static HighScoreResponse deserializeHighScoreResponse(String str)
        {
            if (str.Length > 4)
            {
                str = str.Substring(5);
            }
            else
            {
                return new HighScoreResponse();
            }
            HighScoreResponse response = JsonSerializer.Deserialize<HighScoreResponse>(str);
            return response;
        }

        public static GetRoomsResponse deserializeGetRoomsResponse(String str)
        {
            if(str.Length > 4)
            {
                str = str.Substring(5);
            }
            GetRoomsResponse response = JsonSerializer.Deserialize<GetRoomsResponse>(str);
            return response;
        }

        public static GetRoomStateResponse deserializeGetRoomStateResponse(String str)
        {
            if (str.Length > 4)
            {
                str = str.Substring(5);
            }
            GetRoomStateResponse response = JsonSerializer.Deserialize<GetRoomStateResponse>(str);
            return response;
        }

        

        
    }
}
