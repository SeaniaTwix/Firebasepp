#pragma once

#include "types.h"
#include <string>

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

#include <functional>

#include <cpprest/json.h>

// Error Types
#define EMAIL_NOT_FOUND "EMAIL_NOT_FOUND"
#define INVALID_PASSWORD "INVALID_PASSWORD"
#define NO_FIREBASE_ERROR "__NO_ERROR__";
#define USER_DISABLED "USER_DISABLED"

namespace Firebasepp {

	class Auth {

	public:
		Auth(FirebaseConfig pConfig);
		~Auth();

		AuthResponse loginWithEmailAndPassword(Authentication pAuth);
		void logout();

		AuthResponse getSignedUserState();
		std::string getSignedUserUid();

		bool isSignedIn();

	protected:


	private:
		web::http::client::http_client m_mainClient;

		FirebaseString m_apiKey;

		Authentication m_auth;
		AuthResponse m_res;

		bool m_isSignedIn = false;

		void refreshToken();

		void loginSuccessed();
		void loginFailed();

		void response(std::map<std::string, web::json::value> &m);

		std::string signInError();
	};

}