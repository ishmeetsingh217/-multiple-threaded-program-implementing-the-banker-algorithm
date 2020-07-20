# Bankers Algorithm

- thread run and join part

	pthread_create(&tid, NULL, threadRun, NULL);
	pthread_join(tid, NULL);

- compile
gcc bankers_algorithm.c -std=c99 -pthread -o bankers_algorithm


./assingment04.out.c [available resource array<1><2><3><4>]
```

-command

	RQ [customer_id] [Resources values array]
		The customer request the resources from bank
	RL [customer_id] [Resources values array]
		The customer release the resources to bank from his allocated resource
	Run 
		Run the safe the sequeces and out the result
	*
		Outout available resources, maximum,needed,allocated resources



