     /*
      *   clientScaler.c
      *   
      *   R. Michaels   Sept 2023
      *
      *
      *     compile with 
      *                    gcc -w -o xcli clientScaler.c

      *
      *     old doc:
      *
      *      This is an example program that demonstrates the use of stream
      *      sockets as a BSD IPC mechanism.  This contains the client, and is
      *      intended to operate in conjunction with the server program found
      *      in serv.tcp.  Together, these two programs demonstrate many of the
      *      features of sockets, as well as good conventions for using these
      *      features.
      *
      */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>

#define PORT  0x7200

     int s;                          /* connected socket descriptor */
     struct hostent *hp;             /* pointer to host info for remote host */
     struct servent *sp;             /* pointer to service information */
     long timevar;                   /* contains time returned by time() */
     char *ctime();                  /* declare time formatting routine */

     int optval = 1;
     struct sockaddr_in myaddr_in;   /* for local socket address */
     struct sockaddr_in peeraddr_in; /* for peer socket address */

     /*
      *                      M A I N
      *
      *      This routine is the client which request service from the remote
      *      "example server".  It creates a connection, sends a number of
      *      requests, shuts down the connection in one direction to signal the
      *      server about the end of data, and then receives all of the responses.
      *
      *      The name of the system to which the requests will be sent is given
      *      as a parameter to the command.
      */
 
     main(argc, argv)
     int argc;
     char *argv[];
     {
          int addrlen, i, j, k, n;

           struct myDataStruct {
  	      int ibuf[5];
	      long data1[100]; 
              char cbuf1[40];
	    } ;

           struct myDataStruct sendbuf;
           struct myDataStruct recvbuf;

             if (argc != 3) {
                     fprintf(stderr, "Usage:  %s <remote host> <shell command>\n", argv[0]);
                     exit(1);
             }
                     /* clear out address structures */
             memset ((char *)&myaddr_in, 0, sizeof(struct sockaddr_in));
             memset ((char *)&peeraddr_in, 0, sizeof(struct sockaddr_in));

                     /* Set up the peer address to which we will connect. */
             peeraddr_in.sin_family = AF_INET;
                     /* Get the host information for the hostname that the
                      * user passed in.
                      */
             hp = gethostbyname (argv[1]);
                     /* argv[1] is the host name. */
             if (hp == NULL) {
                     fprintf(stderr, "%s: %s not found in /etc/hosts\n",
                                     argv[0], argv[1]);
                     exit(1);
             }
             peeraddr_in.sin_addr.s_addr =  ((struct in_addr *)
                 (hp->h_addr))->s_addr  ; 

             //printf("peeraddr %x \n",peeraddr_in.sin_addr.s_addr);


         /* Use an available port and allow re-use of socket*/
             peeraddr_in.sin_port = htons(PORT);

                     /* Create the socket. */
         //printf("create socket  \n");
             s = socket (AF_INET, SOCK_STREAM, 0);
             if (s == -1) {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to create socket\n", argv[0]);
                     exit(1);
             }
             if (setsockopt(s, SOL_SOCKET, 
                   SO_REUSEADDR,&optval,sizeof(optval) ) == -1) {
                     printf("Conn aborted (reuseaddr)\n");
                     exit(1);
             }

 
                     /* Try to connect to the remote server at the address
                      * which was just built into peeraddr.
                      */
          //printf("about to call connect %d  \n",s);
             if (connect(s, &peeraddr_in, sizeof(struct sockaddr_in)) == -1) {
                     perror(argv[0]);

       fprintf(stderr, "%s: unable to connect to remote %s \n", argv[0],argv[1]) ;
                     exit(1);
             }
                     /* Since the connect call assigns a random address
                      * to the local end of this connection, let's use
                      * getsockname to see what it assigned.  Note that
                      * addrlen needs to be passed in as a pointer,
                      * because getsockname returns the actual length
                      * of the address.
                      */
             addrlen = sizeof(struct sockaddr_in);
             if (getsockname(s, &myaddr_in, &addrlen) == -1) {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to read socket address\n", argv[0]);
                     exit(1);
             }

                     /* Print out a startup message for the user. */
             time(&timevar);
             //printf("Connected to %s on port %u at %s",
                             //argv[1], ntohs(myaddr_in.sin_port), ctime(&timevar));


                     /* This sleep simulates any preliminary processing
                      * that a real client might do here.
                      */
             //sleep(1);

 
                     /* Send out all the requests to the remote server.
                      * In this case, five are sent, but any random number
                      * could be used.  Note that the first four bytes of
                      * buf are set up to contain the request number.  This
                      * number will be returned in the reply from the server.
                      */

                     /* CAUTION:   Both the client's and server's
                      * sockets can only queue a limited amount of
                      * data on their receive queues.
                      */


	     char lcbuf1[40];
             sprintf(lcbuf1,argv[2]);
             //printf("command found = %s \n",lcbuf1);
             sendbuf.ibuf[0] = 0;
             if(strstr(lcbuf1,"runstart")!=NULL) {
               printf("setting control bit to 1\n");
               sendbuf.ibuf[0] = 1;
	     }
             if(strstr(lcbuf1,"getdat")!=NULL) {
               //printf("getting big data\n");
               sendbuf.ibuf[0] = 2;
	     }
             strcpy(sendbuf.cbuf1,lcbuf1);


            //printf("cbuf to send =  %s \n",sendbuf.cbuf1);
	    if (send(s, (const void *) &sendbuf, sizeof(sendbuf), 0) != sizeof(sendbuf)) {
                  fprintf(stderr, "%s: Connection aborted on error ",
                                           argv[0]);
                  fprintf(stderr, "on send number %d\n", i);
                  exit(1);
	    }
     

             if (shutdown(s, 1) == -1) {
                     perror(argv[0]);
                     fprintf(stderr, "%s: unable to shutdown socket\n", argv[0]);
                     exit(1);
             }

             
             while (i = recv(s, (const void *) &recvbuf, sizeof(recvbuf), 0)) {


                     if (i == -1) {
     errout:                 perror(argv[0]);
                             fprintf(stderr, "%s: error reading result\n", argv[0]);
                             exit(1);
                     }

             //printf("Received cbuf =  %s \n",recvbuf.cbuf1);
             //printf("Fake scaler data \n");

             int slots = 0;
             int channels = 0;
             //argv[1]
             
             printf("Slots: %d\n",slots);
             printf("Channels: %d\n",channels);
	     for (i=0; i<50; i++) {
               //printf("data[%d] = %lx\n",i,recvbuf.data1[i]);
               printf("%d: %lu(0)\n",i,recvbuf.data1[i]);
               //printf("%d: %lx(0)\n",i,recvbuf.data1[i]&0xffffffff);//lu
               //printf("%d: %lx(0)\n",i,(recvbuf.data1[i]>>32LL)&0xffffffff);//lu
               //printf("%lu\n",recvbuf.data1[i]);
	     }	       
	     
	     }	     

                     /* Print message indicating completion of task. */

             time(&timevar);
             printf("All done at %s", ctime(&timevar));

     }

