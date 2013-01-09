
#include "TimeLine.h"

#include "Logger.h"

list<Task*> TimeLine::tasks;

void TimeLine::Clear()
{
	tasks.clear();
}

void TimeLine::AddLast(Task* r)
{
	tasks.push_back(r);
}

void TimeLine::Add(Task* r)// TODO: SkipList
{
	list<Task*>::iterator it = tasks.begin();
	list<Task*>::iterator prev = it;
	for(; it != tasks.end() && ((*it)->GetTime() < r->GetTime()); it++)
	{
		//prev = it;
	}
	tasks.insert(it, r);
}
void TimeLine::Execute()
{
	Logger::Log(LOGGER_INFO) << "TimeLine:" << "begin to Execute(" << tasks.size() << ")" << std::endl;
	int count = 0;
	while(tasks.size() > 0)
	{
		const Task* t = *(tasks.begin());
		unsigned int a = 0xabababab;
		const unsigned int value_of_pointer = (unsigned int)((void*)t);
		
		if(value_of_pointer == a)
		{
			printf("a=%d,",a);
			printf("value_of_pointer = %d",value_of_pointer);
			printf("t = %ud",t);
			printf("t = %p",t);
			printf("t = %X\n",t);
		}

		if(t!= NULL && a != value_of_pointer)
		{
			(*tasks.begin())->Execute();
			count++;
			if(count % 10000 == 0)
			{
				Logger::Log(LOGGER_INFO) << "TimeLine:" << count << "tasks have been Executed, " << tasks.size() << " left" << std::endl;
			}
			delete t;
		}else
		{
			Logger::Log(LOGGER_ERROR) << "TimeLine::Execute()have a null pointer task" << std::endl;
		}
		tasks.pop_front();
		//tasks.erase(tasks.begin());
	}
	Logger::Log(LOGGER_INFO) << "TimeLine:" << count << "tasks have been Executed in total" << std::endl;
}


int TimeLine::Size()
{
	return tasks.size();
}
