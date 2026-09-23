CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

TARGET = async_dag

SOURCES = main.cpp ingestion.cpp tasknodes.cpp deltas.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) priced_options_output.csv

.PHONY: clean