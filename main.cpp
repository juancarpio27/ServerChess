#include <iostream>
#include "game/Game.h"
#include <jansson.h>
#include "seamule-sdk-c/src/seamule-sdk.h"


json_t *process(const json_t *payload);

using namespace std;

int main(int argc, char *argv[]) {
    return seamule_main(argc, argv, process);
}

json_t *process(const json_t *payload) {

    json_error_t error;

    Board *board = new Board(WHITE, 4);

    if (!payload) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        goto error;
    }

    if (!json_is_array(payload)) {
        fprintf(stderr, "error: payload is not an array\n");
        goto error;
    }

    int i;
    for (i = 0; i < json_array_size(payload); i++) {
        json_t *data, *type, *position_x, *position_y, *color;

        data = json_object_get(payload, i);
        if (!json_is_object(data)) {
            printf("%s", json_string_value(data));
            fprintf(stderr, "error: payload data %d is not an object\n", (int) (i + 1));
            goto error;
        }

        //Check al the values of the pieces
        type = json_object_get(data, "type");
        if (!json_is_integer(type)) {
            fprintf(stderr, "error: commit %d: type is not an integer\n", (int) (i + 1));
            goto error;
        }

        position_x = json_object_get(data, "x");
        if (!json_is_integer(position_x)) {
            fprintf(stderr, "error: commit %d: x is not an integer\n", (int) (i + 1));
            goto error;
        }

        position_y = json_object_get(data, "y");
        if (!json_is_integer(position_y)) {
            fprintf(stderr, "error: commit %d: y is not an integer\n", (int) (i + 1));
            goto error;
        }

        color = json_object_get(data, "color");
        if (!json_is_integer(color)) {
            fprintf(stderr, "error: commit %d: y is not an integer\n", (int) (i + 1));
            goto error;
        }

        //int n = json_integer_value(type);
        //printf("N value %d\n",n);

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

    error:
    free(board);
    return NULL;
}
