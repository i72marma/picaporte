#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 	1000
#define CONSUMERS	50
#define PRODUCERS	100

void * producer(void *arg);
void * consumer(void *arg);

typedef struct {
	int buff[BUFFER_SIZE];
	long head, tail;
	int full, empty;
	pthread_mutex_t *mut;
	pthread_cond_t *n_full, *n_empty;

} queue;

queue * queue_init();
void queue_cleanup(queue *q);
void queue_add(queue *q, int d);
void queue_del(queue *q, int *d);
void error_handler(const char *s);

int main()
{
	srand(time(NULL));	

	queue *fifo;
	pthread_t con[CONSUMERS];
	pthread_t prod[PRODUCERS];
	int s_con, s_prod;			/* Per thread status variable */

	fifo = queue_init();

	/* Thread creation */
	for (long i = 0; i < PRODUCERS; i++) {
		s_prod = pthread_create(&prod[i], NULL, producer, (void *) fifo);

		if (s_prod != 0) {
			fprintf(stderr, "Producer error. Exiting...\n");
			exit(EXIT_FAILURE);
		}
	}
	
	for (long i = 0; i < CONSUMERS; i++) {
		s_con = pthread_create(&con[i], NULL, consumer, (void *) fifo);

		if (s_con != 0) {
			fprintf(stderr, "Consumer error. Exiting...\n");
			exit(EXIT_FAILURE);
		}
	}	

	/* Wait untill thread finish */
	for (long i = 0; i < PRODUCERS; i++) { pthread_join(prod[i], NULL); }
	for (long i = 0; i < CONSUMERS; i++) { pthread_join(con[i], NULL); }

	/* Cleanup and exit */
	queue_cleanup(fifo);
	free(fifo);
	pthread_exit(NULL);
}

void * consumer(void *arg)
{
	int d;
	queue *fifo = (queue *) arg;

	while (1) {	
		/* DMZ zone */
		pthread_mutex_lock(fifo -> mut);

		while (fifo -> empty) {
			printf("Queue EMPTY. Waiting...\n");
			pthread_cond_wait(fifo -> n_empty, fifo -> mut);
		}
	
		queue_del(fifo, &d);
	
		pthread_mutex_unlock(fifo -> mut);
		pthread_cond_broadcast(fifo -> n_full);
	
		printf("Consumer GOT %d from queue\n", d);
	}

	pthread_exit(NULL);
}

void * producer(void *arg)
{
	int d;
	queue *fifo = (queue *) arg;

	while (1) {
		/* DMZ zone */
		pthread_mutex_lock(fifo -> mut);

		d = random() % 1001;
		
		while (fifo -> full) {
			printf("Queue FULL. Waiting...\n");
			pthread_cond_wait(fifo -> n_full, fifo -> mut);
		}

		queue_add(fifo, d);
	
		pthread_mutex_unlock(fifo -> mut);
		pthread_cond_broadcast(fifo -> n_empty);
		
		printf("Producer PUT %d into queue\n", d);	
	}

	pthread_exit(NULL);
}

void queue_add(queue *q, int in)
{
	q -> buff[q -> tail] = in;
	q -> tail++;

	if (q -> tail == BUFFER_SIZE) { q -> tail = 0; }
	if (q -> tail == q -> head) { q -> full = 1; }

	q -> empty = 0;
}

void queue_del(queue *q, int *out)
{
	*out = q -> buff[q -> head];
	q -> head++;

	if (q -> head == BUFFER_SIZE) { q -> head = 0; }
	if (q -> head == q -> tail) { q -> empty = 1; }

	q -> full = 0;
}

queue * queue_init()
{
	queue *q;

	q = (queue *) malloc(sizeof(queue));
	if (q == NULL) { error_handler("malloc()"); }

	q -> empty = 1;
	q -> full = 0;
	q -> head = 0;
	q -> tail = 0;

	q -> mut = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (q -> mut == NULL) { error_handler("malloc()"); }
	pthread_mutex_init(q -> mut, NULL);

	q -> n_full = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
	if (q -> n_full == NULL) { error_handler("malloc()"); }
	pthread_cond_init(q -> n_full, NULL);

	q -> n_empty = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
	if (q -> n_empty == NULL) { error_handler("malloc()"); }
	pthread_cond_init(q -> n_empty, NULL);

	return q;
}

void queue_cleanup(queue *q)
{
	pthread_mutex_destroy(q -> mut);
	pthread_cond_destroy(q -> n_full);
	pthread_cond_destroy(q -> n_empty);

	free(q -> mut);
	free(q -> n_full);
	free(q -> n_empty);	
}

void error_handler(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
