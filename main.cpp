#include "MyServer.h"
#include "controllers/Admin.h"
#include "controllers/FilmController.h"
#include "controllers/Recommendation.h"
#include "controllers/UserController.h"
#include "handlers/CommentHandlers.h"
#include "handlers/FilmHandlers.h"
#include "handlers/UserHandlers.h"
#include "server/server.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));
    try {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);

        UserController user_controller;
        FilmController film_controller;
        Recommendation recommendation;
        Admin admin;

        server.get("/", new ShowFilms(&film_controller, &user_controller, &recommendation));
        server.get("/signup", new ShowSignup("static/signup.html", &user_controller));
        server.post("/signup", new SignupHandler(&user_controller));
        server.get("/login", new ShowLogin("static/login.html", &user_controller));
        server.post("/login", new LoginHandler(&user_controller));
        server.get("/logout", new LogoutHandler(&user_controller));
        server.get("/films/add", new ShowCreateFilm("static/add_film.html", &user_controller));
        server.get("/film", new ShowFilmDetails(&film_controller, &user_controller, &recommendation));
        server.post("/films", new CreateFilmHandler(&film_controller, &user_controller, &recommendation));
        server.get("/delete_film", new DeleteFilmHandler(&film_controller, &user_controller, &recommendation));
        server.get("/profile", new ShowPurchasedFilms(&film_controller, &user_controller));
        server.post("/money", new MoneyHandler(&film_controller, &user_controller, &admin));
        server.post("/buy", new BuyFilmHandler(&film_controller, &user_controller, &recommendation));
        server.post("/rate", new RateFilmHandler(&film_controller, &user_controller));

        server.get("/bootstrap.css", new ShowFile("static/css/bootstrap.css", "text/css"));
        server.get("/bootstrap.css.map", new ShowFile("static/css/bootstrap.css.map", "text/css"));
        server.get("/style.css", new ShowFile("static/css/style.css", "text/css"));

        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }

    return 0;
}
