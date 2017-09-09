#include "firebase.h"

namespace Firebasepp {

	firebase::firebase() { }
	
	firebase::~firebase() { }

	void firebase::initializeApp(FirebaseConfig _config) {
		m_config = _config;

		auth = new Auth(m_config);
	}

	AuthResponse firebase::signIn(Authentication _auth) {
		m_res = auth->loginWithEmailAndPassword(_auth);
		return m_res;
	}

	void firebase::initializeDatabase() {
		db = new Database(m_config.databaseURL, m_res.idToken);
	}

	FirebaseMap firebase::get(FirebaseUrl pPath, web::http::status_code *status) {
		return db->get(pPath, status);
	}

	FirebaseMap firebase::update(FirebaseUrl pPath, FirebaseMap pObject, web::http::status_code *status) {
		return db->update(pPath, pObject, status);
	}

	FirebaseMap firebase::set(FirebaseUrl pPath, FirebaseMap pObject, web::http::status_code *status) {
		return db->set(pPath, pObject, status);
	}
}