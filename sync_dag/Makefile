CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = sync_dag

SOURCES = main.cpp ingestion.cpp task_nodes.cpp deltas.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) priced_options_output.csv

.PHONY: clean