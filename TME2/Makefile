FLAGS= -std=c++17 -g -O2 -Wall 
SOURCES= main_hashtable main_vide test main_vector_sans_occurences main_vector_avec_occurences

all: $(SOURCES)

$(SOURCES): $(SOURCES:.cpp)
	g++ $(FLAGS) -o ./bin/$@ ./src/$@.cpp

clean:
	rm -f ./bin/*

