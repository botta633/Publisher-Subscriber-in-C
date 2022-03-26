#ifndef __NOTIF_H__
#define __NOTIF_H__

#include <pthread.h>
#include <stddef.h>
#include <string>
#include "./GLList/glthreads.h"

#define MAX_NOTIFICATION_KEY_SIZE 32

using namespace std;

class NotificationChain;
class NotificationElement;
enum class Operation;

typedef void (*nfc_app_cb)(void *, size_t, Operation, int);

enum class Operation
{
	NFC_UNKNOWN,
	NFC_ADD,
	NFC_MOD,
	NFC_DEL
};

class NotificationChain
{
public:
	NotificationChain(string name);
	char name[MAX_NOTIFICATION_KEY_SIZE];
	glthread head;
	void nfc_register_notif(NotificationElement *);
	void nfc_invoke_notif_chain(void *, size_t,
				    char *, size_t, Operation, int);
	void deleteAll();
	
};

class NotificationElement
{
public:
	char key[MAX_NOTIFICATION_KEY_SIZE];
	size_t key_size;
	bool is_key_set;
	nfc_app_cb app_cb;
	glthread glue;
};

GLTHREAD_TO_STRUCT(glthread_glue_to_notif_chain_elem,
				   NotificationElement, glue);

#endif
