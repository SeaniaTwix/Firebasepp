# Firebasepp

A Firebase Casablanca Wrapper

# Installation

### Requirements

- Vcpkg (if you want it to use on windows os)
- Cpprestsdk (tested on 2.9)
- Set your enviroment variable for vcpkg

# How to use

```cpp
#include <firebase.h>

{
  // declare your firebase
  Firebasepp::firebase fb = new Firebasepp::firebase;

  FirebaseConfig config = {};
  {
    config.apiKey = U("YOUR_APIKEY");
    config.authDomain = U("YOUR_DOMAIN");
    config.databaseURL = U("YOUR_DOMAIN");
    config.projectId = U("YOUR_ID");
    config.storageBucket = U("YOUR_BUCKET");
    config.messagingSenderId = U("YOUR_SENDERID");
  }

  fb.initializeApp(config);

  Authentication auth = {};
  {
    auth.email = email_data;
    auth.password = password_data;
  }

  // Get data as type of AuthResponse.
  // It set a token for database automatically.
  auto res = fb.signIn(auth);

  if (res.idToken.length() > 0) {
    // Login Successed
    // Get data as type of FirebaseMap
    auto res = fb.get(U("YOUR_PATH"));

    // Now you can access to your data
    auto data = res[U("KEY")];
  } else {
    // Login Failed
  }
}
```

# Why need U macro on string?
https://github.com/Microsoft/cpprestsdk/wiki/FAQ#what-is-utilitystring_t-and-the-u-macro
