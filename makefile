# Kompiliatoriaus nustatymas
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Programos pavadinimas
TARGET = programa

# Objekto failų sąrašas
OBJS = main.o studentas.o funkcijos.o

# Pagrindinė taisyklė programos sukompiliavimui
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Atskirų failų kompiliavimo taisyklės
main.o: main.cpp studentas.h funkcijos.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Studentas.o: studentas.cpp studentas.h
	$(CXX) $(CXXFLAGS) -c Studentas.cpp

PagalbinesFunkcijos.o: funkcijos.cpp funkcijos.h studentas.h
	$(CXX) $(CXXFLAGS) -c funkcijos.cpp

# Valymo taisyklė
clean:
	rm -f $(TARGET) $(OBJS)
