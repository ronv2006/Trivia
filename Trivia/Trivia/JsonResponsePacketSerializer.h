#pragma once

#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "GetHighScoreResponse.h"
#include "GetPersonalStatsResponse.h"
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "GetRoomStateResponse.h"
#include "LeaveRoomResponse.h"
#include <vector>

class JsonResponsePacketSerializer {
public:
	std::vector<unsigned char> static serializeResponse(const ErrorResponse& err);
	std::vector<unsigned char> static serializeResponse(const LoginResponse& log);
	std::vector<unsigned char> static serializeResponse(const SignupResponse& sign);
    std::vector<unsigned char> static serializeResponse(const LogoutResponse& response);
    std::vector<unsigned char> static serializeResponse(const GetRoomsReponse& response);
    std::vector<unsigned char> static serializeResponse(const GetPlayersInRoomResponse& response);
    std::vector<unsigned char> static serializeResponse(const JoinRoomResponse& response);
    std::vector<unsigned char> static serializeResponse(const CreateRoomResponse& response);
    std::vector<unsigned char> static serializeResponse(const GetHighScoreResponse& response);
    std::vector<unsigned char> static serializeResponse(const GetPersonalStatsResponse& response);
    std::vector<unsigned char> static serializeResponse(const CloseRoomResponse& response);
    std::vector<unsigned char> static serializeResponse(const StartGameResponse& response);
    std::vector<unsigned char> static serializeResponse(const GetRoomStateResponse& response);
    std::vector<unsigned char> static serializeResponse(const LeaveRoomResponse& response);
};