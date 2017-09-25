#include "Auth.h"
#include <iostream>
#include <string>

namespace Firebasepp {

	Auth::Auth(FirebaseConfig pConfig) : m_mainClient(U("https://www.googleapis.com")) {
		m_apiKey = pConfig.apiKey;
	}

	Auth::~Auth() { }

	std::string wstrToStr(FirebaseString wstr) {
		return std::string(wstr.begin(), wstr.end());
	}

	AuthResponse Auth::loginWithEmailAndPassword(Authentication pAuth) {
		using namespace web;
		using namespace web::http;

		uri_builder uri(U("/identitytoolkit/v3/relyingparty/verifyPassword"));
		uri.append_query(U("key"), m_apiKey);

		json::value data = json::value::object();
		data[U("email")] = json::value::string(pAuth.email);
		data[U("password")] = json::value::string(pAuth.password);
		data[U("returnSecureToken")] = json::value::boolean(true);

		auto req = m_mainClient.request(methods::POST, uri.to_string(), data).then([=](http_response res) {
			FirebaseMap m;
			FirebaseString dataRetreived(res.extract_string().get());

			auto data = json::value::parse(dataRetreived).as_object();

			for (auto it = data.begin(); it != data.end(); it++) {
				m[it->first] = it->second;
			}

			return m;
		}).then([=](FirebaseMap m) {
			response(m);
		});

		try {
			req.wait();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			return AuthResponse();
		}

		m_isSignedIn = true;

		return m_res;
	}

	void Auth::response(FirebaseMap &m) {
		if (!m.empty()) {
			m_res.displayName = m[U("displayName")].as_string();
			m_res.email = m[U("email")].as_string();
			m_res.expiresIn = m[U("expiresIn")].as_string();
			m_res.idToken = m[U("idToken")].as_string();
			m_res.kind = m[U("kind")].as_string();
			m_res.localId = m[U("localId")].as_string();
			m_res.refreshToken = m[U("refreshToken")].as_string();
			m_res.registered = m[U("registered")].as_bool();
		}
	}

	void Auth::logout() {
	}

	AuthResponse Auth::getSignedUserState() {
		return m_res;
	}

	std::string Auth::getSignedUserUid() {
		return wstrToStr(m_res.localId);
	}

	bool Auth::isSignedIn() {
		return m_isSignedIn;
	}


	FirebaseMap Auth::refreshToken() {
		using namespace web;
		using namespace web::http;
		
		web::http::client::http_client client2{ U("https://securetoken.googleapis.com") };

		uri_builder uri(U("/v1/token"));
		uri.append_query(U("key"), m_apiKey);

		json::value payload = json::value::object();
		payload[U("grant_type")] = json::value(U("refresh_token"));
		payload[U("refresh_token")] = json::value::string(m_res.refreshToken);

		auto req = client2.request(methods::POST, uri.to_string(), payload).then([=](http_response res) {
			utility::string_t response_body = res.extract_string().get();
			auto data = json::value::parse(response_body).as_object();

			FirebaseMap m;

			for (auto it : data) {
				m[it.first] = it.second;
			}

			return m;
		});

		try {
			req.wait();
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		return req.get();
	}

	void Auth::setTokenRefreshed(FirebaseMap &m) {
		if (!m.empty()) {
			m_res.expiresIn = m[U("expiresIn")].as_string();
			m_res.refreshToken = m[U("refreshToken")].as_string();
			m_res.idToken = m[U("id_token")].as_string();
			m_res.localId = m[U("user_id")].as_string();
			m_res.registered = m[U("registered")].as_bool();
		}
	}

	void Auth::loginSuccessed() {
	}

	void Auth::loginFailed() {
	}

	std::string Auth::signInError() {
		//const std::string errorMsg = errorObj->value("message").toString().toStdString();

		return nullptr;
	}
}