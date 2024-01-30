using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;




namespace TriviaClient
{
     
    public enum RequestStatus
    {
        LOGIN_REQUEST = 83,
        SIGNUP_REQUEST = 84,
        ERRORMSG_REQUEST = 85,
        GET_PLAYERS_REQUEST = 86,
        JOIN_ROOM_REQUEST = 87,
        CREATE_ROOM_REQUEST = 88,
        LOGOUT_REQUEST = 89,
        PERSONAL_STAT_REQUEST = 90,
        HIGHEST_SCORES_REQUEST = 91,
        CLOSE_ROOM_REQUEST = 92,
        LEAVE_ROOM_REQUEST = 93,
        GET_ROOM_STATE_REQUEST = 94,
        START_GAME_REQUEST = 95,
        GET_ROOMS_REQUEST = 96,
    }

    public enum ResponseStatus
    {
        LOGIN_RESPONSE = 70,
        SIGNUP_RESPONSE = 71,
        ERRORMSG_RESPONSE = 72,
        LOGOUT_RESPONSE = 69,
        GET_ROOMS_RESPONSE = 73,
        GET_PLAYERS_IN_ROOM_RESPONSE = 74,
        JOIN_ROOM_RESPONSE = 75,
        CREATE_ROOM_RESPONSE = 76,
        PERSONAL_STATS_RESPONSE = 77,
        HIGHEST_SCORE_RESPONSE = 78,
        CLOSE_ROOM_RESPONSE = 79,
        LEAVE_ROOM_RESPONSE = 80,
        GET_ROOM_STATE_RESPONSE = 81,
        START_GAME_RESPONSE = 82,

    };
}
