CC = g++
COMPILE_FLAGS = -std=c++11
EXECUTABLE_FILE = a.out
BUILD_DIR = build
MODELS_DIR = models
ROUTES_DIR = routes
REPOSITORIES_DIR = repositories
CONTROLLERS_DIR = controllers
HANDLERS_DIR = handlers


OBJECTS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/route.o \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/response.o \
	$(BUILD_DIR)/request.o \
	$(BUILD_DIR)/utilities.o \
	$(BUILD_DIR)/template_parser.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/UserController.o \
	$(BUILD_DIR)/UserHandlers.o \
	$(BUILD_DIR)/Film.o \
	$(BUILD_DIR)/FilmController.o \
	$(BUILD_DIR)/FilmHandlers.o \
	$(BUILD_DIR)/CommentHandlers.o \
	$(BUILD_DIR)/Comment.o \
	$(BUILD_DIR)/Notification.o \
	$(BUILD_DIR)/md5.o \
	$(BUILD_DIR)/Reply.o \
	$(BUILD_DIR)/Recommendation.o \
	$(BUILD_DIR)/Graph.o \
	$(BUILD_DIR)/Admin.o

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(COMPILE_FLAGS) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp
	$(CC) $(COMPILE_FLAGS) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp
	$(CC) $(COMPILE_FLAGS) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp
	$(CC) $(COMPILE_FLAGS) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp
	$(CC) $(COMPILE_FLAGS) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(COMPILE_FLAGS) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp
	$(CC) $(COMPILE_FLAGS) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/User.o: $(MODELS_DIR)/User.cpp $(MODELS_DIR)/User.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserController.o: $(CONTROLLERS_DIR)/UserController.cpp $(CONTROLLERS_DIR)/UserController.h $(MODELS_DIR)/User.h
	$(CC) $(COMPILE_FLAGS) -c $(CONTROLLERS_DIR)/UserController.cpp -o $(BUILD_DIR)/UserController.o

$(BUILD_DIR)/UserHandlers.o: $(HANDLERS_DIR)/UserHandlers.cpp $(HANDLERS_DIR)/UserHandlers.h $(CONTROLLERS_DIR)/UserController.h
	$(CC) $(COMPILE_FLAGS) -c $(HANDLERS_DIR)/UserHandlers.cpp -o $(BUILD_DIR)/UserHandlers.o

$(BUILD_DIR)/Film.o: $(MODELS_DIR)/Film.cpp $(MODELS_DIR)/Film.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/Film.cpp -o $(BUILD_DIR)/Film.o

$(BUILD_DIR)/FilmController.o: $(CONTROLLERS_DIR)/FilmController.cpp $(CONTROLLERS_DIR)/FilmController.h $(MODELS_DIR)/Film.h
	$(CC) $(COMPILE_FLAGS) -c $(CONTROLLERS_DIR)/FilmController.cpp -o $(BUILD_DIR)/FilmController.o

$(BUILD_DIR)/Admin.o: $(CONTROLLERS_DIR)/Admin.cpp $(CONTROLLERS_DIR)/Admin.h
	$(CC) $(COMPILE_FLAGS) -c $(CONTROLLERS_DIR)/Admin.cpp -o $(BUILD_DIR)/Admin.o

$(BUILD_DIR)/Recommendation.o: $(CONTROLLERS_DIR)/Recommendation.cpp $(CONTROLLERS_DIR)/Recommendation.h $(MODELS_DIR)/Graph.h
	$(CC) $(COMPILE_FLAGS) -c $(CONTROLLERS_DIR)/Recommendation.cpp -o $(BUILD_DIR)/Recommendation.o

$(BUILD_DIR)/FilmHandlers.o: $(HANDLERS_DIR)/FilmHandlers.cpp $(HANDLERS_DIR)/FilmHandlers.h $(CONTROLLERS_DIR)/FilmController.h
	$(CC) $(COMPILE_FLAGS) -c $(HANDLERS_DIR)/FilmHandlers.cpp -o $(BUILD_DIR)/FilmHandlers.o

$(BUILD_DIR)/CommentHandlers.o: $(HANDLERS_DIR)/CommentHandlers.cpp $(HANDLERS_DIR)/CommentHandlers.h $(CONTROLLERS_DIR)/FilmController.h
	$(CC) $(COMPILE_FLAGS) -c $(HANDLERS_DIR)/CommentHandlers.cpp -o $(BUILD_DIR)/CommentHandlers.o

$(BUILD_DIR)/Comment.o: $(MODELS_DIR)/Comment.cpp $(MODELS_DIR)/Comment.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Reply.o: $(MODELS_DIR)/Reply.cpp $(MODELS_DIR)/Reply.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/Reply.cpp -o $(BUILD_DIR)/Reply.o

$(BUILD_DIR)/Notification.o: $(MODELS_DIR)/Notification.cpp $(MODELS_DIR)/Notification.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/Notification.cpp -o $(BUILD_DIR)/Notification.o

$(BUILD_DIR)/Graph.o: $(MODELS_DIR)/Graph.cpp $(MODELS_DIR)/Graph.h
	$(CC) $(COMPILE_FLAGS) -c $(MODELS_DIR)/Graph.cpp -o $(BUILD_DIR)/Graph.o

$(BUILD_DIR)/md5.o: utils/md5.cpp utils/md5.h
	$(CC) $(COMPILE_FLAGS) -c utils/md5.cpp -o $(BUILD_DIR)/md5.o

.PHONY: clean

clean:
	rm *.o