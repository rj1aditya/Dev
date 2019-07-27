63Moons
	using 2 threads print odd and even numbers in a sequence from 1 to 100
	difference in struct and class
>>	move sementics( why it requires and what it does? ) >> done
	pointers: leak memory( when memory get leaked ) and dangling pointer( how to handle dangling pointer )
		e.g int *p = new int(3);
			p = null;
			Note: now here memory get leaked, because it is not deleted and pointer is pointing to null.
		e.g int *p = NULL;
			p = new int(3);
			delete p;
			now p is become dangling pointer. To handle this we have to again initialize to NULL value after delete.
			p = NULL;
	
	Private descructor, and use of it?
		if we want to prevent the user to create an object in the stack, ABC obj;( to prevent this )
	How to prevent dynamic allocation of the memory?
		by doing delete operator overloading and declare it as private.
	Shared memory
	msg queue, can we send a pointer in the message queue?
	future and promise obj
>>	Why constructor can't be virtual? >> done
	Size of empty class
		always 1 byte
	
	in copy constructor what is the significace of const?
	in copy constructor what if i remove const keyword?
	in copy constructor what if i remove &?

Mistakes: 1. It was noticed that you always become jajwati when you find that the question is in your coat. 
			And you got lost. Like you gave the answer of empty class is depends on the system architechture( 32bit or 64 bit).
		2. you dont listen to the interviewer properly.
		3. So always keep in mind before saying anything, listen properly and think twice what you are going to answer.
		