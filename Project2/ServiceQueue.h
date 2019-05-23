#ifndef _SERVICE_QUEUE_H
#define _SERVICE_QUEUE_H

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

//used for location of each buzzer
#define IN_QUEUE 0
#define IN_BUCKET 1

struct node{
    int num; //buzzer ID
    int location; //either in queue or in bucket
    node* prev;
    node* next;
};

struct LL{
    node* head;
    node* tail;
};

class ServiceQueue {

  private:
        /** Your private data members here! 
        *   (you should have NO PUBLIC data members! 
        *                                            
        * Nested private types also go here.  
        * For example, if your design needs some kind of
        *   structure, you would specify it here.
        */ 
    LL queue;
    LL bucket;
    vector<node*> pvec; //vector of pointers to each buzzer
    int qSize; //size of queue


  public:

	/**
	 * Constructor
	 * Description: intializes an empty service queue.
	 * 
	 * RUNTIME REQUIREMENT: O(1)
	 *
         * TODO
	 */
         ServiceQueue() {
             queue.head = nullptr;
             queue.tail = nullptr;
             bucket.head = nullptr;
             bucket.tail = nullptr;
             qSize = 0;
         }

	/**
	 * Destructor
	 * Description:  deallocates all memory assciated
	 *   with service queue 
	 *
	 * RUNTIME REQUIREMENT:  O(N_b) where N_b is the number of buzzer 
	 *	IDs that have been used during the lifetime of the
	 *	service queue; in general, at any particular instant
	 *	the actual queue length may be less than N_b.
	 *
	 *	[See discussion of "re-using buzzers" below]
	 *
         * TODO
	 */
	~ServiceQueue() {
        node* temp;
        
        for (int i = 0; i < pvec.size(); i++)
        {
            delete pvec[i];
        }
    }

	/**
	 * Function: snapshot()
         * param:  buzzers is an integer vector passed by ref
	 * Description:  populates buzzers vector with a "snapshot"
         *               of the queue as a sequence of buzzer IDs 
         *
	 *
	 * RUNTIME REQUIREMENT:  O(N)  (where N is the current queue
	 *		length).
	 */
	void snapshot(std::vector<int> &buzzers) {
            buzzers.clear();   // you don't know the history of the 
                                //   buzzers vector, so we had better
                                //   clear it first.
            node* temp;
            temp = queue.head;
            while (temp != nullptr){ //push contents of queue to buzzers vector
                buzzers.push_back(temp->num);
                temp = temp->next;
            }
            

        }

	/**
	 * Function: length()
	 * Description:  returns the current number of
	 *    entries in the queue.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	int  length() {
             return qSize;
        }

	/**
	 * Function: give_buzzer()
         * Return:   buzzer-ID (integer) assigned to the new customer.
	 * Description:  This is the "enqueue" operation.  For us
	 *    a "buzzer" is represented by an integer (starting
	 *    from zero).  The function selects an available buzzer 
	 *    and places a new entry at the end of the service queue 
	 *    with the selected buzer-ID. 
	 *    This buzzer ID is returned.
	 *    The assigned buzzer-ID is a non-negative integer 
	 *    with the following properties:
	 *
	 *       (1) the buzzer (really it's ID) is not currently 
	 *         taken -- i.e., not in the queue.  (It
	 *         may have been in the queue at some previous
	 *         time -- i.e., buzzer can be re-used).
	 *	  This makes sense:  you can't give the same
	 *	  buzzer to two people!
	 *
	 *       (2) Reusable Buzzers:  A re-usable buzzer is 
	 *	  a buzzer that _was_ in the queue at some previous
	 *	  time, but currently is not.
	 *
         *         REQUIREMENT:  If there is one or more reusable
         *         buzzer, you MUST return one of them; furthermore,
         *         it must be the buzzer that became reusable most 
         *         MOST RECENTLY.
	 *
	 *       (3) if there are no previously-used / reusable buzzers, 
         *         the SMALLEST possible buzzer-ID is used (retrieved from 
         *         inventory).  
	 *	    Properties in this situation (where N is the current
	 *	      queue length):
	 *
	 *		- The largest buzzer-ID used so far is N-1
	 *
	 *		- All buzzer-IDs in {0..N-1} are in the queue
	 *			(in some order).
	 *
	 *		- The next buzzer-ID (from the basement) is N.
	 *
	 *    In other words, you can always get more buzzers (from
	 *    the basement or something), but you don't fetch an
	 *    additional buzzer unless you have to (i.e., no reusable buzzers).
	 *
	 * Comments/Reminders:
	 *
	 *	Rule (3) implies that when we start from an empty queue,
	 *	the first buzzer-ID will be 0 (zero).
	 *
	 *	Rule (2) does NOT require that the _minimum_ reuseable 
	 *	buzzer-ID be used.  If there are multiple reuseable buzzers, 
	 *	any one of them will do.
	 *	
	 *	Note the following property:  if there are no re-useable 
	 *	buzzers, the queue contains all buzzers in {0..N-1} where
	 *       N is the current queue length (of course, the buzzer IDs 
	 *	may be in any order.)
	 *
	 * RUNTIME REQUIREMENT:  O(1)  ON AVERAGE or "AMORTIZED"  
	 *          In other words, if there have been M calls to 
	 *		give_buzzer, the total time taken for those 
	 *		M calls is O(M).
	 *
	 *		An individual call may therefore not be O(1) so long
	 *		as when taken as a whole they average constant time.
	 *
	 */
	int  give_buzzer() {
        int b;
        node *temp, *newNode;

        if (bucket.head != nullptr){ //at least 1 buzzer in bucket?
            b = bucket.head->num;
            bucket.head->location = IN_QUEUE;

            if (queue.head == nullptr){ //empty queue?
                temp = bucket.head->next;
                bucket.head->prev = nullptr;
                bucket.head->next = nullptr;
                queue.head = bucket.head;
                queue.tail = bucket.head;
                bucket.head = temp;
            }
            else{ //queue with at least one buzzer?
                queue.tail->next = bucket.head;
                bucket.head->prev = queue.tail;
                queue.tail = bucket.head;
                temp = bucket.head;
                bucket.head = bucket.head->next;
                temp->next = nullptr;
            }
        }
        else{ //empty buzzer bucket?
            b = qSize;
            newNode = new node;
            newNode->num = b;
            newNode->location = IN_QUEUE;
            pvec.push_back(newNode);

            if (queue.head == nullptr){ //empty queue?
                newNode->prev = nullptr;
                newNode->next = nullptr;
                queue.head = newNode;
                queue.tail = newNode;
            }
            else{ //queue with at least one buzzer?
                queue.tail->next = newNode;
                newNode->prev = queue.tail;
                newNode->next = nullptr;
                queue.tail = newNode;
            }
        }
        qSize++;
        return b;
    }

