Remote Shell ActiveX Control

Please note that this ActiveX control requires the VB 6.0 runtime.

About RemoteShell

RemoteShell is an ActiveX Control that allows a VB program 
(or any other program capable of utilizing ActiveX controls) 
to log on to a Unix system and execute a remote command.  
This control behaves like the rsh and rexec commands 
found on many versions of Unix operating systems. This control 
is very handy for executing scripts or programs on a Unix machine 
and retrieving the results.

Using RemoteShell

You will need to configure your Unix machine to allow for a 
remote shell or remote exec login for the user name you use.  
The default path for execution is the user's home path 
on the Unix server.


Methods, Properties and Events

Properties

Async	
(Boolean) A flag to process the control synchronously or 
asynchronously.  If false, the Process method will not 
return control until the command has completed on the Unix server.

ConnectionType
Specifies rsh or rexec.  In rsh mode, you must specify the command, host,
remote username and local machine or username.  in rexec mode, you must 
specify the command, host, host username and password.

Command	
(String) The unix command to execute.

Host	
(String) The address of the machine to execute the 
remote shell on. This can be a numeric address or DNS name. 
A numeric address is preferable since a failed DNS 
lookup can cause delays.

Username	
(String) The name of the user you 
wish to use to logon to the Unix server.

LocalUsername	
(String) Your local server or local server username.  Used in rsh mode
for host authentication.

Password	
(String) The password of the user you 
wish to use to logon to the Unix server.


Methods

Process
Process the command on the server specified. 

About Box
About RemoteShell. 

Events

ReceiveData(InData as String)
Data received in response to the remote shell command.  
For example, if the command was ls -l, the command 
would return a directory list through the ReceiveData event
	
AsyncComplete
Sent in response to an Async event completion.

Error(ErrorNumber as String, ErrorText as String)
Send in response to a connection, process, or other 
error during the command processing.

Limitations on the Unregistered Version
	
There is no limitation to this unregistered version except for the
register me box that appears upon control creation.  With the registered version you 
will receive both the latest control version (by request) and the 
source code and registered control (include with the download) 
written entirely in Microsoft Visual Basic, version 5.0.


Registration
When you are ready to register, please return to 	
http://www.pathguide.com/greg/rsh.htm.
or email me at gregl@pathguide.com

Thank you for your interest in RemoteShell.

