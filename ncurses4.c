#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Test tabbing between fields
/*
gcc ncurses4.c -g -o ncurses4 -lncursesw_g
rm -f trace; env NCURSES_TRACE=1 ncurses4 2>ncurses4.err; cat ncurses4.err
*/

/* TODO?
    Use left or right arrow keys to insert text in a field
    Save the binary data to a file
    Read the binary data from a file
    Save the delimited data to a file
    Read the delimited data from a file
    Scroll to the next record
*/

int fldlen(const int y, const int x, const int l) 
{
	int x1 = x;
	int x2 = x + l;
	//fprintf(stderr, "fldlen:      y: %d\n", y);
	//fprintf(stderr, "fldlen:      x: %d\n", x);
	//fprintf(stderr, "fldlen:      l: %d\n", l);
	//fprintf(stderr, "fldlen:     x1: %d\n", x1);
	//fprintf(stderr, "fldlen:     x2: %d\n", x2);
	for (x2; x2 >= x1; x2--)
	{
		int c = (mvinch(y, x2) & A_CHARTEXT);
		//fprintf(stderr, "fldlen:     x2: %d\n", x2);
		//fprintf(stderr, "fldlen:      c: %d\n", c);
		if (c > 32) {
			//fprintf(stderr, "fldlen:      r: %d\n\n", x2 - x1 + 1);
			return x2 - x1 + 1;
		}
	}
	//fprintf(stderr, "fldlen:fallthru: %d\n\n", 0);
	return 0;
}

char *mvfld(const int y, const int x, const int l)
{
	int x1 = x;
	int x2 = x + l;
	char *field;
	field = malloc(l + 1);
	if (field == NULL)
	{
		exit(EXIT_FAILURE);
	}
	char *f = field;
	//fprintf(stderr, "*mvfld:      y: %d\n", y);
	//fprintf(stderr, "*mvfld:      x: %d\n", x);
	//fprintf(stderr, "*mvfld:      l: %d\n", l);
	//fprintf(stderr, "*mvfld:     x1: %d\n", x1);
	//fprintf(stderr, "*mvfld:     x2: %d\n", x2);
	for (x1; x1<x2; x1++) 
	{
		int c = (mvinch(y, x1) & A_CHARTEXT);
		//fprintf(stderr, "*mvfld:     x1: %d\n", x1);
		//fprintf(stderr, "*mvfld:      c: %d\n", c);
		*(f++) = c;
	}
	*(f) = 0;
	//fprintf(stderr, "*mvfld:fallthru: %s\n\n", field);
	return field;
}

struct LABEL {
	int y;
	int x;
	int l;
	int fac;
	char l_value[31];
};

struct VALUE {
	int y;
	int x;
	int l;
	int fac;
	char c_value[2001];
	char o_value[2001];
};

struct FIELD {
	struct LABEL label;
	struct VALUE value;
};

struct CURSOR {
	int y;
	int x;
};

