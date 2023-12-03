// Assign 1
// 1. Write a program to create two processes. First process takes a string and
// passes it to second process through a pipe. The second process concatenates
// the received string with another string without using string function and sends
// it back to the first process for printing.
// 2.Develop a program in which the parent process sends two matrices to its
// child process through a pipe and the child process returns the sum of the
// matrices to the parent through a pipe. The parent should print the result.

// Assign 2
// 1.Suppose there exists a file and you have to read, write and update the file concurrently. Write
// a multithreaded program such that , there should be different threads for all different tasks
// and each thread access the file synchronously. Note: Use Mutex

// 2.Write a program to implement a deadlock scenario, in which two threads are accessing two
// resources concurrently.

// 3.Write a program to implement deadlock avoidance using conditional locking in which two
// threads are accessing two resources concurrently. Note: user pthread_mutex_trylock()
// functional locking

// Assign 3
// 1. lAMPORT logical clock

// Assign 4
// 1. distributed mutucal


// Assign 5
// 1.
// i) Implement concurrent echo client-server application.
// ii) Implement a client-server program in which the server accepts a connection from a
// client and updates it own Master table by adding the client information and send the
// updated table to client, so client can update their own table.
// Table format:
// iii)Develop a client server program to implement a date time server and client. 
// Upon connection establishment,the server should send its current date, time and CPU 
// load information to its clients.


// Assign 6
// Suppose you have two TCP servers for converting a lower case string to upper case string.
// You have to design a load balancer server that accept lower case string from client and check
// for the CPU utilization of both servers. Load balancer will transfer the string to the server
// having less CPU utilization. The load balancer will get upper case string from server and
// return to the clients.


// Assign 7
// 7 (i) Implement RPC mechanism for a file transfer across a network in ‘C’.
// (ii) Implement ‘Java RMI’ mechanism for accessing methods of remote systems

// Assign 8
// Implement CORBA mechanism by using ‘C++’ program at one end and ‘Java’ program
// on the other.