#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Test all the key codes
/*
gcc ncurses3.c -g -o ncurses3 -lncursesw_g
env NCURSES_TRACE=1 ncurses3 2>ncurses3.err
*/

void static handle_sigint(/*@unused@*/ int sig) {
	(void) endwin();
	exit(0);
}

int main(/*@unused@*/int argc, /*@unused@*/ char *argv[])
{
	MEVENT mevent = { 0, 0, 0, 0, 0 };
	mmask_t all = (mmask_t) ALL_MOUSE_EVENTS;
	int button_alt = 0;
	int button_ctrl = 0;
	int button_shift = 0;
	int r = 1;

	// Register the signal handler
	(void) signal(SIGINT, handle_sigint);

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

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_NORMAL);
	(void) printw("%s", "A_NORMAL");
	(void) attroff(A_NORMAL);

	/* A_ATTRIBUTES...Bit-mask to extract attributes
	(void) move(r++, 1);
	(void) attron(A_ATTRIBUTES);
	(void) printw("%s", "A_ATTRIBUTES");
	(void) attroff(A_ATTRIBUTES); */

	/* A_CHARTEXT     Bit-mask to extract a character
	(void) move(r++, 1);
	(void) attron(A_CHARTEXT);
	(void) printw("%s", "A_CHARTEXT");
	(void) attroff(A_CHARTEXT); */

	/* A_COLOR        Bit-mask to extract a color (legacy routines)
	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_COLOR);
	(void) printw("%s", "A_COLOR");
	(void) attroff(A_COLOR); */

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_STANDOUT);
	(void) printw("%s", "A_STANDOUT");
	(void) attroff(A_STANDOUT);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_UNDERLINE);
	(void) printw("%s", "A_UNDERLINE");
	(void) attroff(A_UNDERLINE);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_REVERSE);
	(void) printw("%s", "A_REVERSE");
	(void) attroff(A_REVERSE);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_BLINK);
	(void) printw("%s", "A_BLINK");
	(void) attroff(A_BLINK);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_DIM);
	(void) printw("%s", "A_DIM");
	(void) attroff(A_DIM);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_BOLD);
	(void) printw("%s", "A_BOLD");
	(void) attroff(A_BOLD);

	/* A_ALTCHARSET   Alternate character set
	   set this atrribute on in order to use
	   the line drawing symbols
	(void) move(r++, 1);
	(void) attron(A_ALTCHARSET);
	(void) printw("%s", "A_ALTCHARSET");
	(void) attroff(A_ALTCHARSET); */

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_INVIS);
	(void) printw("%s", "A_INVIS");
	(void) attroff(A_INVIS);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_PROTECT);
	(void) printw("%s", "A_PROTECT");
	(void) attroff(A_PROTECT);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_HORIZONTAL);
	(void) printw("%s", "A_HORIZONTAL");
	(void) attroff(A_HORIZONTAL);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_LEFT);
	(void) printw("%s", "A_LEFT");
	(void) attroff(A_LEFT);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_LOW);
	(void) printw("%s", "A_LOW");
	(void) attroff(A_LOW);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_RIGHT);
	(void) printw("%s", "A_RIGHT");
	(void) attroff(A_RIGHT);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_TOP);
	(void) printw("%s", "A_TOP");
	(void) attroff(A_TOP);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_VERTICAL);
	(void) printw("%s", "A_VERTICAL");
	(void) attroff(A_VERTICAL);

	(void) move(r++, 1);
	(void) attron(COLOR_PAIR(1) | A_ITALIC);
	(void) printw("%s", "A_ITALIC");
	(void) attroff(A_ITALIC);

	(void) refresh();

	for (;;)
	{
		int ch = getch();
		_tracef("DJB: %d (%c)", ch, ch);
		switch(ch)
		{
			case 9:
				_tracef("DJB: %s", "TAB");
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
				if (ch < 128)
				{
					(void) printw("%c", ch);
				}
				else 
				{
					_tracef("DJB: Unsupported key code %d", ch);
				}

		}

		(void) refresh();

	}

}