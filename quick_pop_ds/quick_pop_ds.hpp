#include <semaphore>
#include <mutex>

template <typename T>
class DLList
{
public:
    DLList();
    ~DLList();
    void Push(T val);
    T Pop();
    T Peek();
    size_t GetSize();

private:

    class Node
    {
    public:
        Node(T val, Node* next, Node* prev);
        ~Node();

        T m_val;
        Node *m_next;
        Node *m_prev;
    };

    Node* m_head;
    std::counting_semaphore<1024> m_sem;
    std::mutex m_mutex;
    size_t m_size;
};

/* ------------------------------------- */

template <typename T>
DLList<T>::DLList() : m_head(NULL), m_sem(0), 
                                        m_mutex(), m_size(0) {}

/* ------------------------------------- */

template <typename T>
DLList<T>::Node::Node(T val, Node* next, Node* prev) : 
                    m_val(val), m_next(next), m_prev(prev) {}

/* ------------------------------------- */

template <typename T>
void DLList<T>::Push(T val)
{
    m_mutex.lock();

    Node* runner = m_head;
    Node* new_node = new Node(val, NULL, NULL);

    if(m_head == NULL) // empty list
    {
        m_head = new_node;
    }
    else if(m_head->m_val < val)
    {
        new_node->m_next = m_head;
        m_head->m_prev = new_node;
        m_head = new_node;
    }
    else
    {
        while(runner != NULL)
        {
            if(runner->m_val < val)
            {
                new_node->m_next = runner;
                new_node->m_prev = runner->m_prev;
                runner->m_prev->m_next = new_node;
                runner->m_prev = new_node;
                break;
            }
            else
            {
                if(runner->m_next == NULL)
                {
                    new_node->m_prev = runner;
                    runner->m_next = new_node;
                    break;
                }

                runner = runner->m_next;
            }
        }
    }

    ++m_size;
    
    m_sem.release();
    m_mutex.unlock();
}

/* ------------------------------------- */

template <typename T>
T DLList<T>::Pop()
{
    m_sem.acquire();
    m_mutex.lock();
    
    T res = m_head->m_val;
    Node* new_head = m_head->m_next;

    if(new_head != NULL)
    {
        new_head->m_prev = NULL;
    }

    delete m_head;
    m_head = new_head;

    --m_size;

    m_mutex.unlock();

    return res;
}

/* ------------------------------------- */

template <typename T>
T DLList<T>::Peek()
{
    return m_head->m_val;
}

/* ------------------------------------- */

template <typename T>
DLList<T>::Node::~Node() {}

/* ------------------------------------- */

template <typename T>
size_t DLList<T>::GetSize()
{
    return m_size;
}

/* ------------------------------------- */

template <typename T>
DLList<T>::~DLList()
{
    while(m_head != NULL)
    {
        Node *temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
}