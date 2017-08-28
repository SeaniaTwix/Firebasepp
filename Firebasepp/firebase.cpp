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

	FirebaseMap firebase::get(FirebaseUrl pPath) {
		return db->get(pPath);
	}

	FirebaseMap firebase::update(FirebaseUrl pPath, FirebaseMap pObject) {
		return db->update(pPath, pObject);
	}

	FirebaseMap firebase::set(FirebaseUrl pPath, FirebaseMap pObject) {
		return db->set(pPath, pObject);
	}
}