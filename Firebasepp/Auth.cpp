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
			std::map<std::string, web::json::value> m;
			FirebaseString dataRetreived(res.extract_string().get());

			auto data = json::value::parse(dataRetreived).as_object();

			for (auto it = data.begin(); it != data.end(); it++) {
				m[wstrToStr(it->first)] = it->second;
			}

			return m;
		}).then([=](std::map<std::string, web::json::value> m) {
			response(m);
		});

		try {
			req.wait();
		}
		catch (const boost::bad_any_cast& b) {
			std::cout << b.what() << std::endl;
			std::cout << "bad any cast." << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			return AuthResponse();
		}

		m_isSignedIn = true;

		return m_res;
	}

	void Auth::response(std::map<std::string, web::json::value> &m) {
		if (!m.empty()) {
			m_res.displayName = m["displayName"].as_string();
			m_res.email = m["email"].as_string();
			m_res.expiresIn = m["expiresIn"].as_string();
			m_res.idToken = m["idToken"].as_string();
			m_res.kind = m["kind"].as_string();
			m_res.localId = m["localId"].as_string();
			m_res.refreshToken = m["refreshToken"].as_string();
			m_res.registered = m["registered"].as_bool();
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


	void Auth::refreshToken() {

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