#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
/* #include <unistd.h> */

// Test all the key codes
// gcc ncurses1.c -g -o ncurses1 -lncursesw_g
// env NCURSES_TRACE=1 ncurses1 2>ncurses1.err

void static handle_sigint(/*@unused@*/ int sig) {
	(void) endwin();
	exit(0);
}

int main(/*@unused@*/ int argc, /*@unused@*/ char *argv[])
{
	// Register the signal handler
	(void) signal(SIGINT, handle_sigint);

	(void) initscr();
	(void) cbreak();
	(void) nonl();
	(void) echo();
	(void) keypad(stdscr, true);

	if (has_colors())
	{
		(void) start_color();
		(void) init_pair(1, COLOR_YELLOW, COLOR_BLACK);
		(void) attrset(1);
	}

	for (;;)
	{
		int ch = getch();
		_tracef("DJB: %d (%c)", ch, ch);
		switch(ch)
		{
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
				break;
	
			case KEY_RESIZE:
				_tracef("DJB: %s", "KEY_RESIZE");
				break;

		}

		(void) refresh();

	}

	/* This program quits via Ctrl-C */
	
}