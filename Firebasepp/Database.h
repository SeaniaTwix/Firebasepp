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
		FirebaseMap get(FirebaseUrl uri);
		// writeData

		FirebaseMap set(FirebaseUrl uri, FirebaseMap pData);

		FirebaseMap update(FirebaseUrl uri, FirebaseMap pData);
		// removeData
		pplx::task<web::http::http_response> remove(FirebaseUrl uri);

	private:
		web::http::client::http_client m_mainClient;

		FirebaseAuthToken m_token;
		FirebaseUrl m_root;
	};

}