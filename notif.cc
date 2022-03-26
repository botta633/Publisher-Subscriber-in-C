#include "notif.h"
#include <memory>
#include <stdlib.h>
#include <string.h>
#include "./GLList/glthreads.h"

NotificationChain::NotificationChain(string name)
{
    assert(name.size() >= MAX_NOTIFICATION_KEY_SIZE);
    for (int i = 0; i < name.size(); i++)
        this->name[i] = name[i];
}

void NotificationChain::nfc_register_notif(NotificationElement *element)
{

    Node *el = new Node;
    el->init();
    element->glue.head = el;
    this->head.addNode(element->glue.head);
}

void NotificationChain::nfc_invoke_notif_chain(void *arg, size_t arg_size,
                                               char *key, size_t key_size,
                                               Operation operation, int subscriberID)
{
    glthread *curr = new glthread;

    NotificationElement *el = new NotificationElement;

    assert(key_size <= MAX_NOTIFICATION_KEY_SIZE);

    ITERATE_GL_THREADS_BEGIN(this->head.head, curr->head)
    {
        el = glthread_glue_to_notif_chain_elem(curr);

        /* wild card case when there is no notifications */
        if ((!key && key_size &&
             el->is_key_set && (key_size == el->key_size)))
            el->app_cb(arg, arg_size, operation, subscriberID);

        else

            if (memcmp(key, el->key, key_size) == 0)
            el->app_cb(arg, arg_size, operation, subscriberID);
    }
    ITERATE_GL_THREADS_END(this->head, curr);
}
