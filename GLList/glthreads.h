#ifndef __GLTHREADS_H__
#define __GLTHREADS_H__

#include <string>

class Node
{
    private:
	Node *left;
	Node *right;

    protected:
	std::string name;

    public:	
	static void addNext(Node *currNode, Node *newNode);
	static void removeNode(Node *node);
	Node *getLeft();
	Node *getRight();
	void setLeft(Node *);
	void setRight(Node *);
	void init();
//	virtual void setName(std::string name) = 0;
//	virtual std::string getName() const = 0;
};

class glthread
{
    public:
	Node *head;
	unsigned int offset;

    public:
	void addNode(Node *node); /* adding a new head to the list */
	void removeNode(Node *);

	void initThread(unsigned int offset);
};

#define BASE(glthreadptr) ((glthreadptr)->getRight())



/**
 * iteration over Gl_Threads
 */


#define ITERATE_GL_THREADS_BEGIN(glthreadptrstart, glthreadptr){\
    Node *nodeptr = nullptr;	\
    glthreadptr = BASE(glthreadptrstart);	\
    for(; glthreadptr; glthreadptr = nodeptr) { \
	nodeptr = BASE(glthreadptr);	
#define ITERATE_GL_THREADS_END(glthreadptrstart, glthreadptr) \
    }}
  



/* to do: try reinterpret_cast */
#define GLTHREAD_TO_STRUCT(fn_name, struct_name, field_name) \
    static inline struct_name *fn_name(glthread *glthreadptr) { \
	return (struct_name *)((char *)(glthreadptr) - (char *)&(((struct_name *)0)->field_name)); \
    }

#endif
