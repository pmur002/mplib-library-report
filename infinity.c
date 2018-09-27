#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mplib.h"

void mp_dump_solved_path (MP mp, mp_knot h) {
    mp_knot p, q;
    if (h == NULL) return;
    p = h;
    do {
        q=mp_knot_next(mp,p);
        printf ("(%g,%g)..controls (%g,%g) and (%g,%g)",
                mp_number_as_double(mp,p->x_coord),
                mp_number_as_double(mp,p->y_coord),
                mp_number_as_double(mp,p->right_x),
                mp_number_as_double(mp,p->right_y),
                mp_number_as_double(mp,q->left_x),
                mp_number_as_double(mp,q->left_y));
        p=q;
        if ( p!=h || h->data.types.left_type!=mp_endpoint) {
            printf ("\n ..");
        }
    } while (p!=h);
    if ( h->data.types.left_type!=mp_endpoint )
        printf("cycle");
    printf (";\n");
}

int main (int argc, char ** argv) {
    MP mp;
    mp_knot p, first, q;
    int result;
    MP_options * opt = mp_options();
    opt -> command_line = NULL;
    opt -> noninteractive = 1;
    mp = mp_initialize(opt);
    first = p = mp_append_knot(mp, NULL, 0, 0);
    mp_set_knot_direction(mp, p, 1, 0);
    q = mp_append_knot(mp, p, 20, 10);
    mp_set_knot_direction(mp, q, 1, 0);
    p = mp_append_knot(mp, q, 20, 0);
    mp_set_knot_direction(mp, p, -1, 0);
    q = mp_append_knot(mp, p, 0, 10);
    mp_set_knot_direction(mp, q, -1, 0);
    mp_close_path_cycle(mp, q, first);
    if (mp_solve_path(mp, first)) {
        mp_dump_solved_path(mp, first);
    }
    mp_free_path(mp, first);
    mp_finish(mp);
    free(opt);
    return 0;
}
