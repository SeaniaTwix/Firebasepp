#pragma once

#include "types.h"

#include <future>

#include <array>

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

namespace Firebasepp {

	class Database {

	public:
		Database(FirebaseUrl root, FirebaseString pToken);
		~Database();

		// readData
		FirebaseMap get(FirebaseUrl uri, web::http::status_code *status);
		// writeData

		FirebaseMap set(FirebaseUrl uri, FirebaseMap pData, web::http::status_code *status);

		FirebaseMap update(FirebaseUrl uri, FirebaseMap pData, web::http::status_code *status);
		// removeData
		pplx::task<web::http::http_response> remove(FirebaseUrl uri);

		void setToken(FirebaseString tok) { m_token = tok; };

	private:
		web::http::client::http_client m_mainClient;

		FirebaseAuthToken m_token;
		FirebaseUrl m_root;
	};

}