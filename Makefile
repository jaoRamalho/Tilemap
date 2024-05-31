# Diretório de destino para os arquivos .o
OBJ_DIR = obj

# Lista de todos os arquivos .cpp no diretório src
CPP_FILES := $(wildcard *.cpp)

# Adicione o diretório da biblioteca nlohmann/json
JSON_DIR := nlohmann
JSON_INCLUDE := -I$(JSON_DIR)

# Lista de arquivos .o gerados a partir dos arquivos .cpp
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))

# Compilação dos arquivos .cpp para arquivos .o
$(OBJ_DIR)/%.o:	%.cpp
	g++ -c -I. \
	-ISFML \
	-I$(JSON_DIR) \
	$< -o $@

# Regra padrão para construir o executável
all: clean compile link

compile: $(OBJ_FILES)

link:
	g++ $(OBJ_FILES) -o main -Llib -lsfml-graphics -lsfml-window -lsfml-system
# Limpar os arquivos .o e o executável
clean:
	del /F /Q $(OBJ_DIR)\\*.o