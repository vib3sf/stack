#include <chrono>
#include <iostream>
#include <curses.h>
#include "array_stack.h"
#include "list_stack.h"
#include "stack.h"


inline std::chrono::system_clock::time_point get_time()
{
	return std::chrono::system_clock::now();
}

struct TempData {
	Stack<std::string>& stack;
	std::string last_pop;
	std::string err_msg;
	std::chrono::system_clock::time_point begin;
	
	TempData(Stack<std::string> &stack, std::string last_pop, 
			std::string err_msg)
		: stack(stack), last_pop(last_pop), err_msg(err_msg), 
		  begin(std::chrono::system_clock::from_time_t(0))
	{  }

	inline void update_begin()
	{
		begin = get_time();
	}
};

std::string input(std::string prompt)
{
	char str[256];

	move(LINES - 1, 0);
	clrtoeol();
	mvprintw(LINES - 1, 0, "%s: ", prompt.c_str());
	getstr(str);
	return str;
}

void push(TempData &tmp)
{
	std::string in = input("Input");

	tmp.update_begin();
	tmp.stack.Push(in);
}

void pop(TempData &tmp)
{
	if(!tmp.stack.IsEmpty()) 
		tmp.last_pop = tmp.stack.Pop();
	else
		tmp.err_msg = "Stack is empty";
}

void clear(TempData &tmp)
{
	tmp.stack.Clear();
}

void reverse(TempData &tmp)
{
	tmp.stack.Reverse();
}

void charge(TempData &tmp)
{
	std::string in = input("Input");
	clrtoeol();

	int count;

	try {
		count = stoi(input("Count"));
	}
	catch(...) {
		tmp.err_msg = "It isn't num :(";
		return;
	}

	tmp.update_begin();
	tmp.stack.Charge(in, count);
}

void display_action(const TempData& tmp) 
{
	mvprintw(6, 0, "Last pop: %s", tmp.last_pop.c_str());
	if(tmp.begin != std::chrono::system_clock::from_time_t(0))
		mvprintw(7, 0, "Time: %ld ms", std::chrono::duration_cast
			<std::chrono::microseconds>(get_time() - tmp.begin).count());
	mvprintw(LINES - 1, 0, "%s", tmp.err_msg.c_str());
}

void display_instruction()
{
	mvprintw(0, 0, "To add an element, enter a positive number.");
	mvprintw(1, 0, "To remove an element, press 'd'.");
	mvprintw(2, 0, "To clean, press 'c'.");
	mvprintw(3, 0, "To reverse, press 'r'.");
	mvprintw(4, 0, "To quit, press 'q'.");
}

void display_stack(const TempData& tmp)
{
	Stack<std::string> &tmp_stack = *tmp.stack.Clone();
    WINDOW *win = newwin(LINES - 4, 30, 3, COLS / 2 - 15);
	refresh();
    box(win, 0, 0);
	wrefresh(win);
	
    int yPos = LINES - tmp.stack.Size() - 2; 
    while (!tmp_stack.IsEmpty()) {
		std::string element = tmp_stack.Pop();
        int startX = (COLS - element.length()) / 2;
        mvprintw(yPos, startX, "%s", element.c_str());
        yPos++;
    }
}

void display(const TempData& tmp) 
{
	display_stack(tmp);
	display_instruction();
	display_action(tmp);
}

Stack<std::string>& stack_selection()
{
	Stack<std::string> *stack = 0;
	mvprintw(0, 0, "Choose (l)inked or (a)rray: ");
	while(!stack) {
		char input = getch();
		switch(input) {
			case 'l':
				stack = new ListStack<std::string>;
				break;
			case 'a':
				stack = new ArrayStack<std::string>;
				break;
		}
	}
	return *stack;
}

void init()
{
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
}

int main()
{
	init();

	TempData tmp(stack_selection(), "", "");
    while (true) {

        clear();
        display(tmp);
		tmp.err_msg = "";
		move(LINES - 1, COLS - 1);

        char input = getch();

		tmp.update_begin();
		switch(input) {
			case 'p':
				push(tmp);
				break;
			case 'd':
				pop(tmp);
				break;
			case 'c':
				clear(tmp);
				break;
			case 'r':
				reverse(tmp);
				break;
			case 'P':
				charge(tmp);
				break;
			case 'q':
				goto exit;
		}

	}

exit:
    endwin();
	return 0;
}

