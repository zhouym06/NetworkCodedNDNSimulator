
#ifndef __FIB_ENTRY_H__
#define __FIB_ENTRY_H__


class FIBEntry{
	int _distance;
	double _delay;
	//string prefix;
	int _server_no;
	int _next_interface;
public:
	~FIBEntry();
	friend class FIB;
	void Set(int distance, double delay, int server_no, int next_interface);
	void Display();

};

#endif
