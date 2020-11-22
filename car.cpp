#include <iostream>
using namespace std;
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

struct periodic_info {
	int sig;
	sigset_t alarm_sig;
};

void readCSVFile()
{

}



//The period is in nanoseconds.
static int make_periodic(int unsigned period, struct periodic_info *info)
{
	static int next_sig;
	int ret;
	unsigned int ns;
	unsigned int sec;
	struct sigevent sigev;
	timer_t timer_id;
	struct itimerspec itval;

	/* Initialise next_sig first time through. We can't use static
	   initialisation because SIGRTMIN is a function call, not a constant */
	if (next_sig == 0)
		next_sig = SIGRTMIN;
	/* Check that we have not run out of signals */
	if (next_sig > SIGRTMAX)
		return -1;
	info->sig = next_sig;
	next_sig++;
	/* Create the signal mask that will be used in wait_period */
	sigemptyset(&(info->alarm_sig));
	sigaddset(&(info->alarm_sig), info->sig);

	/* Create a timer that will generate the signal we have chosen */
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = info->sig;
	sigev.sigev_value.sival_ptr = (void *)&timer_id;
	ret = timer_create(CLOCK_MONOTONIC, &sigev, &timer_id);
	if (ret == -1)
		return ret;

	/* Make the timer periodic */
	sec = (period/1000);
	ns = (period*1000000);
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timer_settime(timer_id, 0, &itval, NULL);
	return ret;
}

static void wait_period(struct periodic_info *info)
{
	int sig;
	sigwait(&(info->alarm_sig), &sig);
}

static int thread_1_count;
static int thread_2_count;

struct numbers {
  int a;
  int b;
  int sum;
};

void *
sum_thread (void *_args)
{
  /* Cast the arguments to the usable struct type */
  struct numbers *args = (struct numbers *) _args;

  /* Place the result into the struct itself (on the heap) */
  args->sum = args->a + args->b;
  pthread_exit (NULL);
}


