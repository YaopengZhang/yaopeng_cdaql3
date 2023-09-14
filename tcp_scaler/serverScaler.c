     /*
      *   serverScaler.c
      *   
      *   R. Michaels   Sept 2023
      *
      *
      *     compile with 
      *                    gcc -w -o xser serverScaler.c
      *
      *     old doc:
     *
     *      This is an example program that demonstrates the use of
     *      stream sockets as a BSD IPC mechanism.  This contains the server,
     *      and is intended to operate in conjunction with the client
     *      program found in client.tcp.  Together, these two programs
     *      demonstrate many of the features of sockets, as well as good
     *      conventions for using these features.
     *
     *
     */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <netdb.h>

#define PORT  0x7200
       
     int s;                          /* connected socket descriptor */
     int ls;                         /* listen socket descriptor */

     struct hostent *hp;             /* pointer to host info for remote host */
     struct servent *sp;             /* pointer to service information */

     long timevar;                   /* contains time returned by time() */
     char *ctime();                  /* declare time formatting routine */

     struct linger linger = {1,1};   /* allow a lingering, graceful close; */
                                     /* used when setting SO_LINGER */

     int optval = 0;
     struct sockaddr_in myaddr_in;   /* for local socket address */
     struct sockaddr_in peeraddr_in; /* for peer socket address */
 
     /*
      *                                      M A I N
      *
      *      This routine starts the server.  It forks, leaving the child
      *      to do all the work, so it does not have to be run in the
      *      background.  It sets up the listen socket, and for each incoming
      *      connection, it forks a child process to process the data.  It
      *      will loop forever, until killed by a signal.
      */
     int main(int argc, char *argv[]) {

       int i;
 
             int addrlen;
                     /* clear out address structures */
             memset ((char *)&myaddr_in, 0, sizeof(struct sockaddr_in));
             memset ((char *)&peeraddr_in, 0, sizeof(struct sockaddr_in));
                     /* Set up address structure for the listen socket.
     */
             myaddr_in.sin_family = AF_INET;
             myaddr_in.sin_addr.s_addr = htons(INADDR_ANY);
         /* Use an available port and allow re-use of socket*/
             myaddr_in.sin_port = htons(PORT);
         /* Create the listen socket. */
             ls = socket (AF_INET, SOCK_STREAM, 0);
             if (setsockopt(ls, SOL_SOCKET, 
                   SO_REUSEADDR,&optval,sizeof(optval) ) == -1) {
     errout:         printf("Conn with %s aborted (reuseaddr)\n");
                     exit(1);
             }
               
             if (ls == -1) {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to create socket\n", argv[0]);
                     exit(1);
             }
 
                     /* Bind the listen address to the socket. */
             if (bind(ls, &myaddr_in, sizeof(struct sockaddr_in)) == -1)
     {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to bind address\n", argv[0]);
                     exit(1);
             }
             if (listen(ls, 5) == -1) {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to listen on socket\n", argv[0]);
                     exit(1);
             }

             setpgrp();

             switch (fork()) {
             case -1:                /* Unable to fork, for some reason. */
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to fork daemon\n", argv[0]);
                     exit(1);

             case 0:                 /* The child process (daemon) comes here. */
                     fclose(stdin);
                     fclose(stderr);
 
                     signal(SIGCLD, SIG_IGN);
                     for(;;) {
                             addrlen = sizeof(struct sockaddr_in);
                             s = accept(ls, &peeraddr_in, &addrlen);
                             if ( s == -1) exit(1);

                             switch (fork()) {
                             case -1:        /* Can't fork, just continue. */
                                     exit(1);
                             case 0:         /* Child process comes here. */
                                     server();
                                     exit(0);
                             default:        /* Daemon process comes here. */
                                     close(s);
                             }

                     }

             default:                /* Parent process comes here. */
                     exit(0);
             }
     }
 
     /*
      *                              S E R V E R
      *
      *      This is the actual server routine that the daemon forks to
      *      handle each individual connection.  Its purpose is to receive
      *      the request packets from the remote client, process them,
      *      and return the results to the client.  It will also write some
      *      logging information to stdout.
      *
      */
     server()
     {
             int reqcnt = 0;         /* keeps count of number of requests */

	     int icomm = 0;
             char scommand[200];
           struct MyDataStruct {
	      int ibuf[5];
	      long data1[100];  
              char cbuf1[40];
	    } ;
           struct MyDataStruct sendbuf;
           struct MyDataStruct recvbuf;

             char *inet_ntoa();
             char *hostname;         /* points to the remote host's name string */
             int i,len, len1;

                     /* Close the listen socket inherited from the daemon. */
             close(ls);

             hp = gethostbyaddr ((char *) &peeraddr_in.sin_addr,
                                     sizeof (struct in_addr),
                                     peeraddr_in.sin_family);

             if (hp == NULL) {
                     hostname = inet_ntoa(peeraddr_in.sin_addr);
             } else {
                     hostname = hp->h_name;  /* point to host's name */
             }
                     /* Log a startup message. */
             time (&timevar);
 
             printf("Startup from %s port %u at %s",
                     hostname, ntohs(peeraddr_in.sin_port), ctime(&timevar));

             if (setsockopt(s, SOL_SOCKET, SO_LINGER, &linger,
                                             sizeof(linger)) == -1) {
     errout:         printf("Connection with %s aborted on error\n", hostname);
                     exit(1);
             }

             while (len = recv(s, (const void *) &recvbuf, sizeof(recvbuf), 0)) {
                     if (len == -1) goto errout; /* error from recv */
 
                             /* Increment the request count. */
                     reqcnt++;
                             /* This sleep simulates the processing of the
                              * request that a real server might do.
                              */
                     sleep(1);

                     printf("Serving %s \n", hostname);

                             /* Send a response back to the client. */

                     icomm = recvbuf.ibuf[0];
		     printf("I got command %d\n",icomm);
                     strcpy(scommand,recvbuf.cbuf1);
                     printf("String Buffer = %s \n",scommand);

		     sendbuf.ibuf[0]=66;

		     

             switch (icomm) {
             case 1:                
	       // do something else 

	       break;
  
	     case 2:

               printf("Here is my big data \n");
               for (i=0; i<20; i++) {
		 sendbuf.data1[i] = 0xffff123456789a00 + i;
 
	       }
		 
	       break;

             default:
	       printf("nothing\n");

	     }



	   if (send(s, (const void *) &sendbuf, sizeof(sendbuf), 0) != sizeof(sendbuf)) goto errout;
	     }

             close(s);

                     /* Log a finishing message. */
             time (&timevar);
             printf("Completed %s port %u, %d requests, at %s\n",
                     hostname, ntohs(peeraddr_in.sin_port), reqcnt, ctime(&timevar));
     }



