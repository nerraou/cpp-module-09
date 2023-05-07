NAME = btc

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

HEADERS = BitcoinExchange.hpp 
	  
SRC = main.cpp\
	  BitcoinExchange.cpp
	
OBJ = $(SRC:.cpp=.o)

INCLUDES_PATH = -I ./

all:  $(NAME)

%.o: %.cpp $(HEADERS)
	c++ $(INCLUDES_PATH) -o $@ -c $<

$(NAME): $(OBJ)
	c++ $(CPPFLAGS) -o $(NAME) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