	/**
	 * function: seat()
	 * description:  if the queue is non-empty, it removes the first 
	 *	 entry from (front of queue) and returns the 
	 *	 buzzer ID.
	 *	 Note that the returned buzzer can now be re-used.
	 *
	 *	 If the queue is empty (nobody to seat), -1 is returned to
	 *	 indicate this fact.
         *
         * Returns:  buzzer ID of dequeued customer, or -1 if queue is empty.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	int seat() {
        node* temp;
        
        if (queue.head != nullptr){ //buzzer in the queue to seat?
            if (bucket.head != nullptr){ //non-empty buzzer bucket?
                temp = queue.head;
                queue.head = queue.head->next;
                if (queue.head != nullptr)
                    queue.head->prev = nullptr;
                temp->next = bucket.head;
                bucket.head->prev = temp;
                bucket.head = temp;
                bucket.head->prev = nullptr;
            }
            else{ //empty buzzer bucket?
                temp = queue.head;
                queue.head = queue.head->next;
                if (queue.head != nullptr)
                    queue.head->prev = nullptr;
                bucket.head = temp;
                bucket.tail = temp;
                temp->prev = nullptr;
                temp->next = nullptr;
            }
            qSize--;
            bucket.head->location = IN_BUCKET;
            return bucket.head->num;
        }
        else //no buzzer in queue to sit
            return -1;
    }


	/**
	 * function: kick_out()
	 *
	 * description:  Some times buzzer holders cause trouble and
	 *		a bouncer needs to take back their buzzer and
	 *		tell them to get lost.
	 *
	 *		Specifially:
	 *
	 *		If the buzzer given by the 2nd parameter is 
	 *		in the queue, the buzzer is removed (and the
	 *		buzzer can now be re-used) and 1 (one) is
	 *		returned (indicating success).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool kick_out(int buzzer){
        node* tempPrev;
        node* tempNext;
        node* temp;

        if (buzzer < pvec.size() && pvec[buzzer]->location == IN_QUEUE){ //buzzer exists and is in queue?
            if (queue.head == pvec[buzzer]){ //kicking first buzzer in queue
                queue.head = queue.head->next;
                if (queue.head != nullptr)
                    queue.head->prev = nullptr;
            }
            else if (queue.tail == pvec[buzzer]){ //kicking last buzzer in queue
                queue.tail = queue.tail->prev;
                queue.tail->next = nullptr;
            }
            else{ //kicking buzzer in middle of list
                tempPrev = pvec[buzzer]->prev;
                tempNext = pvec[buzzer]->next;
                tempPrev->next = tempNext; 
                tempNext->prev = tempPrev;
            }

            if (bucket.head != nullptr){ //non-empty buzzer bucket
                temp = bucket.head;
                bucket.head = pvec[buzzer];
                bucket.head->next = temp;
                temp->prev = bucket.head;
            }
            else{ //empty buzzer bucket
                bucket.head = pvec[buzzer];
                bucket.tail = pvec[buzzer];
                bucket.head->next = nullptr;
                bucket.head->prev = nullptr;
            }
            qSize--;
            bucket.head->location = IN_BUCKET;
            return true;
        }
        else //buzzer is not in bucket or queue
            return false;
    }

	/**
	 * function:  take_bribe()
	 * description:  some people just don't think the rules of everyday
	 *		life apply to them!  They always want to be at
	 *		the front of the line and don't mind bribing
	 *		a bouncer to get there.
	 *
	 *	        In terms of the function:
	 *
	 *		  - if the given buzzer is in the queue, it is 
	 *		    moved from its current position to the front
	 *		    of the queue.  1 is returned indicating success
	 *		    of the operation.
	 *		  - if the buzzer is not in the queue, the queue 
	 *		    is unchanged and 0 is returned (operation failed).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool take_bribe(int buzzer) {
        node* temp;
        if (pvec[buzzer] == queue.head){ //dummy is already at the front of the queue
            return true;
        }

        if (kick_out(buzzer) == true){ //if buzzer is in the queue, 
            //move bribers buzzer to top of bucket, then to front of queue
            temp = bucket.head;
            bucket.head = bucket.head->next;
            if (bucket.head != nullptr)
                bucket.head->prev = nullptr;
            temp->next = queue.head;
            queue.head->prev = temp;
            queue.head = temp;
            queue.head->location = IN_QUEUE;


            qSize++;
            return true;
        }
        else //buzzer was not found in the queue
            return false;
    }

};   // end ServiceQueue class

#endif