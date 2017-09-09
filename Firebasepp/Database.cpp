#include "Database.h"

#define ACCESS_TOKEN "auth"
#define DOT_JSON ".json"
#define EMPTY ""

#include <iostream>

namespace Firebasepp {

	Database::Database(FirebaseUrl pRoot, FirebaseString pToken = U("")) : m_mainClient(pRoot) {
		m_root = pRoot;
		m_token = pToken;
	}

	Database::~Database() { }

	FirebaseMap Database::get(FirebaseUrl pUri, web::http::status_code *status) {
		using namespace web;
		using namespace web::http;

		auto encodedUri = web::uri::encode_data_string(pUri);
		uri_builder uri(encodedUri + U(DOT_JSON));
		uri.append_query(U(ACCESS_TOKEN), m_token);

		auto request = m_mainClient.request(methods::GET, uri.to_string()).then([=](http_response res) {
			FirebaseMap m = FirebaseMap();
			FirebaseString dataRetreived(res.extract_string().get());
			
			*status = res.status_code();

			if (dataRetreived != U("null")) {
				auto data = json::value::parse(dataRetreived).as_object();

				for (auto it = data.begin(); it != data.end(); it++) {
					m[it->first] = it->second;
				}
			}

			return m;
		});

		try {
			request.wait();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		return request.get();
	}

	FirebaseMap Database::update(FirebaseUrl pUri, FirebaseMap pData, web::http::status_code *status) {
		using namespace web;
		using namespace web::http;

		auto encodedUri = web::uri::encode_data_string(pUri);
		uri_builder uri(encodedUri + U(DOT_JSON));
		uri.append_query(U(ACCESS_TOKEN), m_token);

		json::value data = json::value::object();

		for (auto it = pData.begin(); it != pData.end(); it++) {
			data[it->first] = it->second;
		}

		//std::cout << "Firebase update sending..." << std::endl;

		auto request = m_mainClient.request(methods::PATCH, uri.to_string(), data).then([=](http_response res) {
			FirebaseMap m;
			FirebaseString dataRetreived(res.extract_string().get());

			*status = res.status_code();

			auto data = json::value::parse(dataRetreived).as_object();

			for (auto it = data.begin(); it != data.end(); it++) {
				m[it->first] = it->second;
			}

			return m;
		});

		try {
			request.wait();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		return request.get();
	}

	pplx::task<web::http::http_response> Database::remove(FirebaseUrl pUri) {
		using namespace web;
		using namespace web::http;

		auto encodedUri = web::uri::encode_data_string(pUri);

		uri_builder uri(encodedUri + U(DOT_JSON));
		uri.append_query(U(ACCESS_TOKEN), m_token);

		auto request = m_mainClient.request(methods::DEL, uri.to_string()).then([=](http_response res) {
			return res;
		});

		try {
			request.wait();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		return request;
	}

	FirebaseMap Database::set(FirebaseUrl pUri, FirebaseMap pData, web::http::status_code *status) {
		using namespace web;
		using namespace web::http;

		auto encodedUri = web::uri::encode_data_string(pUri);

		uri_builder uri(encodedUri + U(DOT_JSON));
		uri.append_query(U(ACCESS_TOKEN), m_token);

		json::value data = json::value::object();

		for (auto it = pData.begin(); it != pData.end(); it++) {
			data[it->first] = it->second;
		}

		//std::cout << "Firebase set sending..." << std::endl;

		auto request = m_mainClient.request(methods::PUT, uri.to_string(), data).then([=](http_response res) {
			FirebaseMap m;
			FirebaseString dataRetreived(res.extract_string().get());

			*status = res.status_code();

			auto data = json::value::parse(dataRetreived).as_object();

			for (auto it = data.begin(); it != data.end(); it++) {
				m[it->first] = it->second;
			}

			return m;
		});

		try {
			request.wait();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		return request.get();
	}


}