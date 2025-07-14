
#ifndef __CRA_H__
#define __CRA_H__

/* main.c */

/* display.c */
void display_initialize();
void display_uninitialize();
void display_resize();
void display();
void display_update_matrix();
void display_destroy_matrix();
void display_create_matrix();
unsigned char display_rand_hex();
void display_set_size();
void display_check_resize();
int display_rand(int range);

/* debug.c */
void debug(const char *fmt, ...);
void debug_set(int state);


#endif /* __CRA_H__ */

