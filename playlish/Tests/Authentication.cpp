#include <SQLAPI.h>
#include "./catch_amalgamated.hpp"
#include "./../Validation/Fields/Auth/UsernameField.h"
#include "./../Validation/Fields/Auth/EmailField.h"
#include "./../Validation/Fields/Auth/PasswordField.h"
#include "./../Validation/Fields/Auth/PasswordConfirmationField.h"
#include "./../Models/UserModel.h"
#include "./../Common/DB.h"


SCENARIO("Users can create an account", "[create-account]") {
    SECTION("Username is validated correctly") {
        SECTION("Username is of correct length") {
            UsernameField username;
            username.name = "Username";

            username.value = "georgi";
            REQUIRE(username.validate());

            username.value = "georgi1";
            REQUIRE(username.validate());

            username.value = "123";
            REQUIRE(!username.validate());

            username.value = "1234512345123451234512345";
            REQUIRE(username.validate());

            username.value = "123451234512345123451234";
            REQUIRE(username.validate());

            username.value = "12345123451234512345123456";
            REQUIRE(!username.validate());

            username.value = "123451234512345123451234561234512345123451234512345612345123451234512345123456";
            REQUIRE(!username.validate());
        }

        SECTION("Username is unique.") {
            DB::conn().setAutoCommit(SA_AutoCommitOff);
            UserModel user;
            user.email = "test123123123@gmail.com";
            user.password = "12345678";
            user.username = "georgi123123";
            user.insert();
            UsernameField username;
            username.name = "Username";

            username.value = "georgi123123";
            REQUIRE(!username.validate());
            DB::conn().Rollback();
            DB::conn().setAutoCommit(SA_AutoCommitOn);
        }
    }
    SECTION("User email is validated correctly."){
        EmailField email;
        email.name = "email";

        email.value = "georgi@gmail.com";
        REQUIRE(email.validate());

        email.value = "georgi123456@gmail.com";
        REQUIRE(email.validate());

        email.value = "12@gmail.com";
        REQUIRE(email.validate());

        email.value = "georgi@l.com";
        REQUIRE(email.validate());

        email.value = "georgi@1.com";
        REQUIRE(email.validate());

        email.value = "georgi@";
        REQUIRE(!email.validate());

        email.value = "georgi";
        REQUIRE(!email.validate());

        email.value = "gmail.com";
        REQUIRE(!email.validate());
    }
    SECTION("Password is validated correctly.") {
        PasswordField password;
        password.name = "password";

        password.value = "0";
        REQUIRE(!password.validate());
       
        password.value = "123";
        REQUIRE(!password.validate());

        password.value = "123456";
        REQUIRE(password.validate());

        password.value = "123456789";
        REQUIRE(password.validate());

        password.value = "a123";
        REQUIRE(!password.validate());

        password.value = "ab123";
        REQUIRE(!password.validate());

        password.value = "abvgdej";
        REQUIRE(!password.validate());

        password.value = "@fjalsdj";
        REQUIRE(!password.validate());
    }
}