static void *thread_2(void *arg)
{
	struct periodic_info info;

	printf("Thread 2 period 20ms\n");
	make_periodic(2000000, &info);
	while (1) {
		printf("Thread 2\n");
		thread_2_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readFull_Comsumption_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(10, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readEngine_Speed_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(500, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readEngine_Coolant_Temperature_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(2000, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readCurrent_Gear_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(100, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readTransmission_Oil_Temperature_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(5000, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readVehicle_Speed_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(100, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readAcceleration_Speed_Longitudinal_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(150, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *readIndication_Of_Break_Switch_Thread(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 10ms\n");
	make_periodic(100, &info);
	while (1) {
		printf("Thread 1\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayFull_Comsumption_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(10, &info);
	while (1) {
		printf("Fuel Consumption\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayEngine_Speed_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(500, &info);
	while (1) {
		printf("Engine Speed\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayEngine_Coolant_Temperature_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(2000, &info);
	while (1) {
		printf("Engine Coolant Temperature\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayCurrent_Gear_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(100, &info);
	while (1) {
		printf("Current Gear\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayTransmission_Oil_Temperature_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(5000, &info);
	while (1) {
		printf("Transmission Oil Temperature\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayVehicle_Speed_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(100000000, &info);
	while (1) {
		printf("Vehicle Speed\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayAcceleration_Speed_Longitudinal_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(150000000, &info);
	while (1) {
		printf("Acceleration Speed Longitudinal\n");
		thread_1_count++;
		wait_period(&info);
	}
	return NULL;
}

static void *displayIndication_Of_Break_Switch_Thread(void *arg)
{
	struct periodic_info info;

	//printf("Thread 1 period 10ms\n");
	make_periodic(100000000, &info);
	while (1) {
		printf("Indication Of Break Switch\n");
		thread_1_count++;
		wait_period(&info);

	}
	return NULL;
}


int main() {

	//We need to implement a reading thread for each of the following data

	//We need to get the fuel Consumption every 10 ms
	//We need to get the engine speed every 500 ms
	//We need to get the engine coolant temperature Consumption every 2s
	//We need to get the current gear every 100 ms
	//We need to get the transmission oil temperature every 5s
	//We need to get the vehicle speed every 100 ms
	//We need to get the Acceleration Speed Longitudinal every 150 ms
	//We need to get the indication of break switch every 10 ms

	//We need to implement a displaying thread for each of the following data

	//We need to get the fuel Consumption every 10 ms
	//We need to get the engine speed every 500 ms
	//We need to get the engine coolant temperature Consumption every 2s
	//We need to get the current gear every 100 ms
	//We need to get the transmission oil temperature every 5s
	//We need to get the vehicle speed every 100 ms
	//We need to get the Acceleration Speed Longitudinal every 150 ms
	//We need to get the indication of break switch every 10 ms

	//We need to implement 16 threads with periodic requirements



	cout << "Hello World twice!!!" << endl; // prints Hello World!!!

		//pthread_t t_1;
		//pthread_t t_2;
		sigset_t alarm_sig;
		int i;


		//Lets create all the reading threads now!!!
		pthread_t readFull_Comsumption_Thread_i;
		pthread_t readEngine_Speed_Thread_i;
		pthread_t readEngine_Coolant_Temperature_Thread_i;
		pthread_t readCurrent_Gear_Thread_i;
		pthread_t readTransmission_Oil_Temperature_Thread_i;
		pthread_t readVehicle_Speed_Thread_i;
		pthread_t readAcceleration_Speed_Longitudinal_Thread_i;
		pthread_t readIndication_Of_Break_Switch_Thread_i;

		//Lets create all the reading threads now!!!
		pthread_t displayFull_Comsumption_Thread_i;
		pthread_t displayEngine_Speed_Thread_i;
		pthread_t displayEngine_Coolant_Temperature_Thread_i;
		pthread_t displayCurrent_Gear_Thread_i;
		pthread_t displayTransmission_Oil_Temperature_Thread_i;
		pthread_t displayVehicle_Speed_Thread_i;
		pthread_t displayAcceleration_Speed_Longitudinal_Thread_i;
		pthread_t displayIndication_Of_Break_Switch_Thread_i;


		printf("Periodic threads using POSIX timers\n");

		/* Block all real time signals so they can be used for the timers.
		   Note: this has to be done in main() before any threads are created
		   so they all inherit the same mask. Doing it later is subject to
		   race conditions */
		sigemptyset(&alarm_sig);
		for (i = SIGRTMIN; i <= SIGRTMAX; i++)
			sigaddset(&alarm_sig, i);
		sigprocmask(SIG_BLOCK, &alarm_sig, NULL);

		//pthread_create(&t_1, NULL, thread_1, NULL);
		//pthread_create(&t_2, NULL, thread_2, NULL);

		pthread_create(&readFull_Comsumption_Thread_i, NULL, readFull_Comsumption_Thread, NULL);
		pthread_create(&readEngine_Speed_Thread_i, NULL, readEngine_Speed_Thread, NULL);
		pthread_create(&readEngine_Coolant_Temperature_Thread_i, NULL, readEngine_Coolant_Temperature_Thread, NULL);
		pthread_create(&readCurrent_Gear_Thread_i, NULL, readCurrent_Gear_Thread, NULL);
		pthread_create(&readTransmission_Oil_Temperature_Thread_i, NULL, readTransmission_Oil_Temperature_Thread, NULL);
		pthread_create(&readVehicle_Speed_Thread_i, NULL, readVehicle_Speed_Thread, NULL);
		pthread_create(&readAcceleration_Speed_Longitudinal_Thread_i, NULL, readAcceleration_Speed_Longitudinal_Thread, NULL);
		pthread_create(&readIndication_Of_Break_Switch_Thread_i, NULL, readIndication_Of_Break_Switch_Thread, NULL);


		pthread_create(&displayFull_Comsumption_Thread_i, NULL, displayFull_Comsumption_Thread, NULL);
		pthread_create(&displayEngine_Speed_Thread_i, NULL, displayEngine_Speed_Thread, NULL);
		pthread_create(&displayEngine_Coolant_Temperature_Thread_i, NULL, displayEngine_Coolant_Temperature_Thread, NULL);
		pthread_create(&displayCurrent_Gear_Thread_i, NULL, displayCurrent_Gear_Thread, NULL);
		pthread_create(&displayTransmission_Oil_Temperature_Thread_i, NULL, displayTransmission_Oil_Temperature_Thread, NULL);
		pthread_create(&displayVehicle_Speed_Thread_i, NULL, displayVehicle_Speed_Thread, NULL);
		pthread_create(&displayAcceleration_Speed_Longitudinal_Thread_i, NULL, displayAcceleration_Speed_Longitudinal_Thread, NULL);
		pthread_create(&displayIndication_Of_Break_Switch_Thread_i, NULL, displayIndication_Of_Break_Switch_Thread, NULL);



		sleep(3000);
		//printf("Thread 1 %d iterations\n", thread_1_count);
		//printf("Thread 2 %d iterations\n", thread_2_count);
	return 0;
}