int main(/*@unused@*/int argc, /*@unused@*/ char *argv[])
{
	MEVENT mevent = { 0, 0, 0, 0, 0 };
	mmask_t all = (mmask_t) ALL_MOUSE_EVENTS;
	int button_alt = 0;
	int button_ctrl = 0;
	int button_shift = 0;
	int r = 1;
	
	char spaces[2001];
	for (int i=0; i<sizeof(spaces) - 1; i++) {
		spaces[i] = 32;  // space
	}
	spaces[2000] = 0;

	struct CURSOR cursor = { -1, -1 };
	struct CURSOR curmax = { -1, -1 };
	struct LABEL label = { -1, -1, -1, 0, "" };
	struct VALUE value = { -1, -1, -1, 0, "", "" };
	struct FIELD field = { label, value };
	struct FIELD fields[5];
	//fprintf(stderr, "sizeof(fields)/sizeof(field) == %ld\n", sizeof(fields)/sizeof(field));
	/* initialize the fields */
	for (int i=0; i<sizeof(fields)/sizeof(field); i++)
	{
		fields[i] = field;
	}
	/* set up the fields */
	fields[0].label.y = 1;
	fields[0].label.x = 1;
	fields[0].label.l = 20;
	fields[0].label.fac = (COLOR_PAIR(1) | A_NORMAL);
	//                                123456789012345678901234567890
	strncpy(fields[0].label.l_value, "          First Name", fields[0].label.l);
	fields[0].value.y = fields[0].label.y;
	fields[0].value.x = fields[0].label.x + fields[0].label.l + 1;
	fields[0].value.l = 30;
	fields[0].value.fac = (COLOR_PAIR(1) | A_UNDERLINE);
	strncpy(fields[0].value.c_value, spaces, fields[0].value.l);

	fields[1].label.y = fields[1 - 1].label.y + 1;
	fields[1].label.x = 1;
	fields[1].label.l = 20;
	fields[1].label.fac = (COLOR_PAIR(1) | A_NORMAL);
	//                                123456789012345678901234567890
	strncpy(fields[1].label.l_value, "           Last Name", fields[1].label.l);
	fields[1].value.y = fields[1].label.y;
	fields[1].value.x = fields[1].label.x + fields[1].label.l + 1;
	fields[1].value.l = 30;
	fields[1].value.fac = (COLOR_PAIR(1) | A_UNDERLINE);
	strncpy(fields[1].value.c_value, spaces, fields[1].value.l);

	fields[2].label.y = fields[2 - 1].label.y + 1;
	fields[2].label.x = 1;
	fields[2].label.l = 20;
	fields[2].label.fac = (COLOR_PAIR(1) | A_NORMAL);
	//                                123456789012345678901234567890
	strncpy(fields[2].label.l_value, "          Birth Date", fields[2].label.l);
	fields[2].value.y = fields[2].label.y;
	fields[2].value.x = fields[2].label.x + fields[2].label.l + 1;
	fields[2].value.l = 10;
	fields[2].value.fac = (COLOR_PAIR(1) | A_UNDERLINE);
	strncpy(fields[2].value.c_value, spaces, fields[2].value.l);

	fields[3].label.y = fields[3 - 1].label.y + 1;
	fields[3].label.x = 1;
	fields[3].label.l = 20;
	fields[3].label.fac = (COLOR_PAIR(1) | A_NORMAL);
	//                                123456789012345678901234567890
	strncpy(fields[3].label.l_value, "        Phone Number", fields[3].label.l);
	fields[3].value.y = fields[3].label.y;
	fields[3].value.x = fields[3].label.x + fields[3].label.l + 1;
	fields[3].value.l = 15;
	fields[3].value.fac = (COLOR_PAIR(1) | A_UNDERLINE);
	strncpy(fields[3].value.c_value, spaces, fields[3].value.l);

	fields[4].label.y = fields[4 - 1].label.y + 1;
	fields[4].label.x = 1;
	fields[4].label.l = 20;
	fields[4].label.fac = (COLOR_PAIR(1) | A_NORMAL);
	//                                123456789012345678901234567890
	strncpy(fields[4].label.l_value, "       Email Address", fields[4].label.l);
	fields[4].value.y = fields[4].label.y;
	fields[4].value.x = fields[4].label.x + fields[4].label.l + 1;
	fields[4].value.l = 60;
	fields[4].value.fac = (COLOR_PAIR(1) | A_UNDERLINE);
	strncpy(fields[4].value.c_value, spaces, fields[4].value.l);

	(void) initscr();
	(void) cbreak();
	(void) nonl();
	(void) noecho();
	(void) keypad(stdscr, true);
	(void) mousemask(all, /*@i@*/ NULL);

	if (has_colors())
	{
		(void) start_color();
		(void) init_pair(1, COLOR_YELLOW, COLOR_BLACK);
		(void) attrset(COLOR_PAIR(1));
	}

	// paint the screen using the fields
	for (int i=0; i<sizeof(fields)/sizeof(field); i++)
	{
		if (fields[i].label.y != -1)
		{
			//(void) move(fields[i].value.y, 0);
			(void) move(fields[i].label.y, fields[i].label.x);
			(void) attron(fields[i].label.fac);
			(void) printw("%s", fields[i].label.l_value);
			(void) move(fields[i].label.y, fields[i].label.x + fields[i].label.l);
			(void) attroff(fields[i].label.fac);
		}
		if (fields[i].value.y != -1)
		{
			(void) move(fields[i].value.y, fields[i].value.x);
			(void) attron(fields[i].value.fac);
			(void) printw("%s", fields[i].value.c_value);
			(void) move(fields[i].value.y, fields[i].value.x + fields[i].value.l);
			(void) attroff(fields[i].value.fac);
			if (cursor.y == -1)
			{
				cursor.y = fields[i].value.y;
				cursor.x = fields[i].value.x;
			}
		}
	}
	(void) getmaxyx(stdscr, curmax.y, curmax.x);
	fprintf(stderr, "cursor max y, x = %d, %d", curmax.y, curmax.x);
	(void) move(curmax.y - 2, 2);
	(void) attron(COLOR_PAIR(1) | A_NORMAL);
	(void) printw("(16) Exit");
	//(void) attroff(COLOR_PAIR(1) | A_NORMAL);
	(void) move(cursor.y, cursor.x);
	(void) refresh();

	for (;;)
	{
		int ch = getch();
		_tracef("DJB: %d (%c)", ch, ch);
		(void) getyx(stdscr, cursor.y, cursor.x);
		_tracef("DJB: y=%d x=%d", cursor.y, cursor.x);

		switch(ch)
		{
			case 9:
				_tracef("DJB: %s", "TAB");
				for (int i=0; i<sizeof(fields)/sizeof(field); i++)
				{
					if (cursor.y == fields[i].value.y &&
						cursor.x >= fields[i].value.x && 
						cursor.x <= fields[i].value.x + fields[i].value.l)
					{
						char *p = mvfld(fields[i].value.y, fields[i].value.x, fields[i].value.l);
						strcpy(fields[i].value.c_value, p);
						free(p);
						fprintf(stderr, "KEY_TAB: %s\n", fields[i].value.c_value);
						if (i<sizeof(fields)/sizeof(field) - 1)
						{
							(void) move(fields[i + 1].value.y, fields[i + 1].value.x + \
								 fldlen(fields[i + 1].value.y, fields[i + 1].value.x, fields[i + 1].value.l));
							(void) attron(fields[i + 1].value.fac);
						}
						else
						{
							(void) move(fields[0].value.y, fields[0].value.x + \
								 fldlen(fields[0].value.y, fields[0].value.x, fields[0].value.l));
							(void) attron(fields[0].value.fac);
						}

						break;
					}
				}
				break;

			case 10:
				_tracef("DJB: %s", "NEWLINE");
				break;

			case 13:
				_tracef("DJB: %s", "RETURN");
				break;

			case KEY_CODE_YES:
				_tracef("DJB: %s", "KEY_CODE_YES");
				break;

			// same as KEY_BREAK
			//case KEY_MIN:
			//	_tracef("DJB: %s", "KEY_MIN");
			//	break;
	
			case KEY_BREAK:
				_tracef("DJB: %s", "KEY_BREAK");
				break;
	
			case KEY_SRESET:
				_tracef("DJB: %s", "KEY_SRESET");
				break;
	
			case KEY_RESET:
				_tracef("DJB: %s", "KEY_RESET");
				break;
	
			case KEY_DOWN:
				_tracef("DJB: %s", "KEY_DOWN");
				break;
	
			case KEY_UP:
				_tracef("DJB: %s", "KEY_UP");
				break;
	
			case KEY_LEFT:
				_tracef("DJB: %s", "KEY_LEFT");
				break;
	
			case KEY_RIGHT:
				_tracef("DJB: %s", "KEY_RIGHT");
				break;
	
			case KEY_HOME:
				_tracef("DJB: %s", "KEY_HOME");
				break;
	
			case KEY_BACKSPACE:
				_tracef("DJB: %s", "KEY_BACKSPACE");
				for (int i=0; i<sizeof(fields)/sizeof(field); i++)
				{
					if (cursor.y == fields[i].value.y &&
						cursor.x >  fields[i].value.x && 
						cursor.x <= fields[i].value.x + fields[i].value.l)
					{
						(void) move(cursor.y, --cursor.x);
						(void) attron(fields[i].value.fac);
						(void) printw("%c", 32);
						(void) move(cursor.y, cursor.x);
						break;
					}
				}
				break;
	
			case KEY_F0:
				_tracef("DJB: %s", "KEY_F0");
				break;
	
			case KEY_F(1):
				_tracef("DJB: %s", "KEY_F(1)");
				break;
	
			case KEY_F(2):
				_tracef("DJB: %s", "KEY_F(2)");
				break;
	
			case KEY_F(3):
				_tracef("DJB: %s", "KEY_F(3)");
				break;
	
			case KEY_F(4):
				_tracef("DJB: %s", "KEY_F(4)");
				break;
	
			case KEY_F(5):
				_tracef("DJB: %s", "KEY_F(5)");
				break;
	
			case KEY_F(6):
				_tracef("DJB: %s", "KEY_F(6)");
				break;
	
			case KEY_F(7):
				_tracef("DJB: %s", "KEY_F(7)");
				break;
	
			case KEY_F(8):
				_tracef("DJB: %s", "KEY_F(8)");
				break;
	
			case KEY_F(9):
				_tracef("DJB: %s", "KEY_F(9)");
				break;
	
			case KEY_F(10):
				_tracef("DJB: %s", "KEY_F(10)");
				break;
	
			case KEY_F(11):
				_tracef("DJB: %s", "KEY_F(11)");
				break;
	
			case KEY_F(12):
				_tracef("DJB: %s", "KEY_F(12)");
				break;
	
			case KEY_F(13):
				_tracef("DJB: %s", "KEY_F(13)");
				break;
	
			case KEY_F(14):
				_tracef("DJB: %s", "KEY_F(14)");
				break;
	
			case KEY_F(15):
				_tracef("DJB: %s", "KEY_F(15)");
				break;
	
			case KEY_F(16):
				_tracef("DJB: %s", "KEY_F(16)");
				fprintf(stderr, "KEY_F(16)\n");
				for (int i=0; i<sizeof(fields)/sizeof(field); i++)
				{
					if (cursor.y == fields[i].value.y &&
						cursor.x >= fields[i].value.x && 
						cursor.x <= fields[i].value.x + fields[i].value.l)
					{
						char *p = mvfld(fields[i].value.y, fields[i].value.x, fields[i].value.l);
						strcpy(fields[i].value.c_value, p);
						free(p);
						fprintf(stderr, "KEY_F(16): %s\n", fields[i].value.c_value);
					}
				}
				for (int i=0; i<sizeof(fields)/sizeof(field); i++)
				{
					fprintf(stderr, "KEY_F(16): %s: %s\n", fields[i].label.l_value, fields[i].value.c_value);
				}
				(void) endwin();
				exit(0);
				break;
	
			case KEY_F(17):
				_tracef("DJB: %s", "KEY_F(17)");
				break;
	
			case KEY_F(18):
				_tracef("DJB: %s", "KEY_F(18)");
				break;

			case KEY_F(19):
				_tracef("DJB: %s", "KEY_F(19)");
				break;

			case KEY_F(20):
				_tracef("DJB: %s", "KEY_F(20)");
				break;

			case KEY_F(21):
				_tracef("DJB: %s", "KEY_F(21)");
				break;

			case KEY_F(22):
				_tracef("DJB: %s", "KEY_F(22)");
				break;

			case KEY_F(23):
				_tracef("DJB: %s", "KEY_F(23)");
				break;

			case KEY_F(24):
				_tracef("DJB: %s", "KEY_F(24)");
				break;

			case KEY_DL:
				_tracef("DJB: %s", "KEY_DL");
				break;
	
			case KEY_IL:
				_tracef("DJB: %s", "KEY_IL");
				break;
	
			case KEY_DC:
				_tracef("DJB: %s", "KEY_DC");
				break;
	
			case KEY_IC:
				_tracef("DJB: %s", "KEY_IC");
				break;
	
			case KEY_EIC:
				_tracef("DJB: %s", "KEY_EIC");
				break;
	
			case KEY_CLEAR:
				_tracef("DJB: %s", "KEY_CLEAR");
				break;
	
			case KEY_EOS:
				_tracef("DJB: %s", "KEY_EOS");
				break;
	
			case KEY_EOL:
				_tracef("DJB: %s", "KEY_EOL");
				break;
	
			case KEY_SF:
				_tracef("DJB: %s", "KEY_SF");
				break;
	
			case KEY_SR:
				_tracef("DJB: %s", "KEY_SR");
				break;
	
			case KEY_NPAGE:
				_tracef("DJB: %s", "KEY_NPAGE");
				break;
	
			case KEY_PPAGE:
				_tracef("DJB: %s", "KEY_PPAGE");
				break;
	
			case KEY_STAB:
				_tracef("DJB: %s", "KEY_STAB");
				break;
	
			case KEY_CTAB:
				_tracef("DJB: %s", "KEY_CTAB");
				break;
	
			case KEY_CATAB:
				_tracef("DJB: %s", "KEY_CATAB");
				break;
	
			case KEY_ENTER:
				_tracef("DJB: %s", "KEY_ENTER");
				break;
	
			case KEY_PRINT:
				_tracef("DJB: %s", "KEY_PRINT");
				break;
	
			case KEY_LL:
				_tracef("DJB: %s", "KEY_LL");
				break;
	
			case KEY_A1:
				_tracef("DJB: %s", "KEY_A1");
				break;
	
			case KEY_A3:
				_tracef("DJB: %s", "KEY_A3");
				break;
	
			case KEY_B2:
				_tracef("DJB: %s", "KEY_B2");
				break;
	
			case KEY_C1:
				_tracef("DJB: %s", "KEY_C1");
				break;
	
			case KEY_C3:
				_tracef("DJB: %s", "KEY_C3");
				break;
	
			case KEY_BTAB:
				_tracef("DJB: %s", "KEY_BTAB");
				for (int i=0; i<sizeof(fields)/sizeof(field); i++)
				{
					if (cursor.y == fields[i].value.y &&
						cursor.x >= fields[i].value.x && 
						cursor.x <= fields[i].value.x + fields[i].value.l)
					{
						char *p = mvfld(fields[i].value.y, fields[i].value.x, fields[i].value.l);
						strcpy(fields[i].value.c_value, p);
						free(p);
						fprintf(stderr, "KEY_BTAB: %s\n", fields[i].value.c_value);
						if (i>0)
						{
							(void) move(fields[i - 1].value.y, \
										fields[i - 1].value.x + \
								 fldlen(fields[i - 1].value.y, \
										fields[i - 1].value.x, \
										fields[i - 1].value.l));
							(void) attron(fields[i - 1].value.fac);
						}
						else
						{
							(void) move(fields[sizeof(fields)/sizeof(field) - 1].value.y, \
									    fields[sizeof(fields)/sizeof(field) - 1].value.x + \
								 fldlen(fields[sizeof(fields)/sizeof(field) - 1].value.y, \
								 		fields[sizeof(fields)/sizeof(field) - 1].value.x, \
								 		fields[sizeof(fields)/sizeof(field) - 1].value.l));
							(void) attron(fields[sizeof(fields)/sizeof(field) - 1].value.fac);
						}
						break;
					}
				}
				break;
	
			case KEY_BEG:
				_tracef("DJB: %s", "KEY_BEG");
				break;
	
			case KEY_CANCEL:
				_tracef("DJB: %s", "KEY_CANCEL");
				break;
	
			case KEY_CLOSE:
				_tracef("DJB: %s", "KEY_CLOSE");
				break;
	
			case KEY_COMMAND:
				_tracef("DJB: %s", "KEY_COMMAND");
				break;
	
			case KEY_COPY:
				_tracef("DJB: %s", "KEY_COPY");
				break;
	
			case KEY_CREATE:
				_tracef("DJB: %s", "KEY_CREATE");
				break;
	
			case KEY_END:
				_tracef("DJB: %s", "KEY_END");
				break;
	
			case KEY_EXIT:
				_tracef("DJB: %s", "KEY_EXIT");
				break;
	
			case KEY_FIND:
				_tracef("DJB: %s", "KEY_FIND");
				break;
	
			case KEY_HELP:
				_tracef("DJB: %s", "KEY_HELP");
				break;
	
			case KEY_MARK:
				_tracef("DJB: %s", "KEY_MARK");
				break;
	
			case KEY_MESSAGE:
				_tracef("DJB: %s", "KEY_MESSAGE");
				break;
	
			case KEY_MOVE:
				_tracef("DJB: %s", "KEY_MOVE");
				break;
	
			case KEY_NEXT:
				_tracef("DJB: %s", "KEY_NEXT");
				break;
	
			case KEY_OPEN:
				_tracef("DJB: %s", "KEY_OPEN");
				break;
	
			case KEY_OPTIONS:
				_tracef("DJB: %s", "KEY_OPTIONS");
				break;
	
			case KEY_PREVIOUS:
				_tracef("DJB: %s", "KEY_PREVIOUS");
				break;
	
			case KEY_REDO:
				_tracef("DJB: %s", "KEY_REDO");
				break;
	
			case KEY_REFERENCE:
				_tracef("DJB: %s", "KEY_REFERENCE");
				break;
	
			case KEY_REFRESH:
				_tracef("DJB: %s", "KEY_REFRESH");
				break;
	
			case KEY_REPLACE:
				_tracef("DJB: %s", "KEY_REPLACE");
				break;
	
			case KEY_RESTART:
				_tracef("DJB: %s", "KEY_RESTART");
				break;
	
			case KEY_RESUME:
				_tracef("DJB: %s", "KEY_RESUME");
				break;
	
			case KEY_SAVE:
				_tracef("DJB: %s", "KEY_SAVE");
				break;
	
			case KEY_SBEG:
				_tracef("DJB: %s", "KEY_SBEG");
				break;
	
			case KEY_SCANCEL:
				_tracef("DJB: %s", "KEY_SCANCEL");
				break;
	
			case KEY_SCOMMAND:
				_tracef("DJB: %s", "KEY_SCOMMAND");
				break;
	
			case KEY_SCOPY:
				_tracef("DJB: %s", "KEY_SCOPY");
				break;
	
			case KEY_SCREATE:
				_tracef("DJB: %s", "KEY_SCREATE");
				break;
	
			case KEY_SDC:
				_tracef("DJB: %s", "KEY_SDC");
				break;
	
			case KEY_SDL:
				_tracef("DJB: %s", "KEY_SDL");
				break;
	
			case KEY_SELECT:
				_tracef("DJB: %s", "KEY_SELECT");
				break;
	
			case KEY_SEND:
				_tracef("DJB: %s", "KEY_SEND");
				break;
	
			case KEY_SEOL:
				_tracef("DJB: %s", "KEY_SEOL");
				break;
	
			case KEY_SEXIT:
				_tracef("DJB: %s", "KEY_SEXIT");
				break;
	
			case KEY_SFIND:
				_tracef("DJB: %s", "KEY_SFIND");
				break;
	
			case KEY_SHELP:
				_tracef("DJB: %s", "KEY_SHELP");
				break;
	
			case KEY_SHOME:
				_tracef("DJB: %s", "KEY_SHOME");
				break;
	
			case KEY_SIC:
				_tracef("DJB: %s", "KEY_SIC");
				break;
	
			case KEY_SLEFT:
				_tracef("DJB: %s", "KEY_SLEFT");
				break;
	
			case KEY_SMESSAGE:
				_tracef("DJB: %s", "KEY_SMESSAGE");
				break;
	
			case KEY_SMOVE:
				_tracef("DJB: %s", "KEY_SMOVE");
				break;
	
			case KEY_SNEXT:
				_tracef("DJB: %s", "KEY_SNEXT");
				break;
	
			case KEY_SOPTIONS:
				_tracef("DJB: %s", "KEY_SOPTIONS");
				break;
	
			case KEY_SPREVIOUS:
				_tracef("DJB: %s", "KEY_SPREVIOUS");
				break;
	
			case KEY_SPRINT:
				_tracef("DJB: %s", "KEY_SPRINT");
				break;
	
			case KEY_SREDO:
				_tracef("DJB: %s", "KEY_SREDO");
				break;
	
			case KEY_SREPLACE:
				_tracef("DJB: %s", "KEY_SREPLACE");
				break;
	
			case KEY_SRIGHT:
				_tracef("DJB: %s", "KEY_SRIGHT");
				break;
	
			case KEY_SRSUME:
				_tracef("DJB: %s", "KEY_SRSUME");
				break;
	
			case KEY_SSAVE:
				_tracef("DJB: %s", "KEY_SSAVE");
				break;
	
			case KEY_SSUSPEND:
				_tracef("DJB: %s", "KEY_SSUSPEND");
				break;
	
			case KEY_SUNDO:
				_tracef("DJB: %s", "KEY_SUNDO");
				break;
	
			case KEY_SUSPEND:
				_tracef("DJB: %s", "KEY_SUSPEND");
				break;
	
			case KEY_UNDO:
				_tracef("DJB: %s", "KEY_UNDO");
				break;
	
			case KEY_MOUSE:
				_tracef("DJB: %s", "KEY_MOUSE");
				
				(void) getmouse(&mevent);

				_tracef("DJB: mevent.x is %d", mevent.x);
				_tracef("DJB: mevent.y is %d", mevent.y);
				_tracef("DJB: mevent.bstate is %d", mevent.bstate);
				//_tracef("DJB: BUTTON1_PRESSED is %d", BUTTON1_PRESSED);
				//_tracef("DJB: mevent.bstate & BUTTON1_PRESSED is %d", mevent.bstate & BUTTON1_PRESSED);

				if ((mevent.bstate & BUTTON_ALT) != 0)
				{
					button_alt = 1;
					_tracef("DJB: %s", "BUTTON_ALT");
				}
				if ((mevent.bstate & BUTTON_CTRL) != 0)
				{
					button_ctrl = 1;
					_tracef("DJB: %s", "BUTTON_CTRL");
				}
				if ((mevent.bstate & BUTTON_SHIFT) != 0)
				{
					button_shift = 1;
					_tracef("DJB: %s", "BUTTON_SHIFT");
				}

				if ((mevent.bstate & BUTTON1_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON1_CLICKED");
				}
				if ((mevent.bstate & BUTTON1_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON1_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON1_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON1_PRESSED");
				}
				if ((mevent.bstate & BUTTON1_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON1_RELEASED");
				}
				//if ((mevent.bstate & BUTTON1_RESERVED_EVENT) != 0)
				//{
				//	_tracef("DJB: %s", "BUTTON1_RESERVED_EVENT");
				//}
				if ((mevent.bstate & BUTTON1_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON1_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON2_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON2_CLICKED");
				}
				if ((mevent.bstate & BUTTON2_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON2_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON2_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON2_PRESSED");
				}
				if ((mevent.bstate & BUTTON2_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON2_RELEASED");
				}
				//if ((mevent.bstate & BUTTON2_RESERVED_EVENT) != 0)
				//{
				//	_tracef("DJB: %s", "BUTTON2_RESERVED_EVENT");
				//}
				if ((mevent.bstate & BUTTON2_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON2_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON3_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON3_CLICKED");
				}
				if ((mevent.bstate & BUTTON3_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON3_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON3_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON3_PRESSED");
				}
				if ((mevent.bstate & BUTTON3_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON3_RELEASED");
				}
				//if ((mevent.bstate & BUTTON3_RESERVED_EVENT) != 0)
				//{
				//	_tracef("DJB: %s", "BUTTON3_RESERVED_EVENT");
				//}
				if ((mevent.bstate & BUTTON3_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON3_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON4_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON4_CLICKED");
				}
				if ((mevent.bstate & BUTTON4_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON4_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON4_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON4_PRESSED");
				}
				if ((mevent.bstate & BUTTON4_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON4_RELEASED");
				}
				//if ((mevent.bstate & BUTTON4_RESERVED_EVENT) != 0)
				//{
				//	_tracef("DJB: %s", "BUTTON4_RESERVED_EVENT");
				//}
				if ((mevent.bstate & BUTTON4_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON4_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON5_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON5_CLICKED");
				}
				if ((mevent.bstate & BUTTON5_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON5_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON5_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON5_PRESSED");
				}
				if ((mevent.bstate & BUTTON5_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON5_RELEASED");
				}
				if ((mevent.bstate & BUTTON5_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON5_TRIPLE_CLICKED");
				}
				/*if ((mevent.bstate & BUTTON6_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON6_CLICKED");
				}
				if ((mevent.bstate & BUTTON6_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON6_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON6_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON6_PRESSED");
				}
				if ((mevent.bstate & BUTTON6_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON6_RELEASED");
				}
				if ((mevent.bstate & BUTTON6_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON6_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON7_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON7_CLICKED");
				}
				if ((mevent.bstate & BUTTON7_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON7_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON7_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON7_PRESSED");
				}
				if ((mevent.bstate & BUTTON7_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON7_RELEASED");
				}
				if ((mevent.bstate & BUTTON7_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON7_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON8_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON8_CLICKED");
				}
				if ((mevent.bstate & BUTTON8_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON8_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON8_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON8_PRESSED");
				}
				if ((mevent.bstate & BUTTON8_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON8_RELEASED");
				}
				if ((mevent.bstate & BUTTON8_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON8_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON9_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON9_CLICKED");
				}
				if ((mevent.bstate & BUTTON9_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON9_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON9_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON9_PRESSED");
				}
				if ((mevent.bstate & BUTTON9_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON9_RELEASED");
				}
				if ((mevent.bstate & BUTTON9_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON9_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON10_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON10_CLICKED");
				}
				if ((mevent.bstate & BUTTON10_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON10_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON10_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON10_PRESSED");
				}
				if ((mevent.bstate & BUTTON10_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON10_RELEASED");
				}
				if ((mevent.bstate & BUTTON10_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON10_TRIPLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON11_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON11_CLICKED");
				}
				if ((mevent.bstate & BUTTON11_DOUBLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON11_DOUBLE_CLICKED");
				}
				if ((mevent.bstate & BUTTON11_PRESSED) != 0)
				{
					_tracef("DJB: %s", "BUTTON11_PRESSED");
				}
				if ((mevent.bstate & BUTTON11_RELEASED) != 0)
				{
					_tracef("DJB: %s", "BUTTON11_RELEASED");
				}
				if ((mevent.bstate & BUTTON11_TRIPLE_CLICKED) != 0)
				{
					_tracef("DJB: %s", "BUTTON11_TRIPLE_CLICKED");
				}*/
				button_alt = 0;
				button_ctrl = 0;
				button_shift = 0;

				break;
	
			case KEY_RESIZE:
				_tracef("DJB: %s", "KEY_RESIZE");
				break;

			default:
				if (ch > 31 && ch < 128)
				{
					for (int i=0; i<sizeof(fields)/sizeof(field); i++)
					{
						if (cursor.y == fields[i].value.y &&
							cursor.x >= fields[i].value.x && 
							cursor.x <  fields[i].value.x + fields[i].value.l)
						{
							(void) attron(fields[i].value.fac);
							(void) printw("%c", ch);
							break;
						}
					}
				}
				else 
				{
					_tracef("DJB: Unsupported key code %d", ch);
				}

		}

		(void) refresh();

	}

}