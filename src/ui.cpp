#include <ui.h>
#include <curses.h>
#include <ncursesw/menu.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>

UI::UI(Cesar_Cypher *ces) {
  initscr(); // init ncurses routines

  cbreak(); // one char at a time

  noecho(); // surpress echo

  keypad(stdscr, TRUE); // special keys

  const char *choices[10][10] = {
      {"Caesar Cypher", "Run Caesar's cypher with the preconfigured message"},
      {"Change Message", "Change encrypted message before Running"},
      {"Exit", "Exit the program"}};

  int nr_choices = sizeof(choices) / sizeof((choices[0]));

  ITEM **choices_interface = (ITEM **)malloc(sizeof(ITEM *) * (nr_choices + 1));

  for (int i = 0; i < nr_choices; i++) {
    choices_interface[i] = new_item(choices[i][0], choices[i][1]);
  }

  choices_interface[nr_choices] = NULL;

  MENU *cesar_menu = new_menu((ITEM **)choices_interface);

  post_menu(cesar_menu);
  refresh();

  int c = 0;
  int selected_index = 0;
  bool run = true;

  while ((c = getch()) && run) {
    switch (c) {
    case KEY_DOWN:
      menu_driver(cesar_menu, REQ_DOWN_ITEM);
      if (selected_index < nr_choices)
        selected_index++;
      break;
    case KEY_UP:
      menu_driver(cesar_menu, REQ_UP_ITEM);
      if (selected_index > 0)
        selected_index--;
      break;
    case 10:
      if (selected_index == 2) {
        run = false;
      } else if (selected_index == 1) {
        system("code ./text.txt");
      } else if (selected_index == 0) {
        ces->decrypt(ces->text_file);
        system("code ./output.txt");
      }
      break;
    }
  }

  unpost_menu(cesar_menu);
  free_menu(cesar_menu);

  for (int i = 0; i < nr_choices; ++i)
    free_item(choices_interface[i]);
  endwin();
}
