#include <iostream>
#include "game/Game.h"
#include <jansson.h>
#include "seamule-sdk-c/src/seamule-sdk.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "piece/king/King.h"
#include "piece/queen/Queen.h"
#include "piece/bishop/Bishop.h"
#include "piece/rook/Rook.h"
#include "piece/knight/Knight.h"
#include "piece/pawn/Pawn.h"
#include <fstream>


using namespace std;

int main(int argc, char *argv[]) {
    // -i -o

    char *input_value;
    char *output_value;

    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "i:o:")) != -1)
        switch (c) {
            case 'i':
                input_value = optarg;
                break;
            case 'o':
                output_value = optarg;
                break;
            default:
                abort();
        }

    ifstream myReadFile;
    myReadFile.open(input_value);
    char output[1024 * 1024];
    myReadFile >> output;

    json_error_t error;
    json_t *json_text = json_loads(output, 0, &error);


    json_t *json_turn = json_object_get(json_text, "turn");

    Board *board;

    char *turn = (char *) malloc(20 * sizeof(char));
    strcpy(turn, json_string_value(json_turn));
    Color turn_color;

    if (!strcmp(turn, "blacks"))
        turn_color = BLACK;
    else
        turn_color = WHITE;

    board = new Board(turn_color, 2);

    free(turn);

    json_t *pieces_array = json_object_get(json_text, "pieces");

    int i;
    for (i = 0; i < json_array_size(pieces_array); i++) {

        json_t *data;
        data = json_array_get(pieces_array, i);

        json_t *x, *y, *type, *color;

        //REVISO EL TIPO DE FICHA
        type = json_object_get(data, "kind");
        char *type_string = (char *) malloc(20 * sizeof(char));
        strcpy(type_string, json_string_value(type));
        int type_int;

        if (!strcmp("king", type_string))
            type_int = 0;
        if (!strcmp("queen", type_string))
            type_int = 1;
        if (!strcmp("bishop", type_string))
            type_int = 2;
        if (!strcmp("rook", type_string))
            type_int = 3;
        if (!strcmp("knight", type_string))
            type_int = 4;
        if (!strcmp("pawn", type_string))
            type_int = 5;

        free(type_string);

        //POSICION
        x = json_object_get(data, "x");
        y = json_object_get(data, "y");

        int x_int = json_integer_value(x);
        int y_int = json_integer_value(y);

        //COLOR
        color = json_object_get(data, "color");
        char *color_string = (char *) malloc(20 * sizeof(char));
        strcpy(color_string, json_string_value(color));

        Color color_piece;
        if (!strcmp(color_string, "black"))
            color_piece = BLACK;
        else
            color_piece = WHITE;

        free(color_string);

        Piece *p;
        if (type_int == 0)
            p = new King(x_int, y_int, color_piece);
        if (type_int == 1)
            p = new Queen(x_int, y_int, color_piece);
        if (type_int == 2)
            p = new Bishop(x_int, y_int, color_piece);
        if (type_int == 3)
            p = new Rook(x_int, y_int, color_piece);
        if (type_int == 4)
            p = new Knight(x_int, y_int, color_piece);
        if (type_int == 5)
            p = new Pawn(x_int, y_int, color_piece);

        board->pushPiece(p);

    }

#pragma omp parallel
    {
#pragma omp single
        {
            Game game(board);
            game.init();
            game.execute();
            game.clean();
        }
    }

    Stats *s = s->getInstance();

    FILE *output_file;
    output_file = fopen(output_value, "w");

    json_dumpf(s->boards_json, output_file, 0);

    fclose(output_file);

    return 0;
}
