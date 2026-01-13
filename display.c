
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include <time.h>

#include "cra.h"

#define CTR_MAX 500

static int display_initialized = 0;
static int scr_W = -1; /* x */
static int scr_H = -1; /* y */
static int scr_WH = -1;
void display_initialize()
{
  debug("display_initialize()\n");
  srand(clock());

  initscr();
  raw();
  noecho();
  cbreak();
  curs_set(0);
  display_set_size();

  display_initialized = 1;
}

void display_uninitialize()
{
  debug("display_uninitialize()\n");
  curs_set(1);
  endwin();
}

struct cell
{
  int val;
  int ctr;
};

struct cell **matrix = NULL;

void display()
{
  int xx, yy;
  chtype attr = A_DIM;

  if(!display_initialized){ display_initialize(); }
  display_check_resize();
  display_update_matrix();

  for(xx=0 ; xx<scr_W ; xx++)
  {
    for(yy=0 ; yy<scr_H ; yy++)
    {
      if(0)
      {
        if((xx==0) || (xx==(scr_W-1)) || (yy==0) || (yy==(scr_H-1)))
        {
          mvwprintw(stdscr, yy, xx, "X");
          continue;
        }
        else if((xx==1) || (xx==(scr_W-2)) || (yy==1) || (yy==(scr_H-2)))
        {
          mvwprintw(stdscr, yy, xx, " ");
          continue;
        }
      }
      else
      {
        if     (matrix[xx][yy].ctr == 0              ) { attr = A_DIM     ; }
        else if(matrix[xx][yy].ctr <  ( CTR_MAX   /2)) { attr = A_NORMAL  ; }
        else                                           { attr = A_BOLD    ; }
      }
            
      if(1)
      {
        attron(attr);
        if(matrix[xx][yy].val >= 0)
        {
          mvwprintw(stdscr, yy, xx, "%X", matrix[xx][yy].val);
        }
        else
        {
          mvwprintw(stdscr, yy, xx, " ");
        }
        attroff(attr);
      }
      if(matrix[xx][yy].ctr > 0) { matrix[xx][yy].ctr--; }
    }
  }

  refresh();
}

void display_set_size()
{
  getmaxyx(stdscr, scr_H, scr_W);
  scr_WH = scr_W * scr_H;
  display_create_matrix();
  werase(stdscr);
  debug("display_set_size: w,h=%d,%d\n", scr_W, scr_H);
}

void display_resize()
{
  display_destroy_matrix();
  display_set_size();
  debug("display_resize: w,h=%d,%d\n", scr_W, scr_H);
}

void display_update_matrix()
{
  int xx, yy;
  int element;
  
  element = display_rand(scr_WH);
  matrix[element/scr_H][element%scr_H].val = display_rand_hex();
  matrix[element/scr_H][element%scr_H].ctr = CTR_MAX;
  
//  debug("disp-upd-matrix element: %d (%d,%d)\n", element, element/scr_H, element%scr_H);
}

void display_destroy_matrix()
{
  int xx;
  if(matrix == NULL) { return; }
  for(xx=0 ; xx<scr_W ; xx++)
  {
    if(matrix[xx] != NULL) { free(matrix[xx]); }
  }
  free(matrix);
  matrix = NULL;
}

void display_create_matrix()
{
  int xx, yy;
  if(matrix != NULL) { return; }
  matrix = (struct cell **)malloc(sizeof(struct cell *)*scr_W);
  for(xx=0 ; xx<scr_W ; xx++)
  {
    matrix[xx] = (struct cell *)malloc(sizeof(struct cell)*scr_H);
  }
  for(xx=0 ; xx<scr_W ; xx++)
  {
    for(yy=0 ; yy<scr_H ; yy++)
    {
//      matrix[xx][yy].val = display_rand_hex();
      matrix[xx][yy].val = -1;
      matrix[xx][yy].ctr = 0;
    }
  }
}

unsigned char display_rand_hex()
{
  return (unsigned char)rand();
}

void display_check_resize()
{
  static int xx, yy;
  getmaxyx(stdscr, yy, xx);
  if((xx != scr_W) || (yy != scr_H)) { display_resize(); }
}

int display_rand(int range)
{
  return (int)(((long long)rand() * (long long)range) / RAND_MAX);
}

