#pragma once
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"
#include <vector>
class JsonRequestPacketDeserializer {
public:
	LoginRequest static deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	SignupRequest static deserializeSignupRequest(const std::vector<unsigned char>& buffer);
    GetPlayersInRoomRequest static deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer);
    JoinRoomRequest static deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
    CreateRoomRequest static deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);

};