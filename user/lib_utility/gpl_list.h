/**
 * @brief	GPL license linux kernel dual linked list porting
 * 			for use in user-space.
 *
 * from [ http://www.mcs.anl.gov/~kazutomo/list/list.h ]
 */

#ifndef __GPL_LIST_H__
#define __GPL_LIST_H__


#define offset_of(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({	\
	const typeof( ((type *)0)->member) *__mptr = (ptr);	\
	(type *)((char *)__mptr - offset_of(type,member));})

#define LIST_POISON1	((void *) 0x00100100)
#define LIST_POISON2	((void *) 0x00200200)


struct list_head
{
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name)	{ &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
	} while( 0 )

static inline void __list_add(
	struct list_head			*new,
	struct list_head			*prev,
	struct list_head			*next
	)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(
	struct list_head			*new,
	struct list_head			*head
	)
{
	__list_add( new, head, head->next );
}

static inline void list_add_tail(
	struct list_head			*new,
	struct list_head			*head
	)
{
	__list_add( new, head->prev, head );
}

static inline void __list_del(
	struct list_head			*prev,
	struct list_head			*next
	)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(
	struct list_head			*entry
	)
{
	__list_del( entry->prev, entry->next );
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

static inline void list_del_init(
	struct list_head			*entry
	)
{
	__list_del( entry->prev, entry->next );
	INIT_LIST_HEAD( entry );
}

static inline void list_move(
	struct list_head			*list,
	struct list_head			*head
	)
{
	__list_del( list->prev, list->next );
	list_add( list, head );
}

static inline void list_move_tail(
	struct list_head			*list,
	struct list_head			*head
	)
{
	__list_del( list->prev, list->next );
	list_add_tail( list, head );
}

static inline int list_empty(
	const struct list_head		*head
	)
{
	return head->next == head;
}

static inline void __list_splice(
	struct list_head			*list,
	struct list_head			*head
	)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;
	struct list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

static inline void list_splice(
	struct list_head			*list,
	struct list_head			*head
	)
{
	if( !list_empty( list ) )
		__list_splice( list, head );
}

static inline void list_splice_init(
	struct list_head			*list,
	struct list_head			*head
	)
{
	if( !list_empty( list ) )
	{
		__list_splice( list, head );
		INIT_LIST_HEAD( list );
	}
}


#define list_entry(ptr, type, member)	\
	container_of(ptr, type, member)

#define list_for_each(pos, head)								\
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define __list_for_each(pos, head)								\
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head)							\
	for(pos = (head)->prev; prefetch(pos->prev), pos != (head);	\
		pos = pos->prev)

#define list_for_each_safe(pos, n, head)						\
	for(pos = (head)->next, n = pos->next; pos != (head);		\
		pos = n, n = pos->next)

#define list_for_each_entry(pos, head, member)					\
	for(pos = list_entry((head)->next, typeof(*pos), member);	\
		&pos->member != (head);									\
		pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_entry_reverse(pos, head, member)				\
	for(pos = list_entry((head)->prev, typeof(*pos), member);	\
		&pos->member != (head);									\
		pos = list_entry(pos->member.prev, typeof(*pos), member))

#define list_prepare_entry(pos, head, member)					\
	((pos) ? : list_entry(head, typeof(*pos), member))

#define list_for_each_entry_continue(pos, head, member)			\
	for(pos = list_entry(pos->member.next, typeof(*pos), member);	\
		&pos->member != (head);									\
		pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for(pos = list_entry((head)->next, typeof(*pos), member),	\
			n = list_entry(pos->member.next, typeof(*pos), member);	\
		&pos->member != (head);									\
		pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_for_each_entry_safe_continue(pos, n, head, member)	\
	for(pos = list_entry(pos->member.next, typeof(*pos), member),	\
			n = list_entry(pos->member.next, typeof(*pos), member),	\
		&pos->member != (head);									\
		pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_for_each_entry_safe_reverse(pos, n, head, memeber)	\
	for(pos = list_entry((head)->prev, typeof(*pos), member),	\
			n = list_entry(pos->member.prev, typeof(*pos), member);	\
		&pos->member != (head);									\
		pos = n, n = list_entry(n->member.prev, typeof(*n), member))


#endif	//> #ifndef __GPL_LIST_H__
