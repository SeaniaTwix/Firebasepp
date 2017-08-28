#pragma once
#include "types.h"
#include "Database.h"
#include "Auth.h"

#include <functional>

// Error Types
#define EMAIL_NOT_FOUND "EMAIL_NOT_FOUND"
#define INVALID_PASSWORD "INVALID_PASSWORD"
#define NO_FIREBASE_ERROR "__NO_ERROR__";

namespace Firebasepp {
	class firebase {

	public:
		firebase();
		~firebase();

		void initializeApp(FirebaseConfig pConfig);

	public: // Auth

		AuthResponse signIn(Authentication pAuth);
		AuthResponse signUp();
		AuthResponse createAccount(Authentication pAuth);

		AuthResponse updateAuthToken();

	public: // Db

		void initializeDatabase();

		FirebaseMap get(FirebaseUrl pPath);
		FirebaseMap set(FirebaseUrl pPath, FirebaseMap pObject);
		FirebaseMap update(FirebaseUrl pPath, FirebaseMap pObject);

	protected:
		FirebaseConfig m_config;

		Auth *auth;
		Database *db;

		// **** Current User State ****
		AuthResponse m_res;
		bool isSignedIn = false;

	};

}