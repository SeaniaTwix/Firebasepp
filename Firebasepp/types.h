#pragma once
#include <map>

#include <cpprest/json.h>

using FirebaseString = utility::string_t;
using FirebaseUrl = FirebaseString;
using FirebaseAuthToken = FirebaseString;

typedef struct {
	FirebaseString apiKey;
	FirebaseString authDomain;
	FirebaseString databaseURL;
	FirebaseString projectId;
	FirebaseString storageBucket;
	FirebaseString messagingSenderId;
} FirebaseConfig;

typedef struct {
	FirebaseString email = U(""); 
	FirebaseString password = U("");
} Authentication;

using FirebaseMap = std::map<FirebaseString, web::json::value>;

class AuthResponse {
public:
	FirebaseString kind;
	FirebaseString localId;
	FirebaseString email;
	FirebaseString displayName;
	FirebaseString idToken;
	bool registered;
	FirebaseString refreshToken;
	FirebaseString expiresIn;
};
