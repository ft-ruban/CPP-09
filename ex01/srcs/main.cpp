#include <iostream>

/*
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Erro*/

int main(){//TODO take argument that would be an inverted Polish Math expression
    std::cout<<"Hello World :>"<<std::endl;
    //TODO need to check if argument is present

    //TOASK imo I do not need to parse what the user send me, but I wanna be sure firsthand

    //TODO process part here (would use the class probably)
        // Would require to make an error handler thing that show on the standard error
        // need to handle operations with the following tokens: "+-/*".
        // Find a container that is about stacks I guess
    return(0);
}


/*
personal note: require the first two char to be a number, then we keep in mind the result then take a new number do the sign bla bla bla, should not be that tough.

1 = num
2 = num
3 = symbol
4 = num
5 = symbol
6 = num
7 = symbol
[...]
*/